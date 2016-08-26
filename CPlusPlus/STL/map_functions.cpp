#include <iostream>
#include <map>
#include <list>
#include <unordered_map>

typedef std::map<std::string, int> Map;
typedef std::list<std::string> List;

template <typename Map_type>
void fill_map(Map_type& map, const List& list);

template <typename Map_type>
void print_map(const Map_type& map, std::string label);

int main(int argc, char *argv[]) {
    std::list<std::string> keys = {"a", "b", "c"};
    Map si_map;
    std::unordered_map<std::string, int> usi_map;
    fill_map(si_map, keys);
    fill_map(usi_map, keys);
    print_map(si_map, "map");
    print_map(usi_map, "unordered_map");
    return 0;
}

template <typename Map_type>
void fill_map(Map_type& map, const List& list) {
    int i = 0;
    for (auto iter = list.cbegin(); iter != list.cend(); iter++)
        map[*iter] = ++i;
}

template <typename Map_type>
void print_map(const Map_type& map, std::string label) {
    std::cout << label << ":" << std::endl;
    for (auto iter = map.begin(); iter != map.end(); iter++)
        std::cout << iter->first << " -> " << iter->second
            << std::endl;
}
