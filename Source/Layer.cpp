#include "Layer.h"

std::vector<double> Layer::CalculateOutputs(std::vector<double> inputs)
{
	inputValues = std::vector<double>(inputs);

	for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
	{
		double weightedInput = biases[nodeOut];
		for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
		{
			weightedInput += inputs[nodeIn] * weights[nodeIn][nodeOut];
		}
		weightedInputs[nodeOut] = weightedInput;
	}

	for (int outputNode = 0; outputNode < activations.size(); outputNode++)
	{
		activations[outputNode] = ActivationFunction(weightedInputs[outputNode]);
	}

	return activations;
}

double Layer::NodeCost(double outputActivation, double expectedOutput)
{
	double error = outputActivation - expectedOutput;
	return error * error;
}

double Layer::NodeCostDerivative(double outputActivation, double expectedOutput)
{
	return 2 * (outputActivation - expectedOutput);
}

void Layer::ApplyGradients(double learnRate)
{
	for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
	{
		biases[nodeOut] -= costGradientB[nodeOut] * learnRate;

		for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
		{
			weights[nodeIn][nodeOut] -= costGradientW[nodeIn][nodeOut] * learnRate;
		}
	}
}

void Layer::UpdateGradients(std::vector<double> nodeValues)
{
	for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
	{
		for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
		{
			// Evaluate partial derivative: cost / weight.
			double derivativeCostWeight = inputValues[nodeIn] * nodeValues[nodeOut];

			costGradientW[nodeIn][nodeOut] += derivativeCostWeight;
		}

		// Evaluate partial derivative: cost / bias.
		double derivativeCostBias = 1 * nodeValues[nodeOut];
		costGradientB[nodeOut] += derivativeCostBias;
	}
}

void Layer::ClearGradients()
{
	for (auto vec : costGradientW) {
		for (double val : vec) {
			val = 0;
		}
	}

	for (double val : costGradientB) {
		val = 0;
	}
}

std::vector<double> Layer::CalculateOutputLayerNodeValues(std::vector<double> expectedOutputs)
{
	std::vector<double> nodeValues;
	nodeValues.reserve(expectedOutputs.size());

	for (int i = 0; i < expectedOutputs.size(); i++)
	{
		double costDerivative = NodeCostDerivative(activations[i], expectedOutputs[i]);
		double activationDerivative = ActivationDerivative(weightedInputs[i]);
		nodeValues.emplace_back(activationDerivative * costDerivative);
	}

	return nodeValues;
}

std::vector<double> Layer::CalculateHiddenLayerNodeValues(Layer* oldLayer, std::vector<double> oldNodeValues)
{
	std::vector<double> newNodeValues;
	newNodeValues.reserve(numNodesOut);

	for (int newNodeIndex = 0; newNodeIndex < numNodesOut; newNodeIndex++)
	{
		double newNodeValue = 0;
		for (int oldNodeIndex = 0; oldNodeIndex < oldNodeValues.size(); oldNodeIndex++)
		{
			double weightedInputDerivative = oldLayer->weights[newNodeIndex][oldNodeIndex];
			newNodeValue += weightedInputDerivative * oldNodeValues[oldNodeIndex];
		}

		newNodeValue *= ActivationDerivative(weightedInputs[newNodeIndex]);
		newNodeValues.emplace_back(newNodeValue);
	}

	return newNodeValues;
}

double Layer::ActivationFunction(double weightedInput)
{
	return 1 / (1 + std::exp(-weightedInput));
}

double Layer::ActivationDerivative(double weightedInput)
{
	double activation = ActivationFunction(weightedInput);
	return activation * (1 - activation);
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