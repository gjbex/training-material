#!/usr/bin/env python

from argparse import ArgumentParser
import cv2
import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='capture video')
    arg_parser.add_argument('input', help='file to read from')
    options = arg_parser.parse_args()
    capture = cv2.VideoCapture(options.input)
    counter = 0
    try:
        densities = []
        while (True):
            status, frame = capture.read()
            if status:
                counter += 1
                nr_pixels = frame.shape[0]*frame.shape[1]
                red_channel = frame[:, :, 0]
                green_channel = frame[:, :, 1]
                blue_channel = frame[:, :, 2]
                densities.append((counter,
                                  red_channel.sum()/nr_pixels,
                                  green_channel.sum()/nr_pixels,
                                  blue_channel.sum()/nr_pixels))
                cv2.imshow('frame', frame)
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
            else:
                break
        capture.release()
        cv2.destroyAllWindows()
        densities = np.array(densities).T
        plt.plot(densities[0], densities[1], 'r')
        plt.plot(densities[0], densities[2], 'g')
        plt.plot(densities[0], densities[3], 'b')
        plt.xlabel('frame')
        plt.ylabel('RGB')
        plt.ylim((0, 255))
        plt.show()
    except KeyboardInterrupt:
        capture.release()
        cv2.destroyAllWindows()
