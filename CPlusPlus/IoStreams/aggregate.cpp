#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "### error: two file names as arguments" << std::endl;
        return 1;
    }
    std::string i_filename(argv[1]);
    std::ifstream ifs(i_filename);
    if (!ifs) {
        std::cerr << "### error: can not open " << i_filename << std::endl;
        return 2;
    }
    std::string o_filename(argv[2]);
    std::ofstream ofs(o_filename);
    if (!ofs) {
        std::cerr << "### error: can not open " << i_filename << std::endl;
        return 2;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        double sum {0.0};
        std::stringstream str(line);
        double data {0.0};
        if (str >> data) {
            sum += data;
            char sep;
            while (std::char_traits<char>::not_eof(sep = str.get())) {
                if (str >> data)
                    sum += data;
            }
        }
        ofs << sum << "," << line << std::endl;
    }
    ifs.close();
    ofs.close();
    return 0;
}
