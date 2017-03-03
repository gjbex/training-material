#include <iostream>
#include <unordered_set>

using namespace std;

int main(void) {
    string col1, col2, col3;
    cin >> col1 >> col2 >> col3;
    int id, dim_nr;
    double temp;
    unordered_set<int> dim_nrs;
    while (cin >> id >> dim_nr >> temp)
        dim_nrs.insert(dim_nr);
    for (auto dim_nr: dim_nrs)
        cout << dim_nr << endl;
    return 0;
}
