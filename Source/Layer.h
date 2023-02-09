#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>
#include <math.h>
#include <functional>

#include "Cost.h"
#include "Activation.h"

class Layer {
public:
	Layer(int _numNodesIn, int _numNodesOut, CostFunctionType costFunction, ActivationFunctionType activationFunction);

	std::vector<double> CalculateOutputs(std::vector<double> inputs);

	void ApplyGradients(double learnRate);
	void UpdateGradients(std::vector<double> nodeValues);
	void ClearGradients();

	std::vector<double> CalculateOutputLayerNodeValues(std::vector<double> expectedOutputs);
	std::vector<double> CalculateHiddenLayerNodeValues(Layer* oldLayer, std::vector<double> oldNodeValues);

private:
	void InitializeRandomWeights();

public:
	int numNodesIn, numNodesOut;
	std::vector<std::vector<double>> costGradientW;
	std::vector<double> costGradientB;
	std::vector<std::vector<double>> weights;
	std::vector<double> biases;

	std::vector<double> inputValues;
	std::vector<double> weightedInputs;
	std::vector<double> activations;

	Cost* cost;
	Activation* activation;
};