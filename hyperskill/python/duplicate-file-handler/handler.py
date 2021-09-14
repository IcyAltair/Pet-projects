import argparse
import sys
import os


class Duplicator:
    def __init__(self):
        self.directory = ""
        self.data = []

    def parse(self):
        if len(sys.argv) < 2:
            print("Directory is not specified")
            sys.exit(1)
        parser = argparse.ArgumentParser(description="Building file tree")
        parser.add_argument("dir", type=str, help="Main directory to build a tree of folders and files")
        args = parser.parse_args()
        self.directory = args.dir

    def build_tree(self):
        for i in os.walk(self.directory):
            self.data.append(i)

    def print_tree(self):
        for address, dirs, files in self.data:
            for file in files:
                print(address + '/' + file)


def main():
    file_handler = Duplicator()
    file_handler.parse()
    file_handler.build_tree()
    file_handler.print_tree()


if __name__ == "__main__":
    main()
