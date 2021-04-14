#include "cluster.hpp"

void Cluster::Init(size_t count, double* featureArray, size_t targetFeature, DataSet* ds)
{
    m_TargetFeature = targetFeature;
    m_Count = count;
    m_FeaturesArray = new double[m_Count];
    m_ds = ds;

    for (size_t i = 0; i < m_Count; i++)
    {
        m_FeaturesArray[i] = featureArray[i];
    }
    
}

void Cluster::RepositionAtMean()
{
    //Simply, recenter
    ReCenter();
}

double* Cluster::FeatureArray() const
{
    return m_FeaturesArray;
}

size_t Cluster::Count() const
{
    return m_Count;
}

void Cluster::AddRowIndex(size_t index)
{
    m_Indices.insert(index);
    ReCenter();
}

void Cluster::ResetIndices()
{
    m_Indices.clear();
}

Cluster& Cluster::operator=(const Cluster& other)
{
    m_Count = other.m_Count;
    m_FeaturesArray = new double[m_Count];
    for(int index : other.m_Indices)
        m_Indices.insert(index);
    
    m_ds = other.m_ds;
    m_TargetFeature = other.m_TargetFeature;

    return *this;
}

bool Cluster::operator==(const Cluster& other)
{
    if(m_Count != other.m_Count)
        return false;
    
    if(m_Indices != other.m_Indices)
        return false;

    return true;
}

void Cluster::ReCenter()
{
    for(int index : m_Indices)
    {
        for(int i = 0; i < m_Count; i++)
            m_FeaturesArray[i] += std::stod((*m_ds)[index][i]);
    }

    for(int i = 0; i < m_Count; i++)
        m_FeaturesArray[i] /= m_Count;
}

Cluster::~Cluster()
{
    if(m_FeaturesArray)
        delete[] m_FeaturesArray;
}