import os

from commons import process_file


if __name__ == '__main__':
    with open('output/table3.txt', 'w') as f_out:
        process_file('data/estein10_3D.txt', '3D', f_out, 20)
        process_file('data/estein10_4D.txt', '4D', f_out, 20)
        process_file('data/estein10_5D.txt', '5D', f_out, 20)