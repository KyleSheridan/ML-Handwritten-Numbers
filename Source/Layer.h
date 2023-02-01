#pragma once
#include <iostream>
#include <vector>

class Layer {
public:
	Layer(int _numNodesIn, int _numNodesOut) {
		numNodesIn = _numNodesIn;
		numNodesOut = _numNodesOut;

		weights.reserve(numNodesIn);
		biases.reserve(numNodesOut);
	}

	std::vector<double> CalculateOutputs(std::vector<double> inputs);

private:
	int numNodesIn, numNodesOut;
	std::vector<std::vector<double>> weights;
	std::vector<double> biases;
};