#include <iostream>
#include <list>
#include <map>
#include <string>
#include <unordered_map>

int main() {
    std::list<std::string> keys = {"a", "b", "c"};
    std::map<std::string, int> si_map;
    std::unordered_map<std::string, int> usi_map;
    int i = 0;
    for (auto iter = keys.begin(); iter != keys.end(); iter++) {
        si_map[*iter] = ++i;
        usi_map[*iter] = i;
    }
    std::cout << "map:" << std::endl;
    for (auto iter = si_map.begin(); iter != si_map.end(); iter++)
        std::cout << iter->first << " -> " << iter->second
            << std::endl;
    std::cout << "unordered map:" << std::endl;
    for (auto iter = usi_map.begin(); iter != usi_map.end(); iter++)
        std::cout << iter->first << " -> " << iter->second
            << std::endl;
    return 0;
}
