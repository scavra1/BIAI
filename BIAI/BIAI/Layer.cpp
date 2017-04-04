#include "stdafx.h"
#include <Vector>
#include "Neuron.h"
#include "BiasNeuron.h"
#include "Layer.h"

Layer::Layer(unsigned int neuronsNumber) {
	this->neurons.push_back(new BiasNeuron());
	for (int i = 0; i < neuronsNumber; i++) {
		this->neurons.push_back(new Neuron());
	}
}

Layer::~Layer() {

}

int Layer::getNeuronsNumber() {
	return this->neurons.size();
}

void Layer::projectLayer(Layer * layer) {
	this->previousLayer = layer;

	int n = this->previousLayer->getNeuronsNumber();
	for (int i = 1; i < this->neurons.size(); i++) {
		for (int j = 0; j < n; j++) {
			this->neurons[i]->addWeight(-1.0, 1.0);
		}
	}
	this->previousLayer->setNextLayer(this);
}

std::vector<double> Layer::getOutputValues() {
	std::vector<double> previousLayerOutputValues = this->previousLayer->getOutputValues();
	std::vector<double> outputs;
	for (int i = 0; i < this->neurons.size(); i++) {
		outputs.push_back(this->neurons[i]->getOutputValue(previousLayerOutputValues));
	}
	this->lastOutputValues = outputs;
	return outputs;
}

void Layer::calculateDeltasBasedOnExpectedValues(std::vector<double> expectedOutputs) {
	for (int i = 1; i < this->neurons.size(); i++) {
		this->neurons[i]->calculateDelta(this->lastOutputValues[i], expectedOutputs[i-1] - this->lastOutputValues[i]);
	}
	this->previousLayer->calculateDeltas(this->calculateSumsOfWeightedDeltas());
}

void Layer::calculateDeltas(std::vector<double> nextLayerDeltasWeightedSums) {
	for (int i = 1; i < this->neurons.size(); i++) {
		this->neurons[i]->calculateDelta(this->lastOutputValues[i], nextLayerDeltasWeightedSums[i]);
	}
}

void Layer::adjustWeights(double learningCoeff, std::vector<double> previousLayerOutputValues) {
	int size = this->neurons.size();
	for (int i = 1; i < size; i++) {
		this->neurons[i]->adjustWeights(learningCoeff, previousLayerOutputValues);
	}
	if (this->nextLayer != NULL) {
		this->nextLayer->adjustWeights(learningCoeff, this->lastOutputValues);
	}
}

std::vector<double> Layer::calculateSumsOfWeightedDeltas() {
	std::vector<double> sums;
	int m = this->previousLayer->getNeuronsNumber();
	int n = this->getNeuronsNumber();
	for (int i = 0; i < m; i++) {
		sums.push_back(0.0);
	}
	for (int j = 1; j < n; j++) {
		double delta = this->neurons[j]->getDelta();
		std::vector<double> weights = this->neurons[j]->getWeights();
		for (int i = 0; i < m; i++) {
			sums[i] += delta * weights[i];
		}
	}
	return sums;
}
