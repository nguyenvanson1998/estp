import os

from commons import process_file


if __name__ == '__main__':
    with open('output/table2.txt', 'w') as f_out:
        data_path = 'data/OR-LIBRARY'
        for file in sorted(os.listdir(data_path)):
            if 'opt' not in file:
                process_file(os.path.join(data_path, file), file[6:-4], f_out, 10)
