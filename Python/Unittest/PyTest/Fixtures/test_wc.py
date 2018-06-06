from pathlib import Path
import pytest
from subprocess import check_output

@pytest.fixture(scope='module')
def text_file():
    file_path = Path('my_text.txt')
    with open(file_path, 'w') as out_file:
        for line_nr in range(1, 11):
            for word_nr in range(1, line_nr + 1):
                print('bla', file=out_file, end=' ')
            print('', file=out_file)
    yield file_path
    file_path.unlink()

def test_wc_l(text_file):
    output = check_output(['wc', '-l', text_file])
    nr_lines = 10
    lines, _ = output.decode(encoding='utf-8').split()
    assert int(lines) == nr_lines

def test_wc_w(text_file):
    output = check_output(['wc', '-w', text_file])
    nr_lines = 10
    nr_words = 0
    for words in range(1, nr_lines + 1):
        nr_words += words
    lines, _ = output.decode(encoding='utf-8').split()
    assert int(lines) == nr_words
