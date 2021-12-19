import codecs
import csv
import tensorflow as tf
from tensorflow.keras import layers


class RepeatNetPreprocessing():
    def __init__(self, source):
        self.source = source

        self.item_atts = dict()
        self.samples = []
        self.load()

    def load(self):
        def clean(l): return [int(x) for x in l.strip('[]').split(',')]

        count = 0
        with codecs.open(self.source, encoding="utf-8") as f:
            csv_reader = csv.reader(f, delimiter="|")
            for row in csv_reader:
                count += 1
                self.samples.append([tf.convert_to_tensor([count]), tf.convert_to_tensor(
                    clean(row[0])), tf.convert_to_tensor(clean(row[1]))])

    def __getitem__(self, index):
        return self.samples[index]

    def __len__(self):
        return len(self.samples)

    @staticmethod
    def collate_fn(data):
        count, item_seq, item_tgt = zip(*data)

        return {
            'id': layers.Concatenate(axis=-1)(count),
            'item_seq': tf.stack(item_seq),
            'item_tgt': tf.stack(item_tgt)
        }
