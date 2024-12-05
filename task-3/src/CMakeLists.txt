set(SOURCES
        WAVWriter.cpp WAVReader.cpp MixConverter.cpp MuteConverter.cpp ConfigParser.cpp ConverterFactory.cpp HelpGenerator.cpp)

set(HEADERS
        WAVWriter.h WAVReader.h Converter.h MixConverter.h MuteConverter.h ConfigParser.h ExceptionHandler.h ConverterFactory.h HelpGenerator.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})