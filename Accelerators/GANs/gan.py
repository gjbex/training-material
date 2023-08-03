#!/usr/bin/env python

from argparse import ArgumentParser
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import numpy as np
from skimage.io import imsave
import os
import shutil


img_height = 28
img_width = 28
img_size = img_height * img_width

h1_size = 150
h2_size = 300
z_size = 100
batch_size = 256

def generate_prior(rows, cols):
    return np.random.normal(0, 1, size=(rows, cols)).astype(np.float32)


def build_generator(z_prior):
    w1 = tf.Variable(tf.truncated_normal([z_size, h1_size], stddev=0.1),
                     name="g_w1", dtype=tf.float32)
    b1 = tf.Variable(tf.zeros([h1_size]), name="g_b1", dtype=tf.float32)
    h1 = tf.nn.relu(tf.matmul(z_prior, w1) + b1)
    w2 = tf.Variable(tf.truncated_normal([h1_size, h2_size], stddev=0.1),
                     name="g_w2", dtype=tf.float32)
    b2 = tf.Variable(tf.zeros([h2_size]), name="g_b2", dtype=tf.float32)
    h2 = tf.nn.relu(tf.matmul(h1, w2) + b2)
    w3 = tf.Variable(tf.truncated_normal([h2_size, img_size], stddev=0.1),
                     name="g_w3", dtype=tf.float32)
    b3 = tf.Variable(tf.zeros([img_size]), name="g_b3", dtype=tf.float32)
    h3 = tf.matmul(h2, w3) + b3
    x_generate = tf.nn.tanh(h3)
    g_params = [w1, b1, w2, b2, w3, b3]
    return x_generate, g_params


def build_discriminator(x_data, x_generated, keep_prob):
    x_in = tf.concat([x_data, x_generated], 0)
    w1 = tf.Variable(tf.truncated_normal([img_size, h2_size], stddev=0.1),
                     name="d_w1", dtype=tf.float32)
    b1 = tf.Variable(tf.zeros([h2_size]), name="d_b1", dtype=tf.float32)
    h1 = tf.nn.dropout(tf.nn.relu(tf.matmul(x_in, w1) + b1), keep_prob)
    w2 = tf.Variable(tf.truncated_normal([h2_size, h1_size], stddev=0.1),
                     name="d_w2", dtype=tf.float32)
    b2 = tf.Variable(tf.zeros([h1_size]), name="d_b2", dtype=tf.float32)
    h2 = tf.nn.dropout(tf.nn.relu(tf.matmul(h1, w2) + b2), keep_prob)
    w3 = tf.Variable(tf.truncated_normal([h1_size, 1], stddev=0.1),
                     name="d_w3", dtype=tf.float32)
    b3 = tf.Variable(tf.zeros([1]), name="d_b3", dtype=tf.float32)
    h3 = tf.matmul(h2, w3) + b3
    y_data = tf.nn.sigmoid(tf.slice(h3, [0, 0], [batch_size, -1],
                           name=None))
    y_generated = tf.nn.sigmoid(tf.slice(h3, [batch_size, 0], [-1, -1],
                                name=None))
    d_params = [w1, b1, w2, b2, w3, b3]
    return y_data, y_generated, d_params


