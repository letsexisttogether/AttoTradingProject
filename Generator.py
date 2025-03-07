import random
import struct


def generate_1gb_txt(filename='output.txt', file_size_gb=1):
    target_size = file_size_gb * 1024 * 1024 * 1024 
    with open(filename, 'w') as f:
        current_size = 0
        while current_size < target_size:
            value = random.uniform(-1e6, 1e6)
            line = f'{value:.15f}\n'
            f.write(line)
            current_size += len(line.encode("utf-8"))


if __name__ == "__main__":
    generate_1gb_txt("big_file.txt", 1)
