#pragma once
#include <vector>

class Layer
{
public:
	Layer();
	Layer(int prevLayerNeuronsNumber, int neuronsNumber);	//Init weights
	Layer(std::vector<std::vector<double>> weights);
	~Layer();
	std::vector<double> getOutputValues(std::vector<double> inputValues);
	void calculateDeltas(std::vector<double> nextLayerDeltasWeightedSums);
	void calculateDeltasBasedOnExpectedOutputs(std::vector<double> expectedOutputs);
	void adjustWeights(double learningCoeff, double momentumCoeff, std::vector<double> previousLayerOutputValues);
	std::vector<double> calculateSumsOfWeightedDeltas();
	std::vector<double> getLastOutputValues() { return this->lastOutputValues; };
	std::vector<std::vector<double>> getWeights() { return this->weights; };
	int getNeuronsNumber() { return this->weights.size(); };
	int getPrevLayerNeuronsNumber() { return this->weights.size() > 0 ? this->weights[0].size() - 1 : 0; };
protected:
	std::vector<std::vector<double>> weights;
	std::vector<std::vector<double>> lastWeightsChanges;
	std::vector<double> deltas;
	std::vector<double> lastOutputValues;
};

