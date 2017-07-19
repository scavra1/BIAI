#include "stdafx.h"
#include "Trainer.h"
#include <fstream>
#include <iostream>
#include <iomanip>

Trainer::~Trainer() {}

void Trainer::setTrainingDataSet(std::vector<std::vector<double>> trainingInputValues, std::vector<std::vector<double>> trainingOutputValues) {
	this->trainingInputValues = trainingInputValues;
	this->trainingOutputValues = trainingOutputValues;
}

void Trainer::setTestDataSet(std::vector<std::vector<double>> testInputValues, std::vector<std::vector<double>> testOutputValues) {
	this->testInputValues = testInputValues;
	this->testOutputValues = testOutputValues;
}

TrainingResult Trainer::train(double trainingCoeff, double momentumCoeff, double targetError, int maxIterations, bool log) {
	std::vector<double> errorsList;
	std::vector<double> correctnessList;
	double error;
	double correctness;
	int iterations = maxIterations;
	for (int i = 0; i < maxIterations; i++) {
		error = 0.0;
		correctness = 0.0;
		for (int j = 0; j < this->testInputValues.size(); j++) {
			neuralNetwork->getOutputValues(this->testInputValues[j]);
			error += neuralNetwork->getError(this->testOutputValues[j]);

			int index = neuralNetwork->getOutputIndexWithHighestValue();
			if (this->testOutputValues[j][index] > 0.9) {
				correctness += 1;
			}
		}
		correctness /= this->testInputValues.size();
		error /= this->testInputValues.size();
		errorsList.push_back(error);
		correctnessList.push_back(correctness);
		if (error < targetError) {
			iterations = i;
			break;
		}
		if (log) {
			std::cout << std::fixed << std::setprecision(6)
				<< "Iteration " << i
				<< ", Error: " << error
				<< " Classification correctness: " << std::fixed << std::setprecision(2) << (100 * correctness) << "%" << std::endl;
		}

		//Train
		const int parts = 100;
		int partSize = this->trainingInputValues.size() / parts;
		int part = i % parts;
		int startIndex = part * partSize;
		int endIndex = startIndex + partSize;
		for (int j = startIndex; j < endIndex; j++) {
			neuralNetwork->getOutputValues(this->trainingInputValues[j]);
			neuralNetwork->train(this->trainingOutputValues[j], trainingCoeff, momentumCoeff);
		}
	}
	return { iterations, error, errorsList, correctnessList };
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

void Trainer::saveTrainingDataAsJSArray(std::string fileName, std::vector<double> errorsList, std::vector<double> correctnessList) {
	std::ofstream file(fileName);

	file << "var networkErrors = [";
	for (int i = 0; i < errorsList.size(); i++) {
		file << std::fixed << std::setprecision(6) << errorsList[i];
		if (i != (errorsList.size() - 1)) {
			file << ",";
		}
	}
	file << "];" << std::endl;

	file << "var networkCorrectness = [";
	for (int i = 0; i < correctnessList.size(); i++) {
		file << std::fixed << std::setprecision(6) << correctnessList[i];
		if (i != (correctnessList.size() - 1)) {
			file << ",";
		}
	}
	file << "];" << std::endl;

	file.close();
}
