#!/usr/bin/env python

from argparse import ArgumentParser
import cv2
import matplotlib.pyplot as plt
import numpy as np
import sys
import time

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='follow the yellow ball')
    arg_parser.add_argument('input', help='AVI file to use')
    arg_parser.add_argument('--row', type=int, default=340,
                            help='row for ROI')
    arg_parser.add_argument('--col', type=int, default=300,
                            help='dolumn for ROI')
    arg_parser.add_argument('--height', type=int, default=210,
                            help='height for ROI')
    arg_parser.add_argument('--width', type=int, default=230,
                            help='width for ROI')
    arg_parser.add_argument('--min-hue', type=int, default=25,
                            help='minimum hue')
    arg_parser.add_argument('--max-hue', type=int, default=50,
                            help='maximum hue')
    arg_parser.add_argument('--iterations', type=int, default=5,
                            help='number of iterations for tracking')
    arg_parser.add_argument('--output', help='output file name')
    arg_parser.add_argument('--fps', type=float, default=12.0,
                            help='frames per second for output')
    options = arg_parser.parse_args()
    capture = cv2.VideoCapture(options.input)
    status, frame = capture.read()
    if not status:
        capture.release()
        sys.exit(1)
    if options.output:
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        output = cv2.VideoWriter(options.output, fourcc, options.fps,
                                 (frame.shape[1], frame.shape[0]))
    else:
        output = None
                                 
    track_window = (options.col, options.row, options.width, options.height)
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv_frame,
                       np.array((options.min_hue, 50, 50)),
                       np.array((options.max_hue, 255, 255)))
    roi_hist = cv2.calcHist([hsv_frame], [0], mask, [50], [0, 50])
    cv2.normalize(roi_hist, roi_hist, 0, 255, cv2.NORM_MINMAX)
    termination_cond = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT,
                        options.iterations, 1)
    nr_frames = 1
    while True:
        status, frame = capture.read()
        if status == True:
            nr_frames += 1
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
            dst = cv2.calcBackProject([hsv], [0], roi_hist, [0, 50], 1)
            status, track_window = cv2.meanShift(dst, track_window,
                                                 termination_cond)
            if not status:
                continue
            x, y, w, h = track_window
            img = cv2.rectangle(frame, (x, y), (x + w, y + h), 255, 2)
            cv2.imshow('image', img)
            if output:
                output.write(img)
            if cv2.waitKey(1) % 0xFF == ord('q'):
                break
        else:
            break

    print(f'{nr_frames} frames processed')
    cv2.destroyAllWindows()
    if output:
        output.release()
    capture.release()
