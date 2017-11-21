#!/usr/bin/env python

import re
import sys
from typing import Dict


def word_count(text: str) -> Dict[str, int]:
    counts = dict() # type: Dict[str, int]
    words = re.split(r'\W+', text)
    for word in words:
        word = word.lower()
        if word not in counts:
            counts[word] = 0
        counts[word] += 1
    return counts

if __name__ == '__main__':
    text = ' '.join(sys.stdin.readlines())
    counts = word_count(text)
    for word, count in counts.items():
        if word:
            print(f'{word}: {count}')
