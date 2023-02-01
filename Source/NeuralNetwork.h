#pragma once
#include <float.h>
#include "Layer.h";

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
private:
    std::vector<Layer> layers;
};
