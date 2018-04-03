alias cppcheck_c="cppcheck --quiet --enable=all --inconclusive \
                           --suppress=missingIncludeSystem \
                           --language=c --std=c89 --platform=unix64"

alias cppcheck_cpp="cppcheck --quiet --enable=all --inconclusive \
                           --suppress=missingIncludeSystem \
                           --language=c++ --std=c++14 --platform=unix64"
