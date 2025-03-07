import argparse


def is_file_sorted(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            first_line = file.readline().strip()
            
            try:
                prev_value = float(first_line)
            except ValueError:
                print(f'[Error] "{first_line}" is not a valid number')
                return False

            for line in file:
                line = line.strip()
                
                try:
                    current_value = float(line)
                except ValueError:
                    print(f'[Error] "{line}" is not a valid number')
                    return False

                if prev_value > current_value:
                    return False

                prev_value = current_value

        return True

    except Exception as e:
        print(f'[Error] {e}')

        return False  


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('file')
    
    args = parser.parse_args()
    
    if is_file_sorted(args.file):
        print('[Success] The file is sorted')
    else:
        print('[Failure] The file is NOT sorted')
