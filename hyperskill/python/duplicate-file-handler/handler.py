import argparse


class Duplicator:
    def __init__(self):
        self.directory = ""

    def parse(self):
        parser = argparse.ArgumentParser(description="Building file tree")
        parser.add_argument("dir", type=str, help="Main directory to build a tree of folders and files")
        args = parser.parse_args()
        self.directory = args.dir


def main():
    file_handler = Duplicator()
    file_handler.parse()


if __name__ == "__main__":
    main()
