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
