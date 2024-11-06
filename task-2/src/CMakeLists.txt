set(SOURCES
        Grid.cpp Game.cpp Universe.cpp CommandHandler.cpp FileReader.cpp FileWriter.cpp)

set(HEADERS
        Grid.h Game.h Universe.h CommandHandler.h FileReader.h FileWriter.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})