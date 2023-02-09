#include "NeuralNetwork.h"

std::vector<double> NeuralNetwork::CalculateOutputs(std::vector<double> inputs)
{
	for(Layer* layer : layers)
	{
		inputs = layer->CalculateOutputs(inputs);
	}
	return inputs;
}

int NeuralNetwork::Classify(std::vector<double> inputs)
{
	std::vector<double> outputs = CalculateOutputs(inputs);

	double largest = DBL_MIN;

	for (double val : outputs) {
		if (val > largest) largest = val;
	}

	return largest;
}

void NeuralNetwork::UpdateAllGradients(DataPoint* dataPoint)
{
	CalculateOutputs(dataPoint->inputs);

	// Update gradients of the output layer
	Layer* outputLayer = layers[layers.size() - 1];
	std::vector<double> nodeValues = outputLayer->CalculateOutputLayerNodeValues(dataPoint->expectedOutputs);
	outputLayer->UpdateGradients(nodeValues);

	// Update gradients of the hidden layers
	for (int hiddenLayerIndex = layers.size() - 2; hiddenLayerIndex >= 0; hiddenLayerIndex--)
	{
		Layer* hiddenLayer = layers[hiddenLayerIndex];
		nodeValues = hiddenLayer->CalculateHiddenLayerNodeValues(layers[hiddenLayerIndex + 1], nodeValues);
		hiddenLayer->UpdateGradients(nodeValues);
	}
}

void NeuralNetwork::ApplyAllGradients(double learnRate)
{
	for (Layer* layer : layers) {
		layer->ApplyGradients(learnRate);
	}
}

void NeuralNetwork::ClearAllGradients()
{
	for (Layer* layer : layers) {
		layer->ClearGradients();
	}
}

int NeuralNetwork::TestNumber(DataPoint* dataPoint)
{
	std::vector<double> outputs = CalculateOutputs(dataPoint->inputs);

	int largest = -1;
	int index = 0;

	for (int i = 0; i < outputs.size(); i++)
	{
		if (outputs[i] > largest) {
			largest = outputs[i];
			index = i;
		}
	}

	return index;
}

int NeuralNetwork::IndexOfMaxValue(std::vector<double> arr)
{
	int index = -1;

	double largest = DBL_MIN;

	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > largest) {
			largest = arr[i];

			index = i;
		}
	}

	return index;
}

double NeuralNetwork::Cost(DataPoint* dataPoint)
{
	std::vector<double> outputs = CalculateOutputs(dataPoint->inputs);
	Layer* outputLayer = layers[layers.size() - 1];
	double cost = 0;

	for (int nodeOut = 0; nodeOut < outputs.size(); nodeOut++)
	{
		cost += outputLayer->cost->CostFunction(outputs[nodeOut], dataPoint->expectedOutputs[nodeOut]);
	}

	return cost;
}

int NeuralNetwork::LargestOutput(std::vector<double> outputs)
{
	double largest = DBL_MIN;
	int result = -1;

	for (int i = 0; i < outputs.size(); i++)
	{
		if (outputs[i] > largest) {
			largest = outputs[i];
			result = i;
		}
	}

	return result;
}

double NeuralNetwork::Cost(std::vector<DataPoint*> data)
{
	double totalCost = 0;

	for(DataPoint* dataPoint : data)
	{
		totalCost += Cost(dataPoint);
	}

	return totalCost / data.size();
}

void NeuralNetwork::Learn(std::vector<DataPoint*> trainingData, double learnRate)
{
	for (DataPoint* dataPoint : trainingData) {
		UpdateAllGradients(dataPoint);
	}

	ApplyAllGradients(learnRate / trainingData.size());

	ClearAllGradients();
}

double NeuralNetwork::Test(std::vector<DataPoint*> testingData)
{
	int numCorrect = 0;

	for (DataPoint* test : testingData) {
		std::vector<double> outputs = CalculateOutputs(test->inputs);

		if (test->expectedOutputs[LargestOutput(outputs)] == 1.0) {
			numCorrect++;
		}
	}

	double percentCorrect = (double)numCorrect / (double)testingData.size();

	return round(percentCorrect * 10000) / 100;
}

void NeuralNetwork::BatchLearn(std::vector<DataPoint*> trainingData, double learnRate, int batchSize)
{
	int NumBatches = trainingData.size() / batchSize;

	int percent = 0;

	for (int i = 0; i < NumBatches; i++)
	{
		if (i % (NumBatches / 100) == 0) {
			std::cout << "\rNetwork Learning: " << percent << "%";
			percent++;
		}

		MiniBatch(trainingData, (i * batchSize), batchSize, learnRate);
	}

	std::cout << "\rLearning Complete!\n";
}

void NeuralNetwork::BatchLearn(std::vector<DataPoint*> trainingData, std::vector<DataPoint*> testingData, double learnRate, int batchSize)
{
	int NumBatches = trainingData.size() / batchSize;

	int percent = 0;
	std::random_device rd;
	std::mt19937 g(rd());

	for (int i = 0; i < NumBatches; i++)
	{
		if (i % (NumBatches / 100) == 0) {
			percent++;
		}

		MiniBatch(trainingData, (i * batchSize), batchSize, learnRate);

		std::shuffle(testingData.begin(), testingData.end(), g);
		std::vector<DataPoint*> testBatch(testingData.begin(), testingData.begin() + 200);
		std::cout << "\rNetwork Learning: " << percent << "%  Success rate: " << Test(testBatch) << "%";
	}

	std::cout << "\rLearning Complete! \nFinal Success Rate: " << Test(testingData) << "%\n";
}

void NeuralNetwork::MiniBatch(std::vector<DataPoint*> trainingData, int startIndex, int batchSize, double learnRate)
{
	std::vector<DataPoint*>::const_iterator first = trainingData.begin() + startIndex;
	std::vector<DataPoint*>::const_iterator last = first + batchSize;

	Learn({ first, last }, learnRate);
}

void NeuralNetwork::PrintOutputs(std::vector<double> inputs)
{
	std::vector<double> outputs = CalculateOutputs(inputs);

	std::cout << std::setprecision(3);

	double total = 0.0;

	for (int i = 0; i < outputs.size(); i++) {
		outputs[i] = round(outputs[i] * 100) / 100;

		total += outputs[i];
	}

	for (int i = 0; i < outputs.size(); i++) {
		std::cout << i << ": " << (outputs[i] / total) * 100 << "%\n";
	}

	std::cout << std::endl;
}
