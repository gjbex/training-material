#include <iostream>
#include <unordered_map>

using namespace std;

int main(void) {
    string col1, col2, col3;
    cin >> col1 >> col2 >> col3;
    int id, dim_nr;
    double temp;
    unordered_map<int, int> dim_nr_counts;
    while (cin >> id >> dim_nr >> temp)
        dim_nr_counts[dim_nr]++;
    for (auto dim_nr: dim_nr_counts)
        cout << dim_nr.first << ": " << dim_nr.second << endl;
    return 0;
}

