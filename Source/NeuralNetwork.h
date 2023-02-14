#pragma once
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <random>
#include <string>
#include <float.h>
#include <thread>

#include "Layer.h";
#include "DataPoint.h"
#include "HelperFunctions.h"
#include "ThreadPool.h"

class NeuralNetwork {
public:
    NeuralNetwork(std::vector<int> layerSizes,
                  CostFunctionType costFunction = CostFunctionType::CROSS_ENTORPY,
                  ActivationFunctionType activationFunction = ActivationFunctionType::SIGMOID) 
    {
        int arrSize = layerSizes.size() - 1;
        layers.reserve(arrSize);
        for (int i = 0; i < arrSize; i++)
        {
            layers.emplace_back(new Layer(layerSizes[i], layerSizes[i + 1], costFunction, activationFunction));
        }
    }

    std::vector<double> CalculateOutputs(std::vector<double> inputs);
    int Classify(std::vector<double> inputs);
    void UpdateAllGradients(DataPoint* dataPoint);
    void ApplyAllGradients(double learnRate);
    void ClearAllGradients();

    int TestNumber(DataPoint* dataPoint);

    int IndexOfMaxValue(std::vector<double> arr);

    double Cost(std::vector<DataPoint*> data);

    void Learn(std::vector<DataPoint*> trainingData, double learnRate);

    double Test(std::vector<DataPoint*> testingData);

    void BatchLearn(std::vector<DataPoint*> trainingData, double learnRate, int batchSize);
    void BatchLearn(std::vector<DataPoint*> trainingData, std::vector<DataPoint*> testingData, double learnRate, int batchSize);
    void MiniBatch(std::vector<DataPoint*> trainingData, int startIndex, int batchSize, double learnRate, ThreadPool* pool);

    void PrintOutputs(std::vector<double> inputs);

private:
    double Cost(DataPoint* dataPoint);
    int LargestOutput(std::vector<double> outputs);

    std::vector<Layer*> layers;

    ThreadPool* threadPool;
};
