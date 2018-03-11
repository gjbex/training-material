#include <fstream>
#include <iostream>
#include <sstream>

void replace_sep(std::string& str, const std::string&  old_sep,
                 const std::string new_pos) {
    std::string::size_type pos {0};
    while ((pos = str.find(old_sep, pos)) != std::string::npos)
        str.replace(pos, 1, new_pos);
}

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
        replace_sep(line, ",", "\t");
        ofs << line << std::endl;
    }
    ifs.close();
    ofs.close();
    return 0;
}
