#pragma once
#include <vector>
#include "InputLayer.h"

class NeuralNetwork {
public:
	NeuralNetwork(std::vector<unsigned int> neuronNumbers);
	~NeuralNetwork();
	void setInputValues(std::vector<double> values);
	std::vector<double> getOutputValues();
	void setExpectedOutputValues(std::vector<double> values);
	void train(double learningCoeff, double momentumCoeff);
	//std::vector<double> getErrors();
	//double getError();
private:
	InputLayer* inputLayer;
	Layer* outputLayer;
	std::vector<double> expectedOutputValues;
};

