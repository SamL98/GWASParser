#include <iostream>
#include <sstream>
#include <string>
#include <mysql++.h>

class Utility
{
public:
    static int stringToInt(std::string str);
    static int stringToDouble(std::string str);
    static int rowToInt(mysqlpp::Row row);
};