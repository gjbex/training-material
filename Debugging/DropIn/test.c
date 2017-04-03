#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen("test.txt", "w");
    fprintf(fp, "hello from %s and %s!\n", argv[0], "gjb");
    fclose(fp);
    return 0;
}
