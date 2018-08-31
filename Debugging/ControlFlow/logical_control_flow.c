#include <stdio.h>

int main(int argc, char *argv[]) {
    char *file_name = argc > 1 ? argv[1] : "";
    FILE *fp;
    (fp = fopen(file_name, "w")) || (fp = stdout);
    fprintf(fp, "hello");
    fp == stdout || fclose(fp);
    return 0;
}
