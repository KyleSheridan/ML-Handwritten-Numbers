#pragma once
#include <math.h>

enum class CostFunctionType {
	MEAN_SQUARE,
	CROSS_ENTORPY
};

struct Cost
{
	virtual double CostFunction(double outputActivation, double expectedOutput) = 0;
	virtual double CostDerivative(double outputActivation, double expectedOutput) = 0;
};

struct MeanSquare : Cost
{
	double CostFunction(double outputActivation, double expectedOutput) override {
		double error = outputActivation - expectedOutput;
		return error * error;
	}

	double CostDerivative(double outputActivation, double expectedOutput) override {
		return 2 * (outputActivation - expectedOutput);
	}
};

struct CrossEntropy : Cost
{
	double CostFunction(double outputActivation, double expectedOutput) override {
		double v = (expectedOutput == 1) ? -log(outputActivation) : -log(1 - outputActivation);
		return v;
	}

	double CostDerivative(double outputActivation, double expectedOutput) override {
		if (outputActivation == 0 || outputActivation == 1) {
			return 0;
		}
		return (expectedOutput - outputActivation) / (outputActivation * (outputActivation - 1));
	}
};