#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>
#include <math.h>

class Layer {
public:
	Layer(int _numNodesIn, int _numNodesOut) {
		numNodesIn = _numNodesIn;
		numNodesOut = _numNodesOut;

		std::vector<double> temp;

		temp.resize(numNodesOut, 0.0);

		costGradientW.resize(numNodesIn, temp);
		weights.resize(numNodesIn, temp);
		costGradientB.resize(numNodesOut, 0.0);
		biases.resize(numNodesOut, 0.0);

		weightedInputs.resize(numNodesOut, 0.0);
		activations.resize(numNodesOut, 0.0);

		InitializeRandomWeights();
	}

	std::vector<double> CalculateOutputs(std::vector<double> inputs);

	double NodeCost(double outputActivation, double expectedOutput);
	double NodeCostDerivative(double outputActivation, double expectedOutput);
	double CrossEntopy(double outputActivation, double expectedOutput);
	double CrossEntopyDerivative(double outputActivation, double expectedOutput);


	void ApplyGradients(double learnRate);
	void UpdateGradients(std::vector<double> nodeValues);
	void ClearGradients();

	std::vector<double> CalculateOutputLayerNodeValues(std::vector<double> expectedOutputs);
	std::vector<double> CalculateHiddenLayerNodeValues(Layer* oldLayer, std::vector<double> oldNodeValues);

private:
	double ActivationFunction(double weightedInput);
	double ActivationDerivative(double weightedInput);
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
};