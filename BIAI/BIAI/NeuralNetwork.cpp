#include "stdafx.h"
#include "NeuralNetwork.h"
#include <fstream>

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

int NeuralNetwork::getOutputIndexWithHighestValue() {
	int index = 0;
	double maxValue = 0;
	std::vector<double> lastOutputs = this->layers[this->layers.size() - 1].getLastOutputValues();
	for (int i = 1; i < lastOutputs.size(); i++) {
		if (lastOutputs[i] > maxValue) {
			maxValue = lastOutputs[i];
			index = i;
		}
	}
	return index;
}

void NeuralNetwork::saveToFile(std::string fileName) {
	/*
	Format:
	char readWeights //'y' or 'n'
	int Number_of_layers
	int Number_of_neurons_0
	int Number_of_neurons_1
		double w00 double w01 double w02 ...
		double w10 double w11 double w12 ...
		double w20 double w21 double w22 ...
		...
	...
	int Number_of_neurons_n
		double w00 double w01 double w02 ...
		double w10 double w11 double w12 ...
		double w20 double w21 double w22 ...
		...
	*/
	std::ofstream file(fileName);
	file << 'y' << std::endl;
	file << (this->layers.size() + 1) << std::endl;	//Number of layers. WITH input layer.
	file << this->layers[0].getPrevLayerNeuronsNumber() << std::endl;

	for (int i = 0; i < this->layers.size(); i++) {
		file << this->layers[i].getNeuronsNumber() << std::endl;
		std::vector<std::vector<double>> weights = this->layers[i].getWeights();
		for (int j = 0; j < weights.size(); j++) {
			for (int k = 0; k < weights[j].size(); k++) {
				file << weights[j][k] << " ";
			}
			file << std::endl;
		}
	}
	file.close();
}

void NeuralNetwork::loadFromFile(std::string fileName) {
	std::ifstream file(fileName);
	
	char readWeights;
	int layersNumber, prevLayerSize, currentLayerSize;

	file >> readWeights;
	file >> layersNumber;
	file >> currentLayerSize;

	for (int i = 1; i < layersNumber; i++) {
		prevLayerSize = currentLayerSize;
		file >> currentLayerSize;
		if (readWeights == 'y') {
			std::vector<std::vector<double>> weights;
			weights.resize(currentLayerSize);
			for (int j = 0; j < currentLayerSize; j++) {
				weights[j].resize(prevLayerSize + 1);
				for (int k = 0; k < prevLayerSize + 1; k++) {
					file >> weights[j][k];
				}
			}
			this->layers.push_back(Layer(weights));
		}
		else {
			this->layers.push_back(Layer(prevLayerSize, currentLayerSize));
		}
		
	}
	file.close();
}
