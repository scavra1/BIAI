#include "stdafx.h"
#include "NeuralNetwork.h"
#include "Layer.h"


Layer::Layer() {}

Layer::Layer(int prevLayerNeuronsNumber, int neuronsNumber) {
	if (neuronsNumber < 1 || prevLayerNeuronsNumber < 1) {
		throw new std::exception("Layer must have at least one neuron");
	}

	//Weights initialization range
	double minW = -1.0;
	double maxW = +1.0;

	this->lastOutputValues.resize(neuronsNumber);
	this->deltas.resize(neuronsNumber);
	this->weights.resize(neuronsNumber);
	for (int i = 0; i < neuronsNumber; i++) {
		this->weights[i].resize(prevLayerNeuronsNumber + 1);	//+1 because of bias neuron
		for (int j = 0; j < prevLayerNeuronsNumber + 1; j++) {
			double weight = minW + (maxW - minW) * ((double)rand() / RAND_MAX);
			this->weights[i][j] = weight;
		}
	}
}


Layer::~Layer() {}

std::vector<double> Layer::getOutputValues(std::vector<double> inputValues) {
	for (int i = 0; i < this->weights.size(); i++) {
		double sum = 0;
		sum += this->weights[i][0] * 1.0;		//Bias neuron
		for (int j = 1; j < this->weights[i].size(); j++) {
			sum += this->weights[i][j] * inputValues[j - 1];
		}
		this->lastOutputValues[i] = NeuralNetwork::activationFunction(sum);
	}
	return this->lastOutputValues;
}

void Layer::calculateDeltas(std::vector<double> nextLayerDeltasWeightedSums) {
	for (int i = 0; i < this->deltas.size(); i++) {
		this->deltas[i] = NeuralNetwork::beta * this->lastOutputValues[i] * (1.0 - this->lastOutputValues[i]) * nextLayerDeltasWeightedSums[i];
	}
}

void Layer::calculateDeltasBasedOnExpectedOutputs(std::vector<double> expectedOutputs) {
	for (int i = 0; i < this->deltas.size(); i++) {
		this->deltas[i] = NeuralNetwork::beta * this->lastOutputValues[i] * (1.0 - this->lastOutputValues[i]) * (expectedOutputs[i] - this->lastOutputValues[i]);
	}
}

void Layer::adjustWeights(double learningCoeff, double momentumCoeff, std::vector<double> previousLayerOutputValues) {
	for (int i = 0; i < this->weights.size(); i++) {
		this->weights[i][0] += learningCoeff * this->deltas[i] * 1.0;
		for (int j = 1; j < this->weights[i].size(); j++) {
			this->weights[i][j] += learningCoeff * this->deltas[i] * previousLayerOutputValues[j - 1];
		}
	}
}

std::vector<double> Layer::calculateSumsOfWeightedDeltas() {
	std::vector<double> sumsOfWeightedDeltas;
	for (int j = 1; j < this->weights[0].size(); j++) {	//Iterate over previous layer neurons (without bias neuron)
		double sum = 0;
		for (int i = 0; i < this->weights.size(); i++) {	//Iterate over current layer neurons
			sum += this->weights[i][j] * this->deltas[i];
		}
		sumsOfWeightedDeltas.push_back(sum);
	}
	return sumsOfWeightedDeltas;
}
