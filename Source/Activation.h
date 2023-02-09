#pragma once
#include <math.h>

enum class ActivationFunctionType {
	SIGMOID
};

struct Activation
{
	virtual double ActivationFunction(double weightedInput) = 0;
	virtual double ActivationFunctionDerivative(double weightedInput) = 0;
};

struct Sigmoid : Activation
{
	double ActivationFunction(double weightedInput) override {
		return 1 / (1 + std::exp(-weightedInput));
	}

	double ActivationFunctionDerivative(double weightedInput) override {
		double activation = ActivationFunction(weightedInput);
		return activation * (1 - activation);
	}
};
