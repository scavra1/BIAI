#include "stdafx.h"
#include "Trainer.h"

Trainer::~Trainer() {}

void Trainer::setTrainingDataSet(std::vector<std::vector<double>> trainingInputValues, std::vector<std::vector<double>> trainingOutputValues) {
	this->trainingInputValues = trainingInputValues;
	this->trainingOutputValues = trainingOutputValues;
}

void Trainer::setTestDataSet(std::vector<std::vector<double>> testInputValues, std::vector<std::vector<double>> testOutputValues) {
	this->testInputValues = testInputValues;
	this->testOutputValues = testOutputValues;
}

TrainingResult Trainer::train(double targetError, int maxIterations) {		//Returns number of iterations
	TrainingResult result;
	double error;
	int iterations = maxIterations;
	for (int i = 0; i < maxIterations; i++) {
		error = 0;
		for (int j = 0; j < trainingInputValues.size(); j++) {
			neuralNetwork->getOutputValues(trainingInputValues[j]);
			neuralNetwork->train(trainingOutputValues[j], 0.4, 0.0);
			error += neuralNetwork->getError(trainingOutputValues[j]);
		}
		if (error < targetError) {
			iterations = i;
			break;
		}
	}
	result.error = error;
	result.iterations = iterations;
	return result;
}
