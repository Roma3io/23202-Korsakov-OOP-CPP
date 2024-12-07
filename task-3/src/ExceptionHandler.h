#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <stdexcept>
#include <string>

class ExceptionHandler : public std::exception
{
    std::string message;

public:
    explicit ExceptionHandler(const std::string &message): message(message) {}
};

class InvalidFormatException : public ExceptionHandler
{
public:
    explicit InvalidFormatException(const std::string &message)
        : ExceptionHandler(message) {}
};

class FileNotFoundException : public ExceptionHandler
{
public:
    explicit FileNotFoundException(const std::string &message)
        : ExceptionHandler(message) {}
};

class InvalidConfigException : public ExceptionHandler
{
public:
    explicit InvalidConfigException(const std::string &message)
        : ExceptionHandler(message) {}
};

#endif // EXCEPTIONHANDLER_H
