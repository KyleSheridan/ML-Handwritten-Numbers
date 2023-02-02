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

double Layer::ActivationFunction(double weightedInput)
{
	return 1 / (1 + std::exp(-weightedInput));
}

double Layer::NodeCost(double outputActivation, double expectedOutput)
{
	double error = outputActivation - expectedOutput;
	return error * error;
}
