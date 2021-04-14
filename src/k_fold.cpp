#include "pch.hpp"

std::set<int>** kfoldValidation(int k, const DataSet& ds)
{
    #if TIMING_ENABLE
    Timer timer("kfoldValidation");
    #endif
    
    int n_row = ds.GetRowCount();

    int* start, *end;
    start = (int*)alloca(sizeof(int) * k);
    end = (int*)alloca(sizeof(int) * k);

    for(int t = 1; t <= k; t++)
    {
        start[t - 1] = (t - 1) * (n_row / k);
        end[t - 1] = (n_row / k  - 1) + start[t - 1];
    }

    //Prepare test data indices as
    std::set<int>* test, *train;
    test = new std::set<int>[k];
    train = new std::set<int>[k];
    // std::set<int> tst[k], trn[k];
    for(int it = 1; it <= k; it++)
    {
        for(int i = start[it - 1]; i <= end[it - 1]; i++)
            test[it - 1].insert(i);
    }
    
    for(int it = 1; it <= k; it++)
    {
        for(int i = 0; i < n_row; i++)
            if(i < start[it - 1] || i > end[it - 1])
                train[it - 1].insert(i);
    }

    std::set<int>** splitIndex = new std::set<int>*[2];
    splitIndex[0] = test;
    splitIndex[1] = train;

    return splitIndex;
}

void ReleaseResultMem(std::set<int>** result, int k)
{
    delete[] result[0], result[1];
    delete[] result;
}