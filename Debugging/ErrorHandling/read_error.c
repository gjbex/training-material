#include <err.h>
#include <stdio.h>
#include <string.h>

#define ARG_ERR 1
#define FILE_OPEN_ERR 2
#define VALUE_ERR 3

typedef struct {
    double x, y, z;
} Point;

int main(int argc, char *argv[]) {
    if (argc == 1)
        errx(ARG_ERR, "no file name specified");
    FILE *fp;
    int nr_read;
    int line_nr = 0;
    char name[20];
    double value;
    Point point;
    if (!(fp = fopen(argv[1], "r")))
        err(FILE_OPEN_ERR, "can't open file '%s' for reading", argv[1]);
    while ((nr_read = fscanf(fp, "%s = %lf", name, &value)) != -1) {
        line_nr++;
        if (nr_read != 2)
            errx(VALUE_ERR, "invalid input on line %d of %s\n",
                 line_nr, argv[1]);
        if (!strcmp("x", name))
            point.x = value;
        else if (!strcmp("y", name))
            point.y = value;
        else if (!strcmp("z", name))
            point.z = value;
        else
            errx(VALUE_ERR, "invalid name '%s'", name);
    }
    fclose(fp);
    printf("x = %lf, y = %lf, z = %lf\n", point.x, point.y, point.z);
    return 0;
}
