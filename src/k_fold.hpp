#ifndef K_FOLD_HPP
#define K_FOLD_HPP

#include "pch.hpp"

#define TIMING_ENABLE 0


/*
Provides indices for training and testing data for each fold
Input-
1) Number of folds
2) Dataset to split

Result- It gives a double pointer to a set. The first index refers to testing data[0], training data[1] 
and the second index refers to the nth fold's testing or training data indices.
For example: If you call the function as--  
std::set<int>** result = kfoldValidation(3, dataset_name);
then result[0][1] would give the testing dataset splitted indices for the 2nd fold.
Similary, result[1][2] would give the training dataset splitted indices for the 3rd(and the last fold, for this example) fold.
*/
std::set<int>** kfoldValidation(int, const DataSet&);

//Frees the memory occupied by the result of kfoldValidation function
void ReleaseResultMem(std::set<int>**, int);

#endif