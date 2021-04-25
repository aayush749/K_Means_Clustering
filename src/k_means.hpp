#ifndef K_MEANS_HPP
#define K_MEANS_HPP

#include "cluster.hpp"

enum class DistanceType
{
    Euclid, Manhattan
};

//This would run its utility function until the result achieved in two consective iterations come out to be same
/*
Input:-
1--> value of k, number of clusters
2--> a reference to the dataset
3--> fold index of the fold of dataset -- generated after k fold splitting
4--> Distance algorithm to be used to calculate the distance (Euclidean or Manhattan distance)
5--> Target attribute's index in the dataset
6--> (Optional) The maximum number of iterations of k means clustering to perform.

Output:- Pointer to the array of clusters
*/
Cluster* k_means_clustering(
                            int k, 
                            const DataSet& ds, 
                            std::set<int>* split, 
                            size_t foldNumber, 
                            DistanceType type,  
                            size_t targetAttributeIndex, 
                            int max_Iter = -1
                            );

#endif