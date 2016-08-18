#include <iostream>
#include <list>
#include <map>
#include <string>

int main(int argc, char *argv[]) {
    std::list<std::string> keys = {"a", "b", "c"};
    std::map<std::string, int> si_map;
    int i = 0;
    for (auto iter = keys.begin(); iter != keys.end(); iter++)
        si_map[*iter] = ++i;
    for (auto iter = si_map.begin(); iter != si_map.end(); iter++)
        std::cout << iter->first << " -> " << iter->second
            << std::endl;
    return 0;
}
