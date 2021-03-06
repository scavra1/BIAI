#pragma once
#include "Layer.h"
#include <vector>

class NeuralNetwork {
public:
	NeuralNetwork(std::string fileName) { this->loadFromFile(fileName); };
	NeuralNetwork(std::vector<unsigned int> neuronNumbers);
	~NeuralNetwork();
	std::vector<double> getOutputValues(std::vector<double> inputValues);
	void train(std::vector<double> expectedOutputs, double learningCoeff, double momentumCoeff);
	double getError(std::vector<double> expectedOutputs);
	int getOutputIndexWithHighestValue();
	void saveToFile(std::string fileName);
	void loadFromFile(std::string fileName);
	static double activationFunction(double x);
	static double beta;
protected:
	std::vector<Layer> layers;
	std::vector<double> lastInputValues;
};