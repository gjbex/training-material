#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

class String {
    private:
        char *str;
        int id;
        static int global_id;
    public:
        String() : str {nullptr}, id {++global_id} {
            std::cout << "String() " << id << std::endl;
        }
        String(const char* s) {
            id = ++global_id;
            str = new char[strlen(s) + 1];
            memcpy(str, s, strlen(s) + 1);
            std::cout << "String(\"" << str << "\") " << id << std::endl;
        }
        String(const String& other) : id {++global_id} {
            str = new char[strlen(other.str) + 1];
            memcpy(str, other.str, strlen(other.str) + 1);
            std::cout << "String(&\"" << str << "\") " << id << std::endl;
        }
        String& operator=(const String& other) {
            str = new char[strlen(other.str) + 1];
            memcpy(str, other.str, strlen(other.str) + 1);
            std::cout << id << " =& " << other.id << " \"" << str << "\""
                      << std::endl;
            return *this;
        }
        String(String&& other) : id {++global_id} {
            str = std::exchange(other.str, nullptr);
            std::cout << "String(&&\"" << str << "\") " << id << std::endl;
        }
        String& operator=(String&& other) {
            str = std::exchange(other.str, nullptr);
            std::cout << id << " =&& " << other.id << " \"" << str << "\""
                      << std::endl;
            return *this;
        }
        String operator+(const String& other) const {
             String s((std::string(this->str) + std::string(other.str)).c_str());
             return s;
        }
        ~String() {
            if (str) {
                std::cout << "~String(\"" << str << "\") " << id << std::endl;
                delete[] str;
            } else {
                std::cout << "~String() " << id << std::endl;
            }
        }
};

int String::global_id = 0;

int main() {
    // constructor call
    String s1("abc");
    // copy constructor call
    String s2 {s1};
    // copy constructor call, copy elision
    String s3 = s1 + s2;
    // trivial constructor call
    String s4, s5;
    // copy assignment call
    s4 = s1;
    // move assignment call
    s5 = std::move(s1);
    std::vector<String> v;
    v.reserve(5);
    // move constructor call
    v.push_back(s3);
    v.emplace_back("gfh");
    // destructor calls
    return 0;
}
