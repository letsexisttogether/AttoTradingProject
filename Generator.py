import random
import struct


def generate_1gb_txt(filename="output.txt", file_size_gb=1):
    target_size = file_size_gb * 1024 * 1024 * 1024  # Convert GB to bytes
    with open(filename, "w") as f:
        current_size = 0
        while current_size < target_size:
            value = random.uniform(-1e6, 1e6)  # Generate a random double
            line = f"{value:.15f}\n"  # Format to 15 decimal places
            f.write(line)
            current_size += len(line.encode("utf-8"))


if __name__ == "__main__":
    generate_1gb_txt("file.txt", 0.1)
