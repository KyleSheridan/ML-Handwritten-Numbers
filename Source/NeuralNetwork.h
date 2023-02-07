#pragma once
#include <float.h>

#include "Layer.h";
#include "DataPoint.h"

class NeuralNetwork {
public:
    NeuralNetwork(std::vector<int> layerSizes) {
        int arrSize = layerSizes.size() - 1;
        layers.reserve(arrSize);
        for (int i = 0; i < arrSize; i++)
        {
            layers.emplace_back(new Layer(layerSizes[i], layerSizes[i + 1]));
        }
    }

    std::vector<double> CalculateOutputs(std::vector<double> inputs);
    int Classify(std::vector<double> inputs);
    void UpdateAllGradients(DataPoint* dataPoint);
    void ApplyAllGradients(double learnRate);
    void ClearAllGradients();

    int IndexOfMaxValue(std::vector<double> arr);

    double Cost(std::vector<DataPoint*> data);

    void Learn(std::vector<DataPoint*> trainingData, double learnRate);

private:
    double Cost(DataPoint* dataPoint);

    std::vector<Layer*> layers;
};
