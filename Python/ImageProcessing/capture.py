#!/usr/bin/env python

from argparse import ArgumentParser
import cv2
import numpy as np

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='capture video')
    arg_parser.add_argument('--dev', type=int, default=0,
                            help='device number to capture')
    arg_parser.add_argument('--input', help='file to read from')
    arg_parser.add_argument('--output', help='file to write to')
    arg_parser.add_argument('--fps', type=float, default=10.0,
                            help='frames per soecond for recording')
    options = arg_parser.parse_args()
    if options.input:
        capture = cv2.VideoCapture(options.input)
    else:
        capture = cv2.VideoCapture(options.dev)
    if options.output:
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        output = cv2.VideoWriter(options.output, fourcc,
                                 options.fps, (640, 480))
    counter = 0
    try:
        while True:
            status, frame = capture.read()
            if status:
                counter += 1
                # frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                if options.output:
                    output.write(frame)
                cv2.imshow('frame', frame)
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
            else:
                break
    except KeyboardInterrupt:
        capture.release()
        if options.output:
            output.release()
        cv2.destroyAllWindows()
        print('captured {0:d} frames'.format(counter))
    else:
        capture.release()
        if options.output:
            output.release()
        cv2.destroyAllWindows()
        print('captured {0:d} frames'.format(counter))
