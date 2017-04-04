#pragma once
#include <Vector>
#include "Neuron.h"

class Layer {
public:
	Layer(unsigned int neuronsNumber);
	~Layer();
	int getNeuronsNumber();
	void projectLayer(Layer* layer);
	virtual std::vector<double> getOutputValues();
	void calculateDeltasBasedOnExpectedValues(std::vector<double> expectedOutputs);
	virtual void calculateDeltas(std::vector<double> nextLayerDeltas);
	void adjustWeights(double learningCoeff, double momentumCoeff, std::vector<double> previousLayerOutputValues);
protected:
	Layer* previousLayer = NULL;
	Layer* nextLayer = NULL;
	void setNextLayer(Layer* layer) { this->nextLayer = layer; };
private:
	std::vector<double> calculateSumsOfWeightedDeltas();
	std::vector<double> lastOutputValues;
	std::vector<Neuron*> neurons;
};

