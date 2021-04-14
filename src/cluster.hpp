#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "pch.hpp"

class Cluster
{
    double* m_FeaturesArray;
    size_t m_Count;
    size_t m_TargetFeature;
public:

    Cluster()
        :m_Count(0), m_FeaturesArray(nullptr), m_ds(nullptr)
    {}

    Cluster(size_t num_of_features, double* featureArray, size_t targetFeature, DataSet* ds)
        :m_Count(num_of_features), m_TargetFeature(targetFeature), m_ds(ds)
    {
        m_FeaturesArray = new double[m_Count];
        for (size_t i = 0; i < m_Count; i++)
        {
            m_FeaturesArray[i] = featureArray[i];
        }
        
    }

public:

    //Initializes the cluster
    void Init(size_t, double* featureArray, size_t targetFeature, DataSet* ds);

    //Returns a pointer to FeatureArray
    double* FeatureArray() const;
    
    //Returns the size of the feature array
    inline size_t Count() const;

    //Adds the new index to the cluster
    void AddRowIndex(size_t index);

    //It repositions the cluster at the mean position, should be called after every iteration
    void RepositionAtMean();

    //Clears the row index set of the cluster, call it before every iteration of the clustering algorithm, except for the first.
    void ResetIndices();

    //Destructor
    ~Cluster();

public:
    Cluster& operator=(const Cluster& other);
    bool operator==(const Cluster& other);

private:
    //This stores the index of the dataset's row which belongs to the cluster
    std::set<size_t> m_Indices;
    DataSet* m_ds;

private:
    void ReCenter();
};


#endif