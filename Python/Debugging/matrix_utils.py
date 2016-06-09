def print_matrix(matrix):
    fmt_elem = lambda elem: '{:2d}'.format(elem)
    print('\n'.join(' '.join(fmt_elem(e) for e in row) for row in matrix))
