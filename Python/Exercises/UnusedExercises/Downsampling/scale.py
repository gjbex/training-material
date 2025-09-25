#!/usr/bin/env python

import struct
import sys


def read_info(img_file):
    info = b''
    byte = img_file.read(1)
    while byte and not byte.isspace():
        info += byte
        byte = img_file.read(1)
    return info.decode('utf-8')


def get_properties(img_file):
    prop = {'type': read_info(img_file)}
    prop['width'] = int(read_info(img_file))
    prop['height'] = int(read_info(img_file))
    return prop


def get_image(img_file, width, height):
    img = [[0] * width for _ in range(height)]
    bytes = width//8
    if width % 8 != 0:
        bytes += 1
    for i in range(height):
        for j in range(bytes):
            byte = struct.unpack('B', img_file.read(1))[0]
            mask = 1 << 7
            for k in range(8):
                if byte & mask != 0:
                    img[i][j*8 + k] = 1
                mask = mask >> 1
            if byte % 2 == 1:
                if img[i][j*8 + 7] != 1:
                    print('oops')
    return img


def compute_black_fraction(img):
    nr_blacks = sum(sum(row) for row in img)
    return nr_blacks/(len(img)*len(img[0]))


def write_image(img_file, img):
    height = len(img)
    width = len(img[0])
    bytes = width//8
    if width % 8 != 0:
        bytes += 1
    img_file.write(b'P4\n')
    img_file.write(str(width).encode(encoding='utf-8'))
    img_file.write(b' ')
    img_file.write(str(height).encode(encoding='utf-8'))
    img_file.write(b'\n')
    for row in img:
        for j in range(bytes):
            bits = row[j*8:(j + 1)*8]
            byte = 0
            mask = 1 << 7
            for bit in bits:
                if bit == 1:
                    byte = byte | mask
                mask = mask >> 1
            byte = struct.pack('B', byte)
            img_file.write(byte)


def scale_image(img, threshold=2):
    width = len(img[0])
    height = len(img)
    new_width = width//2
    new_height = height//2
    new_img = [[0] * new_width for _ in range(new_height)]
    for i in range(new_height):
        for j in range(new_width):
            avg = (img[2*i][2*j] + img[2*i][2*j + 1] +
                   img[2*i + 1][j] + img[2*i + 1][2*j + 1])
            if avg >= threshold:
                new_img[i][j] = 1
    return new_img


def main():
    if len(sys.argv) > 2:
        in_file_name = sys.argv[1]
        out_file_name = sys.argv[2]
    else:
        sys.stderr.write('### error: no files given\n')
        return 1
    with open(in_file_name, 'rb') as img_file:
        prop = get_properties(img_file)
        img = get_image(img_file, prop['width'], prop['height'])
        new_img = scale_image(img, 2)
        with open(out_file_name, 'wb') as img_out:
            write_image(img_out, new_img)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
