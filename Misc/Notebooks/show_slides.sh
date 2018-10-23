#!/usr/bin/env bash
module load conda
source activate py36

jupyter nbconvert slides.ipynb --to slides --post serve
