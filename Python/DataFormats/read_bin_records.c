#include <err.h>
#include <stdio.h>

#define BUFF_SIZE 8

int main(int argc, char *argv[]) {
    FILE *fp;
    char name[BUFF_SIZE + 1];
    int age;
    if (argc != 2)
        errx(1, "### error: binary file name required as argument");
    if (!(fp = fopen(argv[1], "rb")))
        errx(1, "### error: can't open input file");
    while (!feof(fp)) {
        size_t nr_items = 0;
        nr_items = fread(name, sizeof(char), BUFF_SIZE, fp);
        if (nr_items != BUFF_SIZE)
            break;
        nr_items = fread(&age, sizeof(int), 1, fp);
        if (nr_items != 1) 
            break;
        printf("'%s' %d\n", name, age);
    }
    fclose(fp);
    return 0;
}
