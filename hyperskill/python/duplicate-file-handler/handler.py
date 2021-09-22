import argparse
import sys
import os


class Duplicator:
    def __init__(self):
        self.directory = ""
        self.data = []
        self.ext = ""
        self.way = 0
        self.paths = []
        self.file = {"path": "", "ext": "", "size": ""}
        self.library = []

    def parse(self):
        ways = ("1", "2", "")
        if len(sys.argv) < 2:
            print("Directory is not specified")
            sys.exit(1)
        parser = argparse.ArgumentParser(description="Building file tree")
        parser.add_argument("dir", type=str, help="Main directory to build a tree of folders and files")
        args = parser.parse_args()
        self.directory = args.dir
        self.ext = input("Enter file format:\n")
        print("\nSize sorting options:")
        print("1. Descending")
        print("2. Ascending\n")
        self.way = input("Enter a sorting option:\n")
        while self.way not in ways:
            print("\nWrong option\n")
            self.way = input("Enter a sorting option:\n")

    def build_tree(self):
        for i in os.walk(self.directory):
            self.data.append(i)

    def print_tree(self, show=False):
        for address, dirs, files in self.data:
            for file in files:
                path = address + "\\" + file
                if show:
                    print(path)
                self.paths.append(path)

    def get_file_info(self):
        for path in self.paths:
            self.file.update({"path": path, "ext": os.path.splitext(path)[1][1:], "size": os.path.getsize(path)})
            self.library.append(self.file)
            self.file = {}
        print(self.library)


def main():
    file_handler = Duplicator()
    file_handler.parse()
    file_handler.build_tree()
    file_handler.print_tree()
    file_handler.get_file_info()


if __name__ == "__main__":
    main()
