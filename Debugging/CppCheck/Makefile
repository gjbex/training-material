check: check_c check_cpp

check_c: $(wildcard *.c)
	cppcheck --quiet --enable=all --inconclusive \
             --suppress=missingIncludeSystem \
             --language=c --std=c89 --platform=unix64 $^

check_cpp: $(wildcard *.cpp)
	cppcheck --quiet --enable=all --inconclusive \
             --suppress=missingIncludeSystem \
             --language=c++ --std=c++14 --platform=unix64 $^
