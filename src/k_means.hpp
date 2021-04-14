#ifndef K_MEANS_HPP
#define K_MEANS_HPP

#include "cluster.hpp"

enum class DistanceType
{
    Euclid, Manhattan
};

//This would run its utility function until the result achieved in two consective iterations come out to be same
/*
It takes in:-
1--> value of k, number of clusters
2--> the dataset
3--> could also accept a set of training data indices and also a set of testing data indices (currently takes only training dataset indices) against which to test the trained model
The trained model would be the final features' centroid for clustering

It could output:- The test accuracy against the trained model
*/
Cluster* k_means_clustering(int k, const DataSet& ds, std::set<int>* split, size_t foldNumber, DistanceType type,  size_t targetAttributeIndex, int max_Iter = -1);

#endif