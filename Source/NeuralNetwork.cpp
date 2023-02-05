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

double NeuralNetwork::Cost(std::vector<DataPoint*> data)
{
	double totalCost = 0;

	for(DataPoint* dataPoint : data)
	{
		totalCost += Cost(dataPoint);
	}

	return totalCost / data.size();
}

void NeuralNetwork::Learn(std::vector<DataPoint*> trainingData, double learnRate)
{
	const double h = 0.0001;
	double originalCost = Cost(trainingData);

	std::cout << originalCost << "\n";

	for (Layer layer : layers) 
	{
		for (int nodeIn = 0; nodeIn < layer.numNodesIn; nodeIn++)
		{
			for (int nodeOut = 0; nodeOut < layer.numNodesOut; nodeOut++)
			{
				layer.weights[nodeIn][nodeOut] += h;
				double deltaCost = Cost(trainingData) - originalCost;
				layer.weights[nodeIn][nodeOut] -= h;
				layer.costGradientW[nodeIn][nodeOut] = deltaCost / h;
			}
		}

		for (int biasIndex = 0; biasIndex < layer.biases.size(); biasIndex++)
		{
			layer.biases[biasIndex] += h;
			double deltaCost = Cost(trainingData) - originalCost;
			layer.biases[biasIndex] -= h;
			layer.costGradientB[biasIndex] = deltaCost / h;
		}
	}

	for (Layer layer : layers) 
	{
		layer.ApplyGradients(learnRate);
	}
}
