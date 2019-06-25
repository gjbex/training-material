#!/usr/bin/env bash

module load conda
source activate spacy

python -m spacy download en_core_web_sm
python -m spacy download en_core_web_md
python -m spacy download nl_core_news_sm
