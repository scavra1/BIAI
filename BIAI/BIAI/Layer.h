#pragma once
#include <vector>

class Layer
{
public:
	Layer();
	Layer(int prevLayerNeuronsNumber, int neuronsNumber);	//Init weights
	~Layer();
	std::vector<double> getOutputValues(std::vector<double> inputValues);
	void calculateDeltas(std::vector<double> nextLayerDeltasWeightedSums);
	void calculateDeltasBasedOnExpectedOutputs(std::vector<double> expectedOutputs);
	void adjustWeights(double learningCoeff, double momentumCoeff, std::vector<double> previousLayerOutputValues);
	std::vector<double> calculateSumsOfWeightedDeltas();
	std::vector<double> getLastOutputValues() { return this->lastOutputValues; };
protected:
	std::vector<std::vector<double>> weights;
	std::vector<double> deltas;
	std::vector<double> lastOutputValues;
};

