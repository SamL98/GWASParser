#include "csv.hpp"

std::string CSVRow::operator[] (int i) const
{
    std::size_t index = static_cast<std::size_t>(i);
    return row_data[index];
}
int CSVRow::size() const
{
    return static_cast<int>(row_data.size());
}
void CSVRow::readNextRow(std::istream& str)
{
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    row_data.clear();

    while (std::getline(lineStream, cell, ','))
    {
        row_data.push_back(cell);
    }
}