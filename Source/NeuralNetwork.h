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
            layers.emplace_back(Layer(layerSizes[i], layerSizes[i + 1]));
        }
    }

    std::vector<double> CalculateOutputs(std::vector<double> inputs);
    int Classify(std::vector<double> inputs);

    int IndexOfMaxValue(std::vector<double> arr);

    double Cost(std::vector<DataPoint> data);

private:
    double Cost(DataPoint* dataPoint);

    std::vector<Layer> layers;
};
