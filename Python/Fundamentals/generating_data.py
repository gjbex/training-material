#!/usr/bin/env python

def main():
    print('case', 'condition', 'temperature')
    case_nr = 0
    for cond_nr in range(1, 4):
        for temp in [0.5*t for t in range(-1, 2)]:
            case_nr += 1
            print(case_nr, cond_nr, temp)

if __name__ == '__main__':
    main()

