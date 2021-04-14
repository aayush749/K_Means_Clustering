#pragma once

#include <string>
#include <string_view>

#include "vendor/csv.hpp"

using namespace csv;

enum class ColName
{
    sky, air_temp, humidity, wind, water, forecast, enjoy_sport    
};

template <class T>
class Vec : public std::vector<T>
{
public:
    
    //Const Version
    const T& operator[](int index) const
    {
        return std::vector<T>::operator[](index);
    }

    const T& operator[](ColName col) const
    {
        return std::vector<T>::operator[]((size_t)col);
    }

    //Non Const Version
    T& operator[](int index)
    {
        return std::vector<T>::operator[](index);
    }

    T& operator[](ColName col)
    {
        return std::vector<T>::operator[]((size_t)col);
    }
    
};

//An instance of this class will store the dataset in memory.
class DataSet
{
public:
    DataSet() = default;

    DataSet(const char* filepath)
    {
        CSVReader reader(filepath);

        Vec<std::string> tempVec;
        m_NumberOfRows = 0;

        std::vector<std::string> col_names = reader.get_col_names();
        m_NumberOfColumns = col_names.size();

        for(CSVRow& row : reader)
        {
            tempVec.clear();
            for(std::string& col : col_names)
                tempVec.push_back(row[col].get<std::string>());
            
            
            ds.push_back(tempVec);
            m_NumberOfRows++;
        }

        //Convert all the output strings (yes/no) to lowercase
        int i = 0;
        for(auto& row : ds)
        std::for_each(row[m_NumberOfColumns - 1].begin(), row[m_NumberOfColumns - 1].end(), [](char& c) {
        c = ::tolower(c);
        });
    }

    //const version
    const Vec<std::string>& operator[](size_t index) const
    {
        if(index >= m_NumberOfRows)
        {
            printf("[Index: %u] is out of range\n", index);
            __debugbreak;
        }
        return ds[index];
    }

    //non-const version
    Vec<std::string>& operator[](size_t index)
    {
        if(index >= m_NumberOfRows)
        {
            printf("[Index: %u] is out of range\n", index);
            __debugbreak;
        }
        return ds[index];
    }
    const Vec<std::string>& GetRow(size_t rowIndex) const
    {
        return operator[](rowIndex);
    }
    
    const size_t GetRowCount() const
    {
        return m_NumberOfRows;
    }
    
    const size_t GetColumnCount() const
    {
        return m_NumberOfColumns;
    }

public:
    //It modifies the value of a particular column, takes in 1) the column index to modify, 2) modifier function
    void Modify(size_t, std::function<void(std::string&)>);

private:
    std::vector<Vec<std::string>> ds;
    size_t m_NumberOfRows, m_NumberOfColumns;
};

std::ostream& operator<<(std::ostream& stream, const DataSet& dataset);
std::ostream& operator<<(std::ostream& stream, Vec<std::string> vec);