import random
import struct
import argparse


def generate_file_with_double(filename, file_size_gb):
    target_size = file_size_gb * 1024 * 1024 * 1024 
    with open(filename, 'w') as f:
        current_size = 0
        while current_size < target_size:
            value = random.uniform(-1e6, 1e6)

            line = f'{value:.13f}\n'
            f.write(line)

            current_size += len(line.encode('utf-8'))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('file', type=str, default='Input.txt')
    parser.add_argument('size', type=float, default=1)
    
    args = parser.parse_args()

    file_name = args.file 
    size = args.size

    generate_file_with_double(args.file, args.size)
