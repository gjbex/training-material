#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v {{1, 3, 7, 14}};
    for (auto target: {2, 4, 9, 18}) {
        auto it = find_if(v.cbegin(), v.cend(),
                          [target] (int x) { return x > target; });
        if (it != v.cend())
            cout << "found " << *it << " > " << target << endl;
        else
            cout << "no element > " << target << endl;
    }
    return 0;
}
