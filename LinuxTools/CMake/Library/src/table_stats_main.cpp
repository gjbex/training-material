#include <iostream>
#include <sstream>

#include "table_stats.h"

NameList parse_names(const std::string& line);
void parse_values(const std::string& line, std::vector<double>& values);

int main() {
    std::string line;
    if (std::getline(std::cin, line)) {
        NameList name_list {parse_names(line)};
        TableStats table_stats(name_list);
        std::vector<double> values(name_list.size());
        while (std::getline(std::cin, line)) {
            try {
                parse_values(line, values);
            } catch (std::out_of_range& e) {
                std::cerr << "### error: " << e.what() << std::endl;
                std::exit(1);
            }
            table_stats.add(values);
        }
        const NameList* names = table_stats.names();
        const StatsList* stats = table_stats.stats();
        try {
            for (size_t i = 0; i < names->size(); ++i) {
                std::cout << (*names)[i] << ":\n";
                std::cout << "\t" << "mean: " << (*stats)[i].mean() << "\n";
                std::cout << "\t" << "mean: " << (*stats)[i].mean() << "\n";
                std::cout << "\t" << "stddev: " << (*stats)[i].stddev() << "\n";
                std::cout << "\t" << "min: " << (*stats)[i].min() << "\n";
                std::cout << "\t" << "max: " << (*stats)[i].max() << "\n";
                std::cout << "\t" << "median: " << (*stats)[i].median() << "\n";
                std::cout << "\t" << "n: " << (*stats)[i].nr_values() << std::endl;
            }
        } catch (std::out_of_range& e) {
            std::cerr << "### error: " << e.what() << std::endl;
            std::exit(2);
        }
    }
    return 0;
}

NameList parse_names(const std::string& line) {
    std::stringstream stream(line);
    NameList names;
    std::string name;
    while (stream >> name)
        names.push_back(name);
    return names;
}

void parse_values(const std::string& line, std::vector<double>& values) {
    std::stringstream stream(line);
    double value;
    for (size_t i = 0; i < values.size(); ++i) {
        if (stream >> value)
            values[i] = value;
        else
            throw std::out_of_range("expecting " + std::to_string(values.size()) +
                                    " values, only read " + std::to_string(i));;
    }
    if (stream >> value)
        throw std::out_of_range("expecting " + std::to_string(values.size()) +
                                " values, read more");;
}
