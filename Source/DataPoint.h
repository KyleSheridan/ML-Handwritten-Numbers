#pragma once
#include <iostream>
#include <vector>

#include "Number.h"

class DataPoint {
public:
	DataPoint() {}
	DataPoint(TrainingNumber* number) {
		inputs.reserve(784);
		expectedOutputs.reserve(10);

		for (int i = 0; i < 10; i++)
		{
			expectedOutputs.emplace_back(0.0);
		}

		for (short i = 0; i < 28; i++)
		{
			for (short j = 0; j < 28; j++)
			{
				inputs.emplace_back(number->image->pixels[i][j]);
			}
		}
		
		expectedOutputs[*number->value] = 1.0;
	}
	DataPoint(Number* number, int value) {
		inputs.reserve(784);
		expectedOutputs.reserve(10);

		for (int i = 0; i < 10; i++)
		{
			expectedOutputs.emplace_back(0.0);
		}

		for (short i = 0; i < 28; i++)
		{
			for (short j = 0; j < 28; j++)
			{
				inputs.emplace_back((double)number->pixels[i][j] / 255.0);
			}
		}

		expectedOutputs[value] = 1.0;
	}

	std::vector<double> inputs;
	std::vector<double> expectedOutputs;
};