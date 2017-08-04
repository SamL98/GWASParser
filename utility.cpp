#include "utility.hpp"

int Utility::stringToInt(std::string str)
{
    std::istringstream istr(str);
    int to_int;
    istr >> to_int;
    return to_int;
}

int Utility::stringToDouble(std::string str)
{
    std::istringstream ostr(str);
    double to_double;
    ostr >> to_double;
    return to_double;
}

int Utility::rowToInt(mysqlpp::Row row)
{
    std::string result;
    std::ostringstream rowStream;
    rowStream << row;
    result = rowStream.str();
    return Utility::stringToInt(result);
}