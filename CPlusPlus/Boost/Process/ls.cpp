#include <boost/process.hpp>
#include <iostream>

namespace bp = boost::process;

int main() {
    bp::ipstream ips;
    bp::child child_process(bp::search_path("ls"), ".", bp::std_out > ips);
    std::string line;
    while (child_process.running() && std::getline(ips, line)
            && !line.empty())
        std::cout << line << std::endl;
    child_process.wait();
    return 0;
}
