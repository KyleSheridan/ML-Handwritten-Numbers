#include "NeuralNetwork.h"

std::vector<double> NeuralNetwork::CalculateOutputs(std::vector<double> inputs)
{
	for(Layer layer : layers)
	{
		inputs = layer.CalculateOutputs(inputs);
	}
	return inputs;
}

int NeuralNetwork::Classify(std::vector<double> inputs)
{
	std::vector<double> outputs = CalculateOutputs(inputs);

	double largest = DBL_MIN;

	for (double val : outputs) {
		if (val > largest) largest = val;
	}

	return largest;
}

int NeuralNetwork::IndexOfMaxValue(std::vector<double> arr)
{
	int index = -1;

	double largest = DBL_MIN;

	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > largest) {
			largest = arr[i];

			index = i;
		}
	}

	return index;
}

double NeuralNetwork::Cost(DataPoint* dataPoint)
{
	std::vector<double> outputs = CalculateOutputs(dataPoint->inputs);
	Layer outputLayer = layers[layers.size() - 1];
	double cost = 0;

	for (int nodeOut = 0; nodeOut < outputs.size(); nodeOut++)
	{
		cost += outputLayer.NodeCost(outputs[nodeOut], dataPoint->expectedOutputs[nodeOut]);
	}

	return cost;
}

double NeuralNetwork::Cost(std::vector<DataPoint> data)
{
	double totalCost = 0;

	for(DataPoint dataPoint : data)
	{
		totalCost += Cost(&dataPoint);
	}

	return totalCost / data.size();
}
