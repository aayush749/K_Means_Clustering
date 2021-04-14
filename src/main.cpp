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
    auto iris_split = kfoldValidation(3, iris);
    auto mall_cust_split = kfoldValidation(3, mall_cust);

    int maxIterations;
    printf("Enter the maximum number of iterations: ");
    scanf("%d", &maxIterations);

    auto clustersArray = k_means_clustering(3, mall_cust, mall_cust_split[1], 0, DistanceType::Euclid, 4, maxIterations);

    //Release memory of k fold validation results
    ReleaseResultMem(iris_split, 3);
    ReleaseResultMem(mall_cust_split, 3);
    return 0;
}