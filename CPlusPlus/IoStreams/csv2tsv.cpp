#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "# error: two file names as arguments" << endl;
        terminate();
    }
    string i_filename(argv[1]);
    string o_filename(argv[2]);
    ifstream ifs(i_filename);
    if (!ifs) {
        cerr << "# error: can not open " << i_filename << endl;
        terminate();
    }
    ofstream ofs(o_filename);
    if (!ofs) {
        cerr << "# error: can not open " << i_filename << endl;
        terminate();
    }
    string line;
    while (getline(ifs, line)) {
        stringstream str(line);
        double data {0.0};
        str >> data;
        ofs << data;
        char sep;
        while (std::char_traits<char>::not_eof(sep = str.get())) {
            str >> data;
            ofs << "\t" << data;
        }
        ofs << endl;
    }
    ifs.close();
    ofs.close();
    return 0;
}
