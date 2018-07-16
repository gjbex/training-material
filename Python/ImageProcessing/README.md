# ImageProcessing
Some sample code for image processing using Scikit-Image and video
processing with OpenCV.

## What is it?
1. `denoise.py`: sharpen an image using deconvolution.
1. `segmentation.py`: segmentation using an active cotour model, aka,
    snake.
1. `restoration.ipynb`: Jupyter notebook illustrating analysis of a
    problematic camera image and custum restoration.
1. `Data`: directory containing image files for illustration purposes.
1. `caputure.py`: capture video from a webcam using OpenCV.
1. `analyze.py`: show a plot of the average RGB values for the frames in
    a movie using OpenCV.
1. `split_scenes.py`: very naive utility to split a movie into scences,
    based on rapid changes in RGB intenisty.
1. `bouncing_ball_full.avi`: movie to test `scene_spliiter.py` with.
1. `follow_ball.py`: example of using the camshift algorithm to follow
    a bouncing ball in a scene.
1. `bouncing_ball.avi`: movie to test `follow_ball.py` with.
