#include "stdafx.h"
#include "Trainer.h"
#include <fstream>

Trainer::~Trainer() {}

void Trainer::setTrainingDataSet(std::vector<std::vector<double>> trainingInputValues, std::vector<std::vector<double>> trainingOutputValues) {
	this->trainingInputValues = trainingInputValues;
	this->trainingOutputValues = trainingOutputValues;
}

void Trainer::setTestDataSet(std::vector<std::vector<double>> testInputValues, std::vector<std::vector<double>> testOutputValues) {
	this->testInputValues = testInputValues;
	this->testOutputValues = testOutputValues;
}

//Returns number of iterations
TrainingResult Trainer::train(double trainingCoeff, double momentumCoeff, double targetError, int maxIterations) {
	std::vector<double> errorsList;
	double error;
	int iterations = maxIterations;
	for (int i = 0; i < maxIterations; i++) {
		error = 0;
		for (int j = 0; j < trainingInputValues.size(); j++) {
			neuralNetwork->getOutputValues(trainingInputValues[j]);
			neuralNetwork->train(trainingOutputValues[j], trainingCoeff, momentumCoeff);
			error += neuralNetwork->getError(trainingOutputValues[j]);
		}
		errorsList.push_back(error);
		if (error < targetError) {
			iterations = i;
			break;
		}
	}
	return { iterations, error, errorsList };
}

void Trainer::loadDataSetFromFile(std::string fileName, std::vector<std::vector<double>> &inputValues, std::vector<std::vector<double>> &outputValues) {
	std::fstream file(fileName, std::ios_base::in);
	int examplesNumber, inputsNumber, outputsNumber;
	file >> examplesNumber;
	file >> inputsNumber;
	file >> outputsNumber;

	inputValues.resize(examplesNumber);
	outputValues.resize(examplesNumber);
	for (int i = 0; i < examplesNumber; i++) {
		inputValues[i].resize(inputsNumber);
		outputValues[i].resize(outputsNumber);

		//Read inputs
		for (int j = 0; j < inputsNumber; j++) {
			file >> inputValues[i][j];
		}

		//Read outputs
		for (int j = 0; j < outputsNumber; j++) {
			file >> outputValues[i][j];
		}
	}
	file.close();
}

void Trainer::loadTrainingSetFromFile(std::string fileName) {
	this->loadDataSetFromFile(fileName, this->trainingInputValues, this->trainingOutputValues);
}

void Trainer::loadTestSetFromFile(std::string fileName) {
	this->loadDataSetFromFile(fileName, this->testInputValues, this->testOutputValues);
}
