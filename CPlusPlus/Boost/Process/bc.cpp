#include <boost/process.hpp>
#include <iostream>

namespace bp = boost::process;

int main() {
    bp::ipstream ips;
    bp::opstream ops;
    bp::child bc_process(bp::search_path("bc"), "-q",
                         bp::std_out > ips, bp::std_in < ops);
    std::string line;
    while (std::getline(std::cin, line)) {
        ops << line << std::endl;
        std::string value;
        ips >> value;
        std::cout << "result: " << value << std::endl;
    }
    return 0;
}
