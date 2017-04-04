#include "stdafx.h"
#include "NeuralNetwork.h"
#include "Layer.h"

NeuralNetwork::NeuralNetwork(std::vector<unsigned int> neuronNumbers) {
	Layer* layer = new Layer(neuronNumbers[neuronNumbers.size() - 1]);
	this->outputLayer = layer;
	for (int i = neuronNumbers.size() - 2; i > 0; i--) {
		Layer* newLayer = new Layer(neuronNumbers[i]);
		layer->projectLayer(newLayer);
		layer = newLayer;
	}
	this->inputLayer = new InputLayer(neuronNumbers[0]);
	layer->projectLayer(this->inputLayer);
}

NeuralNetwork::~NeuralNetwork() {

}

void NeuralNetwork::setInputValues(std::vector<double> values) {
	this->inputLayer->setInputValues(values);
}

std::vector<double> NeuralNetwork::getOutputValues() {
	return this->outputLayer->getOutputValues();
}

void NeuralNetwork::setExpectedOutputValues(std::vector<double> values) {
	this->expectedOutputValues = values;
}

void NeuralNetwork::train(double learningCoeff, double momentumCoeff) {
	this->outputLayer->calculateDeltasBasedOnExpectedValues(this->expectedOutputValues);
	this->inputLayer->adjustWeights(learningCoeff, momentumCoeff);
}
