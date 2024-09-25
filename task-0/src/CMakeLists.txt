set(SOURCES
        Statistic.cpp Parser.cpp FileWriter.cpp FileReader.cpp)

set(HEADERS
        Statistic.h Parser.h FileWriter.h FileReader.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})