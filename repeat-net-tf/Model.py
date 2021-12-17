import tensorflow as tf
from tensorflow.keras import layers

import BilinearAttention as ba


class RepeatNet(layers.Layer):
    def __init__(self,
                 embedding_size,
                 hidden_size,
                 item_vocab_size,
                 trainable=True,
                 name=None,
                 dtype=None,
                 dynamic=False,
                 **kwargs
                 ):
        # super().__init__(trainable=trainable, name=name, dtype=dtype, dynamic=dynamic, **kwargs)
        super(RepeatNet, self).__init__()

        self.embedding_size = embedding_size
        self.hidden_size = hidden_size
        self.item_vocab_size = item_vocab_size

        self.item_emb = layers.Embedding(
            input_dim=item_vocab_size,
            output_dim=embedding_size,
            mask_zero=False
        )

        self.enc = layers.Bidirectional(
            layer=layers.GRU(
                units=hidden_size // 2,
                return_sequences=True)
        )

        self.mode_attn = ba.BilinearAttention(
            hidden_size, hidden_size, hidden_size)

        self.mode = layers.Dense(
            units=2,
            input_shape=(hidden_size,),
            activation=None
        )

        self.repeat_attn = ba.BilinearAttention(
            hidden_size, hidden_size, hidden_size)
        self.explore_attn = ba.BilinearAttention(
            hidden_size, hidden_size, hidden_size)
        self.explore = layers.Dense(
            units=item_vocab_size,
            input_shape=(hidden_size,),
            activation=None
        )

    @staticmethod
    def gru_call(gru, gru_input, lengths, state=None, batch_first=True):
        gru = layers.Flatten()(gru)
        input_lengths = tf.sort(
            values=lengths,
            direction="DESCENDING"
        )
        perm = tf.argsort(
            values=lengths,
            direction="DESCENDING"
        )

        gru_input = gru_input[perm]
        if state:
            state = tf.transpose(  # creates new tensor
                a=state[perm],
                perm=[0, 1]
            )

        total_length = gru_input.get_shape(1)
        if not batch_first:
            gru_input = tf.transpose(
                a=gru_input,
                perm=[0, 1]
            )

        # packed = tf.keras.preprocessing.sequence.pad_sequences(sequences = gru_input)

        packed = tf.stack(
            values=gru_input
        )

        '''
        packed = layers.StackedRNNCells(
            cells=gru_input
        )
        '''
        outputs = gru(
            inputs=packed,
            initial_state=state
        )
        state = gru.states

        outputs = tf.pad(
            tensor=outputs,
            paddings=input_lengths,  # TODO get paddings
            mode="CONSTANT"
        )

        _ = tf.sort(
            values=perm,
            direction="ASCENDING"
        )
        perm = tf.argsort(
            values=perm,
            direction="ASCENDING"
        )
        outputs = outputs[perm]
        state = tf.transpose(
            a=state,
            perm=[0, 1]
        )[perm]

        return outputs, state

    @classmethod
    def my_tensorflow_scatter_add(cls, tensor, indices, updates):
        original_tensor = tensor
        indices = tf.compat.v1.reshape(
            indices, shape=[-1, tf.shape(indices)[-1]])
        indices_add = tf.compat.v1.expand_dims(
            tf.range(0, tf.shape(indices)[0], 1)*(tf.shape(tensor)[-1]), axis=-1)
        indices += indices_add

        tensor = tf.compat.v1.reshape(tensor, shape=[-1])
        indices = tf.compat.v1.reshape(indices, shape=[-1, 1])
        updates = tf.compat.v1.reshape(updates, shape=[-1])

        scatter = tf.compat.v1.tensor_scatter_nd_add(tensor, indices, updates)
        scatter = tf.compat.v1.reshape(scatter, shape=[tf.shape(
            original_tensor)[0], tf.shape(original_tensor)[1], -1])
        return scatter

    @staticmethod
    def build_map(b_map, map_max=None):
        batch_size, b_len = b_map.size()  # TODO check TF data
        if not map_max:
            map_max = tf.reduce_max(b_map).eval() + 1
        b_map_ = RepeatNet.my_tensorflow_scatter_add(  # undefined behaviour of scatter
            tensor=tf.expand_dims(
                input=b_map,
                axis=2
            ),
            indices=tf.zeros(b_map.shape, tf.float64),
            updates=tf.zeros(b_map.shape, tf.float64)
        )
        tf.stop_gradient(b_map_)
        return b_map_

    def model(self, data):
        batch_size = data['item_seq'].size(0)  # TODO check TF data
        mask = data['item_seq'].ne(0)
        lengths = mask.float().sum(dim=-1).long()

        item_seq_embs = layers.Dropout(
            inputs=self.item_emb(data['item_seq']),
            rate=0.5,
            training=True
        )

        output, state = self.gru_call(
            self.enc, item_seq_embs, lengths, batch_first=True)
        state = layers.Dropout(
            inputs=state,
            rate=0.5,
            training=True
        )
        output = layers.Dropout(
            inputs=output,
            rate=0.5,
            training=True
        )

        explore_feature, attn, norm_attn = self.explore_attn(
            tf.expand_dims(
                input=state.reshape(batch_size, -1),
                axis=1),
            output,
            output,
            mask=tf.expand_dims(
                input=mask,
                axis=1)
        )

        p_explore = self.explore(tf.squeeze(
            input=explore_feature,
            axis=1)
        )
        explore_mask = tf.squeeze(
            input=tf.matmul(
                a=tf.expand_dims(
                    input=tf.cast(
                        x=(data['item_seq'] > 0),
                        dtype=tf.float64
                    ),
                    axis=1
                ),
                b=data['source_map']
            ),
            axis=1
        )

        # p_explore = ba.BilinearAttention.mask_fill()  # TODO whether need tf.boolean_mask
        p_mode = tf.nn.softmax(
            logits=p_explore,
            axis=-1
        )
        _, p_repeat = self.repeat_attn.score(tf.expand_dims(
            input=state.reshape(batch_size, -1),
            axis=1),
            output,
            mask=tf.expand_dims(
                input=mask,
                axis=1)
        )
        p_repeat = tf.squeeze(
            input=tf.matmul(
                a=p_repeat,
                b=data['source_map']
            ),
            axis=1
        )
        mode_feature, attn, norm_attn = self.mode_attn(
            tf.expand_dims(
                input=state.reshape(batch_size, -1),
                axis=1),
            output,
            output,
            mask=tf.expand_dims(
                input=mask,
                axis=1)
        )

        p_mode = tf.nn.softmax(
            logits=self.mode(
                tf.squeeze(
                    input=mode_feature,
                    axis=1
                )
            ),
            axis=-1
        )

        p = tf.expand_dims(
            input=p_mode[:, 0],
            axis=1
        ) * p_explore + tf.expand_dims(
            input=p_mode[:, 1],
            axis=1
        ) * p_repeat

        return p

    def do_train(self, data):
        scores = self.model(data)
        loss = tf.keras.losses.SparseCategoricalCrossentropy()
        # TODO 0 is not unpadded
        loss = loss(tf.math.log(scores + 1e-8), data["item_tgt"].reshape(-1))
        return loss

    def do_infer(self, data):
        scores = self.model(data)
        scores = tf.sort(
            values=scores,
            axis=-1,
            direction="DESCENDING"
        )
        index = tf.argsort(
            values=scores,
            axis=-1,
            direction="DESCENDING"
        )
        return scores, index

    def call(self, data, training=True):
        data["source_map"] = self.build_map(
            data['item_seq'], max=self.item_vocab_size)
        if training:
            return self.do_train(data)
        else:
            return self.do_infer(data)
