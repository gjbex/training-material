#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v1 {1, 3, 5, 7};
    vector<int> v2 {2, 4, 8, 10};
    vector<int> v3(4, 0);
    transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(),
              [] (int x, int y) { return x + y; });
    for (const auto& x: v1)
        cout << x << " ";
    cout << endl;
    for (const auto& x: v2)
        cout << x << " ";
    cout << endl;
    for (const auto& x: v3)
        cout << x << " ";
    cout << endl;
    return 0;
}
