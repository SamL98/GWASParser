#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow
{
public:
    std::string operator[](int i) const;
    int size() const;
    void readNextRow(std::istream& str);
private:
    std::vector<std::string> row_data;
};