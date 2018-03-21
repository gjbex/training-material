#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double value;
} Record;

Record make_record(double value);

int main() {
    const int n = 5;
    int i;
    double v = 0.2;
    for (i = 0; i < n; i++) {
        Record record = make_record(v);
        printf("id %d: value %lf\n", record.id, record.value);
        v += 0.23;
    }
    return EXIT_SUCCESS;
}

static int _global_id = 0;

Record make_record(double value) {
    int _global_id = 0;
    Record record = {
        .id = ++_global_id,
        .value = value
    };
    return record;
}
