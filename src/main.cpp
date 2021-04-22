#include "pch.hpp"
#include "k_means.hpp"
#include <climits>

int main()
{
    DataSet iris("Datasets/iris.csv"), mall_cust("Datasets/Mall_Customers.csv");
    
    //Convert all the string data (species column), to a corresponding double
    iris.Modify(4, [](std::string& value)
    {
        if(value == "setosa")
            value = "1.0";
        else if(value == "versicolor")
            value = "2.0";
        else
            value = "3.0";
    });


    //Convert all the string data (gender column), to a corresponding double
    mall_cust.Modify(1, [](std::string& value)
    {
        if(value == "Male")
            value = "1.0";
        else
            value = "2. 0";
    });

    //Perform k fold 
    int num_folds = 4;
    auto iris_split = kfoldValidation(num_folds, iris);
    auto mall_cust_split = kfoldValidation(num_folds, mall_cust);

    int maxIterations;
    printf("Enter the maximum number of iterations: ");
    scanf("%d", &maxIterations);

    int k = 3; //Number of clusters
    for(int fold_val = 0; fold_val < num_folds; fold_val++)
    {   
        printf("\n=============================Fold : %d=============================\n", fold_val + 1);
        auto clustersArray = k_means_clustering(k, mall_cust, mall_cust_split[1], fold_val, DistanceType::Manhattan, 4, maxIterations);
        for(int cluster = 0; cluster < k; cluster++)
        {
            std::set<size_t> indices = clustersArray[cluster].GetIndicesSet();
            for(size_t index : indices)
                std::cout<<mall_cust[index]<<std::endl;
        }
    }

    //Release memory of k fold validation results
    ReleaseResultMem(iris_split, 3);
    ReleaseResultMem(mall_cust_split, 3);
    return 0;
}