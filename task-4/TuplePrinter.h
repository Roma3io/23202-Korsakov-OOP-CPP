#ifndef TUPLEPRINTER_H
#define TUPLEPRINTER_H

#include <iostream>
#include <tuple>

template<int Index, typename Ch, typename Tr, typename... Args>
class TuplePrinter
{
public:
    void printTuple(std::basic_ostream<Ch, Tr> &os,
                    std::tuple<Args...> const &tuple)
    {
        TuplePrinter<Index - 1, Ch, Tr, Args...> tuplePrinter;
        tuplePrinter.printTuple(os, tuple);
        if (Index != sizeof...(Args) - 1)
            os << std::get<Index>(tuple) << ", ";
        else
            os << std::get<Index>(tuple);
    }
};

template<typename Ch, typename Tr, typename... Args>
class TuplePrinter<0, Ch, Tr, Args...>
{
public:
    void printTuple(std::basic_ostream<Ch, Tr> &os,
                    std::tuple<Args...> const &tuple)
    {
        os << std::get<0>(tuple) << ", ";
    }
};

template<typename Ch, typename Tr, typename... Args>
std::ostream &operator<<(std::basic_ostream<Ch, Tr> &os,
                         std::tuple<Args...> const &tuple)
{
    os << '(';
    TuplePrinter<sizeof...(Args) - 1, Ch, Tr, Args...> tuplePrinter;
    tuplePrinter.printTuple(os, tuple);
    return os << ')';
}

#endif//TUPLEPRINTER_H
