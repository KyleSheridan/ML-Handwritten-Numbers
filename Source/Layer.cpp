#include "Layer.h"

std::vector<double> Layer::CalculateOutputs(std::vector<double> inputs)
{
	std::vector<double> weightedInputs;
	weightedInputs.reserve(numNodesOut);

	for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
	{
		double weightedInput = biases[nodeOut];
		for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
		{
			weightedInput += inputs[nodeIn] * weights[nodeIn][nodeOut];
		}
		weightedInputs[nodeOut] = ActivationFunction(weightedInput);
	}

	return weightedInputs;
}

double Layer::NodeCost(double outputActivation, double expectedOutput)
{
	double error = outputActivation - expectedOutput;
	return error * error;
}

void Layer::ApplyGradients(double learnRate)
{
	for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
	{
		biases[nodeOut] -= costGradientB[nodeOut] * learnRate;

		for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
		{
			weights[nodeIn][nodeOut] = costGradientW[nodeIn][nodeOut] * learnRate;
		}
	}
}

double Layer::ActivationFunction(double weightedInput)
{
	return 1 / (1 + std::exp(-weightedInput));
}

void Layer::InitializeRandomWeights()
{
	srand(time(NULL));

	for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
	{
		for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
		{
			double randomVal = (rand() / (double)RAND_MAX) * 2 - 1;

			// 1 / sqrt(numInputs) works best for sigmoid (Change with activation function)
			weights[nodeIn][nodeOut] = randomVal / sqrt(numNodesIn);
		}
	}
}