#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LEN 80

typedef struct {
    int a, c, g, t;
} NucleotideCounts;

void reset_counts(NucleotideCounts *counts);
void update_counts(NucleotideCounts *counts, char *sequence);
void print_counts(NucleotideCounts counts);

int  main(int argc, char *argv[]) {
    if (argc != 2)
        errx(1, "no file name given");
    FILE *fp;
    if (!(fp = fopen(argv[1], "r")))
        err(2, "can't open file '%s'", argv[1]);
    char *line_ptr = NULL;
    size_t nr_chars = 0;
    char current_id[MAX_ID_LEN] = "", next_id[MAX_ID_LEN] = "";
    NucleotideCounts counts;
    while (getline(&line_ptr, &nr_chars, fp) != -1) {
        int nr_assigned = sscanf(line_ptr, "> %s", next_id);
        if (nr_assigned == 1) {
            if (strlen(current_id) > 0) {
                printf("%s: ", current_id);
                print_counts(counts);
            }
            strncpy(current_id, next_id, MAX_ID_LEN);
            reset_counts(&counts);
        } else if (nr_chars > 0) {
            update_counts(&counts, line_ptr);
        }
    }
    free(line_ptr);
    fclose(fp);
    return 0;
}

void reset_counts(NucleotideCounts *counts) {
    counts->a = counts->c = counts->g = counts->t = 0;
}

void update_counts(NucleotideCounts *counts, char *sequence) {
    for (char *nucl = sequence; *nucl != '\0'; nucl++)
        switch (*nucl) {
            case 'A':
                counts->a++;
                break;
            case 'C':
                counts->c++;
                break;
            case 'G':
                counts->g++;
                break;
            case 'T':
                counts->t++;
                break;
            case '\n':
                break;
            case '\r':
                break;
            default:
                warnx("invalid nucleotide symbol '%c'", *nucl);
        }
}

void print_counts(NucleotideCounts counts) {
    printf("A: %d, C = %d, G = %d, T = %d\n",
           counts.a, counts.c, counts.g, counts.t);
}