def show_result(batch_res, fname, grid_size=(8, 8), grid_pad=5):
    batch_res = 0.5 * batch_res.reshape((batch_res.shape[0], img_height, img_width)) + 0.5
    img_h, img_w = batch_res.shape[1], batch_res.shape[2]
    grid_h = img_h * grid_size[0] + grid_pad * (grid_size[0] - 1)
    grid_w = img_w * grid_size[1] + grid_pad * (grid_size[1] - 1)
    img_grid = np.zeros((grid_h, grid_w), dtype=np.uint8)
    for i, res in enumerate(batch_res):
        if i >= grid_size[0] * grid_size[1]:
            break
        img = (res) * 255
        img = img.astype(np.uint8)
        row = int(i // grid_size[0]) * (img_h + grid_pad)
        col = (i % grid_size[1]) * (img_w + grid_pad)
        img_grid[row:row + img_h, col:col + img_w] = img
    imsave(fname, img_grid)


def train(output_path, max_epoch, to_restore):
    mnist = input_data.read_data_sets('MNIST_data', one_hot=True)

    x_data = tf.placeholder(tf.float32, [batch_size, img_size],
                            name="x_data")
    z_prior = tf.placeholder(tf.float32, [batch_size, z_size],
                             name="z_prior")
    keep_prob = tf.placeholder(tf.float32, name="keep_prob")
    global_step = tf.Variable(0, name="global_step", trainable=False)

    x_generated, g_params = build_generator(z_prior)
    y_data, y_generated, d_params = build_discriminator(x_data,
                                                        x_generated,
                                                        keep_prob)

    d_loss = - (tf.log(y_data) + tf.log(1 - y_generated))
    g_loss = - tf.log(y_generated)

    optimizer = tf.train.AdamOptimizer(0.0001)

    d_trainer = optimizer.minimize(d_loss, var_list=d_params)
    g_trainer = optimizer.minimize(g_loss, var_list=g_params)

    init = tf.global_variables_initializer()

    saver = tf.train.Saver()

    with tf.Session() as sess:
        sess.run(init)

        if to_restore:
            chkpt_fname = tf.train.latest_checkpoint(output_path)
            saver.restore(sess, chkpt_fname)
        else:
            if os.path.exists(output_path):
                shutil.rmtree(output_path)
            os.mkdir(output_path)


        z_sample_val = generate_prior(batch_size, z_size)

        for i in range(sess.run(global_step), max_epoch):
            for j in range(int(60000 // batch_size)):
                print(f"epoch:{i}, iter:{j}")
                x_value, _ = mnist.train.next_batch(batch_size)
                x_value = 2 * x_value.astype(np.float32) - 1
                z_value = generate_prior(batch_size, z_size)
                sess.run(d_trainer,
                         feed_dict={x_data: x_value,
                                    z_prior: z_value,
                                    keep_prob: np.sum(0.7).astype(np.float32)})
                sess.run(g_trainer,
                         feed_dict={x_data: x_value,
                                    z_prior: z_value,
                                    keep_prob: np.sum(0.7).astype(np.float32)})
            x_gen_val = sess.run(x_generated, feed_dict={z_prior: z_sample_val})
            if i % 50 == 0:
                file_path = os.path.join(output_path,
                                         'sample{0:04d}.jpg'.format(i))
                show_result(x_gen_val, file_path)
            z_random_sample_val = generate_prior(batch_size, z_size)
            x_gen_val = sess.run(x_generated,
                                 feed_dict={z_prior: z_random_sample_val})
            if i % 50 == 0:
                file_path = os.path.join(output_path,
                                         'random_sample{0:04d}.jpg'.format(i))
                show_result(x_gen_val, file_path)
            sess.run(tf.assign(global_step, i + 1))
            if (i + 1) % 100 == 0:
                saver.save(sess, os.path.join(output_path, "model"),
                           global_step=global_step)


def test(output_path):
    z_prior = tf.placeholder(tf.float32, [batch_size, z_size], name="z_prior")
    x_generated, _ = build_generator(z_prior)
    chkpt_fname = tf.train.latest_checkpoint(output_path)

    init = tf.global_variables_initializer()
    sess = tf.Session()
    saver = tf.train.Saver()
    sess.run(init)
    saver.restore(sess, chkpt_fname)
    z_test_value = generate_prior(batch_size, z_size)
    x_gen_val = sess.run(x_generated, feed_dict={z_prior: z_test_value})
    file_path = os.path.join(output_path, 'test_result.jpg')
    show_result(x_gen_val, file_path)


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='train and test GAN on '
                                            'MNIST data')
    arg_parser.add_argument('--train', action='store_true',
                            help='train GANs')
    arg_parser.add_argument('--output', required=True,
                            help='directory to store output in')
    arg_parser.add_argument('--max-epoch', type=int, default=500,
                            help='number of training epochs')
    arg_parser.add_argument('--to-restore', action='store_true',
                            help='restore from checkpoint')
    options = arg_parser.parse_args()
    if options.train:
        train(options.output, options.max_epoch, options.to_restore)
    else:
        test(options.output)
