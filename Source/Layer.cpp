#include "Layer.h"

std::vector<double> Layer::CalculateOutputs(std::vector<double> inputs)
{
	std::vector<double> weightedInputs;

	for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
	{
		double weightedInput = biases[nodeOut];
		for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
		{
			weightedInput += *(inputs[nodeIn]) * weights[nodeIn][nodeOut];
		}
		weightedInputs[nodeOut] = weightedInput;
	}

	return weightedInputs;
}
