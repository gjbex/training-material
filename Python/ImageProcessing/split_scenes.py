#!/usr/bin/env python

from argparse import ArgumentParser
import cv2
import matplotlib.pyplot as plt
import numpy as np
import os.path

def avg_rgb(frame):
    nr_pixels = frame.shape[0]*frame.shape[1]
    red_channel = frame[:, :, 0].sum()/nr_pixels
    green_channel = frame[:, :, 1].sum()/nr_pixels
    blue_channel = frame[:, :, 2].sum()/nr_pixels
    return np.array((red_channel, green_channel, blue_channel))


def is_new_scene(prev_rgb, rgb, threshold):
    diff = np.abs(rgb - prev_rgb)
    return np.any(diff > threshold)


def write_movie(base_name, extension, scene_nr, frames, fps):
    file_name = f'{base_name}_{scene_nr:03d}{extension}'
    size = (frames[0].shape[1], frames[0].shape[0])
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    output = cv2.VideoWriter(file_name, fourcc, fps, size)
    for frame in frames:
        output.write(frame)
    output.release()

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='capture video')
    arg_parser.add_argument('input', help='file to read from')
    arg_parser.add_argument('--threshold', type=float, default=10,
                            help='threshold to use to distinguish scenes')
    arg_parser.add_argument('--fps', type=float, default=10.0,
                            help='frames per second for movies')
    arg_parser.add_argument('--min-frames', type=int, default=20,
                            help='minimum number of frames in  scene')
    options = arg_parser.parse_args()
    base_name, extension = os.path.splitext(options.input)
    capture = cv2.VideoCapture(options.input)
    counter = 0
    try:
        status, frame = capture.read()
        if status:
            frames = [frame]
            counter += 1
            prev_rgb = avg_rgb(frame)
            scene_nr = 1
            saved_scenes = 0
            while True:
                status, frame = capture.read()
                if not status:
                    break
                counter += 1
                cv2.imshow('frame', frame)
                rgb = avg_rgb(frame)
                if is_new_scene(prev_rgb, rgb, options.threshold):
                    if len(frames) >= options.min_frames:
                        saved_scenes += 1
                        write_movie(base_name, extension, saved_scenes,
                                    frames, options.fps)
                    print(f'scene {scene_nr}: {len(frames)} frames')
                    scene_nr += 1
                    counter = 1
                    frames = [frame]
                else:
                    frames.append(frame)
                prev_rgb = rgb
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
            if frames:
                if len(frames) >= options.min_frames:
                    saved_scenes += 1
                    write_movie(base_name, extension, saved_scenes,
                                frames, options.fps)
                print(f'scene {scene_nr}: {counter} frames')
            capture.release()
            cv2.destroyAllWindows()
    except KeyboardInterrupt:
        capture.release()
        cv2.destroyAllWindows()
