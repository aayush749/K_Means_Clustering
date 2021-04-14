#include "k_means.hpp"
#include <cmath>


static double EuclideanDistance(const double* array1, const double* array2, int size, int targetAttributeIndex)
{
    double ed = 0;
    for(int i = 0; i < size; i++)
        if(i != targetAttributeIndex)
            ed += pow(array1[i] - array2[i], 2);

    return sqrt(ed);
}

static double ManhattanDistance(const double* array1, const double* array2, int size, int targetAtrributeIndex)
{
    double md = 0;
    for(int i = 0; i < size; i++)
        if(i != targetAtrributeIndex)
            md += abs(array1[i] - array2[i]);
    
    return md;
}

//This function returns the index of the minimum element in the distances array
static int GetMinDistEntryIndex(const double* distances, int size)
{
    int minIndex = 0;
    for(int i = 1; i < size; i++)
    {
        if(distances[i] < distances[minIndex])
            minIndex = i;   //Then update the minIndex
    }

    return minIndex;
}

/*
This function accepts the training dataSet and training indices set, the array of clusters (whose size is the value k, which is also the number of clusters for k means clustering), 
and a distance calculator function
*/
static void k_mean_util(int k, const DataSet& ds, std::set<int>* split, int splitIndex, Cluster* clusters, std::function<double(const double* array1, const double* array2, int arraySize, int targetAttributeIndex)> distanceCalculator, int targetAtributeIndex)
{
    //This function calculates the distance between at the current index in the dataset and the different 
    //clusters passed to it, 
    //and gives a judgement as to which cluster does it belong
    int n_cols = ds.GetColumnCount();
    double* rowDouble = new double[n_cols];

    //A vector of strings to store the rows of the dataset, which would then be later converted to an array of doubles
    std::vector<std::string> rowStringVec;

    //An array to store the distances from the different clusters
    double* distances = new double[k];

    int t = 0;
    for(int index : split[splitIndex])
    {
        if(t < k)
        {
            t++;
        }
        else
        {
            rowStringVec = ds[index];
            int i = 0;
            for(std::string value : rowStringVec)
            {
                rowDouble[i++] = std::stod(value);
            }

            //Now after you have the row double array, which consists of all the feature values in form of a double value rather than a string value, pass the array to the cluster
            //Calculate the distance from each cluster
            for(i = 0; i < k; i++)
            {
                distances[i] = distanceCalculator(clusters[i].FeatureArray(), rowDouble, n_cols, 4);
            }

            int minDistIndex = GetMinDistEntryIndex(distances, k);

            //Add that dataSet row index to the cluster
            clusters[minDistIndex].AddRowIndex(index);
            

            // //Update the nearest found cluster
            // clusters[minDistIndex].Update(rowDouble);
            
        }
    }

    //After all the clusters have been filled, reposition them at their individual means
    for(int clusterInd = 0; clusterInd < k; clusterInd++)
            clusters[clusterInd].RepositionAtMean();

    delete[] distances;
    delete[] rowDouble;
}

static void SwapClusterDoubleBuffer(Cluster** clusterDoubleBuffer)
{
    //Just swap the pointers
    auto* tempPtr = clusterDoubleBuffer[0];
    clusterDoubleBuffer[0] = clusterDoubleBuffer[1];
    clusterDoubleBuffer[1] = tempPtr;
}

Cluster* k_means_clustering(int k, const DataSet& ds, std::set<int>* split, size_t foldNumber, DistanceType type,  size_t targetAttributeIndex, int max_Iter)
{
    printf("Running k means clustering --iterations = %d\n", max_Iter);
    Timer timer("k_means_clustering");
    //Declare a distance function pointer to store the type of distance to use.
    double (*distanceFPtr)(const double*, const double*, int, int);
    if(type == DistanceType::Euclid)
        distanceFPtr = EuclideanDistance;
    else
        distanceFPtr = ManhattanDistance;


    // auto train = split[0];
    // auto test = split[1];

    //Make and array of k clusters
    Cluster* clusters = new Cluster[k];
    Cluster* otherClusters = new Cluster[k];
    
    Cluster** clusterDoubleBuffer = new Cluster*[2];
    clusterDoubleBuffer[0] = clusters;
    clusterDoubleBuffer[1] = otherClusters;

    int iterations = 0;

    //Initialize the clusters
    {
        double* temp = (double*)alloca(sizeof(double) * ds.GetColumnCount());
        for(int clusterNo = 0; clusterNo < k; clusterNo++)
        {
            for(int i = 0; i < ds.GetColumnCount(); i++)
                temp[i] = std::stod(ds[clusterNo][i]);
            clusters[clusterNo].Init(ds.GetColumnCount(), temp, targetAttributeIndex, (DataSet*)&ds);
        }
    }
    for(int i = 0; i < k; i++)
        clusterDoubleBuffer[1][i] = clusterDoubleBuffer[0][i];
    
    k_mean_util(k, ds, split, foldNumber, clusterDoubleBuffer[0], distanceFPtr, 4);
    while(true)
    {
        SwapClusterDoubleBuffer(clusterDoubleBuffer);
        k_mean_util(k, ds, split, foldNumber, clusterDoubleBuffer[0], distanceFPtr, 4);
        
        iterations++;
        //if the clusters do not change between two iterations or max Iteration is reached then stop iterating
        if(max_Iter != -1)
            if(*clusterDoubleBuffer[1] == *clusterDoubleBuffer[0])
                break;
            else if(iterations == max_Iter)
                break; 
            //Reset the indices only if next iteration is to take place
            else
                for(int clustNo = 0; clustNo < k; clustNo++)
                    clusterDoubleBuffer[0][clustNo].ResetIndices();

        if(max_Iter == -1)
            if(*clusterDoubleBuffer[1] == *clusterDoubleBuffer[0])
                break;
                
            else    //for the case of unlimited iterations, if there is to be a next iteration then reset the indices
                for(int clustNo = 0; clustNo < k; clustNo++)
                    clusterDoubleBuffer[0][clustNo].ResetIndices();
    }




    printf("Stopped k means clustering after %d iterations\n", iterations);

    Cluster* result = new Cluster[k];
    for(int i = 0; i < k; i++)
        result[i] = clusterDoubleBuffer[0][i];

    delete[] clusterDoubleBuffer;
    delete[] clusters;
    delete[] otherClusters;
    
    return result;
}

