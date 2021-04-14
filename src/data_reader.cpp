#include "pch.hpp"

std::ostream& operator<<(std::ostream& stream, Vec<std::string> vec)
{
    int i = 0;
    for(; i < vec.size() - 1; i++)
    {
        stream << "'" << vec[i] <<"'" << ", ";
    }

    stream << "'" << vec[i] <<"'";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const DataSet& dataset)
{
    for(int i = 0; i < dataset.GetRowCount(); i++)
    {
        stream<<dataset[i]<<std::endl;
    }

    return stream;
}

void DataSet::Modify(size_t col, std::function<void(std::string&)> modify)
{
    for(auto& row : ds)
    {
        modify(row[col]);
    }
}