if (!include(../../config.txt)) {
    error("Failed to open config.txt")
}

SOURCES += main.cpp foo.cpp developer1.cpp developer2.cpp
HEADERS += foo.hpp

# Boost.Test works well only when we link against
# static version of boost_unit_test_framework library
LIBS += -static -lboost_unit_test_framework -lboost_system -ldl -lrt
