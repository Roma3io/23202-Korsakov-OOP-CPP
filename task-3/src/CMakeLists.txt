set(SOURCES
        WAVWriter.cpp WAVReader.cpp ConfigParser.cpp HelpGenerator.cpp Converters.cpp ConsoleParser.cpp SoundProcessor.cpp ConvertersController.cpp)

set(HEADERS
        WAVWriter.h WAVReader.h ConfigParser.h ExceptionHandler.h HelpGenerator.h Converters.h ConsoleParser.h SoundProcessor.h ConvertersController.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})