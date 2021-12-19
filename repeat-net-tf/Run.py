import argparse
import codecs
import numpy as np
import os
import sys
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

from Model import RepeatNet as rn
from Preprocess import RepeatNetPreprocessing as rnp


class RunRepeatNet():
    def __init__(self):
        self.parser = argparse.ArgumentParser()
        self.parser.add_argument("-eps", "--epoches", type=int, default=10,
                                 help="Set quantity of epochs")
        self.parser.add_argument("-embs", "--embedding_size", type=int, default=16,
                                 help="Set size of embedding")
        self.parser.add_argument("-hds", "--hidden_size", type=int, default=16,
                                 help="Set size of hidden")
        self.parser.add_argument("-ivs", "--item_vocab_size", type=int, default=11,
                                 help="Set size of items' vocabulary")
        self.parser.add_argument("-m", "--mode", type=str, default="train",
                                 help="Set mode for model execution")
        self.args = self.parser.parse_args()
        self.train, self.test, self.valid = None, None, None
        self.train_size = 0
        self.data_directory = os.path.abspath(os.getcwd()) + "/data/"
        self.output_directory = os.path.abspath(os.getcwd()) + "/output/"

    def get_data(self):
        self.train = rnp(self.data_directory + "demo.train")
        self.test = rnp(self.data_directory + "demo.test")
        self.valid = rnp(self.data_directory + "demo.valid")
        self.train_size = len(self.train)

    def training(self):
        model = rn(embedding_size=self.args.embedding_size,
                   hidden_size=self.args.hidden_size,
                   item_vocab_size=self.args.item_vocab_size)

    def infering(self):
        pass

    def execute(self):
        self.get_data()
        if self.args.mode == "train":
            self.training()
        elif self.args.mode == "infer":
            self.infering()
        else:
            print("Unsupported execution mode")
            sys.exit(1)


def main():
    print("TensorFlow version: {}".format(tf.__version__))
    print("Eager execution: {}".format(tf.executing_eagerly()))
    print("Starting RepeatNet model execution...")
    executor = RunRepeatNet()
    executor.execute()


if __name__ == "__main__":
    main()
