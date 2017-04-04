#include "stdafx.h"
#include "Neuron.h"
#include <math.h>

double Neuron::beta = 4.0;
Neuron::Neuron() {

}

Neuron::~Neuron() {

}

double Neuron::activationFunction(double x) {
	double beta = Neuron::beta;
	return 1 / (1 + exp(-beta * x));
}

void Neuron::addWeight(double weight) {
	this->weights.push_back(weight);
	this->lastWeightChanges.push_back(0.0);
}

void Neuron::addWeight(double min, double max) {
	double weight = min + (max - min) * ((double)rand() / RAND_MAX);
	this->addWeight(weight);
}

double Neuron::getOutputValue(std::vector<double> inputValues) {
	double sum = 0;
	for (int i = 0; i < inputValues.size(); i++) {
		sum += this->weights[i] * inputValues[i];
	}
	return this->activationFunction(sum);
}

void Neuron::calculateDelta(double lastOutput, double variableTerm) {
	this->delta = Neuron::beta * lastOutput * (1 - lastOutput) * variableTerm;
}

void Neuron::adjustWeights(double learningCoeff, double momentumCoeff, std::vector<double> inputValues) {
	for (int i = 0; i < this->weights.size(); i++) {
		double weightChange = learningCoeff * this->delta * inputValues[i] + momentumCoeff * this->lastWeightChanges[i];
		this->weights[i] += weightChange;
		this->lastWeightChanges[i] = weightChange;
	}
}
