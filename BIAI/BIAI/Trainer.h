#pragma once
#include "NeuralNetwork.h"

struct TrainingResult {
	int iterations;
	double error;
	std::vector<double> errorsList;
};

class Trainer
{
public:
	Trainer(NeuralNetwork* neuralNetwork) : neuralNetwork(neuralNetwork) {};
	~Trainer();
	void setTrainingDataSet(std::vector<std::vector<double>> trainingInputValues, std::vector<std::vector<double>> trainingOutputValues);
	void setTestDataSet(std::vector<std::vector<double>> testInputValues, std::vector<std::vector<double>> testOutputValues);
	TrainingResult train(double trainingCoeff, double momentumCoeff, double targetError, int maxIterations);
protected:
	NeuralNetwork* neuralNetwork;
	std::vector<std::vector<double>> trainingInputValues;
	std::vector<std::vector<double>> trainingOutputValues;
	std::vector<std::vector<double>> testInputValues;
	std::vector<std::vector<double>> testOutputValues;
};