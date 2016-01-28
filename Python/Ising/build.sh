#!/bin/bash

export PKG_CONFIG_PATH="/home/lucg5005/miniconda/envs/py3k/lib/pkgconfig:${PKG_CONFIG_PATH}"
cd src
make clean all
make deploy
