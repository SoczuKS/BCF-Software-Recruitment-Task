from essential_generators import DocumentGenerator
import pathlib
import randomfiletree
import random
import threading

gen = DocumentGenerator()


def process_directory(path):
    for path in path.iterdir():
        if path.is_dir():
            thread = threading.Thread(target=process_directory, args=(path,))
            thread.start()
        elif path.is_file():
            thread = threading.Thread(target=fill_file, args=(path,))
            thread.start()


def fill_file(path):
    with path.open('w') as file:
        file_content = ""
        num_lines = random.randint(1, 5)

        for i in range(num_lines):
            file_content += gen.paragraph(max_sentences=5)
            file_content += "\n"

        print(file_content, file=file)


def main():
    directory = "./sample_directories"

    randomfiletree.iterative_gaussian_tree(
        directory,
        nfolders=4,
        maxdepth=5,
        repeat=5,
        filename=lambda: gen.word(True) + ".txt"
    )

    process_directory(pathlib.Path(directory))


main()
