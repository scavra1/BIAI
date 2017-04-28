#include "stdafx.h"
#include "NeuralNetwork.h"

double NeuralNetwork::beta = 1.0;
double NeuralNetwork::activationFunction(double x) {
	return 1 / (1 + exp(-NeuralNetwork::beta * x));
}

NeuralNetwork::NeuralNetwork(std::vector<unsigned int> neuronNumbers) {
	if (neuronNumbers.size() < 1) {
		throw new std::exception("Network must have at least one layer");
	}

	for (int i = 1; i < neuronNumbers.size(); i++) {	//Start from 1 because input layer don't need to be stored
		this->layers.push_back(Layer(neuronNumbers[i - 1], neuronNumbers[i]));
	}
}

NeuralNetwork::~NeuralNetwork() {}

std::vector<double> NeuralNetwork::getOutputValues(std::vector<double> inputValues) {
	this->lastInputValues = inputValues;
	std::vector<double> values = this->layers[0].getOutputValues(inputValues);
	for (int i = 1; i < this->layers.size(); i++) {
		values = this->layers[i].getOutputValues(values);
	}
	return values;
}

void NeuralNetwork::train(std::vector<double> expectedOutputs, double learningCoeff, double momentumCoeff) {	//Call getOutputValues before
	//Calculate deltas for the last layer
	this->layers[this->layers.size() - 1].calculateDeltasBasedOnExpectedOutputs(expectedOutputs);
	std::vector<double> sumsOfWeightedDeltas = this->layers[this->layers.size() - 1].calculateSumsOfWeightedDeltas();

	//Calculate deltas for the remaining layers
	for (int i = this->layers.size() - 2; i >= 0; i--) {
		this->layers[i].calculateDeltas(sumsOfWeightedDeltas);
		sumsOfWeightedDeltas = this->layers[this->layers.size() - 1].calculateSumsOfWeightedDeltas();
	}

	//Adjust weights for the first (not input) layer
	this->layers[0].adjustWeights(learningCoeff, momentumCoeff, this->lastInputValues);

	//Adjust weights for the remaining layers
	for (int i = 1; i < this->layers.size(); i++) {
		this->layers[i].adjustWeights(learningCoeff, momentumCoeff, this->layers[i - 1].getLastOutputValues());
	}
}

double NeuralNetwork::getError(std::vector<double> expectedOutputs) {
	double error = 0.0;
	std::vector<double> lastOutputs = this->layers[this->layers.size() - 1].getLastOutputValues();
	for (int i = 0; i < expectedOutputs.size(); i++) {
		error += pow(lastOutputs[i] - expectedOutputs[i], 2);
	}
	error /= 2;
	return error;
}
