import tensorflow as tf
from tensorflow.keras import layers


class BilinearAttention(layers.Layer):
    def __init__(self,
                 query_size,
                 key_size,
                 hidden_size,
                 trainable=True,
                 name=None,
                 dtype=None,
                 dynamic=False,
                 **kwargs
                 ):
        # super().__init__(trainable=trainable, name=name, dtype=dtype, dynamic=dynamic, **kwargs)
        super().__init__()
        self.linear_key = layers.Dense(
            units=hidden_size,
            input_shape=(key_size,),
            activation=None,
            use_bias=False
        )
        self.linear_query = layers.Dense(
            units=hidden_size,
            input_shape=(query_size,),
            activation=None,
            use_bias=True
        )
        self.v = layers.Dense(
            units=1,
            input_shape=(hidden_size,),
            activation=None,
            use_bias=False
        )
        self.hidden_size = hidden_size

    def matching(self, query, key, mask=None):
        wq = self.linear_query(query)
        wq = tf.expand_dims(
            input=wq,
            axis=-2
        )

        uh = self.linear_key(key)
        uh = tf.expand_dims(
            input=uh,
            axis=-3
        )

        wuc = wq + uh

        wquh = tf.math.tanh(x=wuc)

        attn = tf.squeeze(
            input=self.v(wquh),
            axis=-1
        )

        if mask is not None:
            attn = self.mask_fill(attn, ~mask, -float('inf'))

        return attn

    def score(self, query, key, softmax_dim=-1, mask=None):
        attn = self.matching(query, key, mask)

        norm_attn = tf.nn.softmax(
            logits=attn,
            axis=softmax_dim
        )

        if mask is not None:
            norm_attn = self.mask_fill(norm_attn, ~mask, 0)

        return attn, norm_attn

    @staticmethod
    def mask_fill(matrix, mask, fill):
        negmask = 1 - mask
        # num = 3.4 * math.pow(10, 38)
        return (matrix * mask) + (-((negmask * fill + fill) - fill))

    def call(self, query, key, value, mask=None):
        attn, norm_attn = self.score(query, key, mask=mask)
        h = tf.matmul(
            a=norm_attn.reshape(-1, norm_attn.get_shape(-2),
                                norm_attn.get_shape(-1)),
            b=value.reshape(-1, value.get_shape(-2), value.get_shape(-1))
        )

        return h.reshape(list(value.get_shape())[:-2] + [norm_attn.get_shape(-2), -1]), attn, norm_attn
