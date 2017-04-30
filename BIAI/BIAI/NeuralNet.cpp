#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#include "NeuralNetwork.h"
#include "Trainer.h"

using namespace std;

void readLearningParamsFromFile(string fileName, double &learningCoeff, double &momentumCoeff, double &targetError, int &maxIterations) {
	std::ifstream file(fileName);
	file >> learningCoeff;
	file >> momentumCoeff;
	file >> targetError;
	file >> maxIterations;
	file.close();
}

int main(int argc, char* argv[]) {
	string chartDataFilePath = "../../charts/learningData.js";
	string trainingDataFilePath, neuralNetworkFilePath, learningParamsFilePath, saveTrainedNetwork, saveNetworkFilePath;
	if (argc < 4) {
		cout << "Argument is missing!" << endl;
		return 0;
	}
	else {
		neuralNetworkFilePath = argv[1];
		trainingDataFilePath = argv[2];
		learningParamsFilePath = argv[3];
		if (argc >= 6) {
			saveTrainedNetwork = argv[4];
			saveNetworkFilePath = argv[5];
		}
		else {
			saveTrainedNetwork = "n";
		}
	}
	srand((unsigned)time(NULL));

	double learningCoeff, momentumCoeff, targetError;
	int maxIterations;
	readLearningParamsFromFile(learningParamsFilePath, learningCoeff, momentumCoeff, targetError, maxIterations);

	NeuralNetwork neuralNet(neuralNetworkFilePath);
	Trainer trainer(&neuralNet);
	trainer.loadTrainingSetFromFile(trainingDataFilePath);

	TrainingResult result = trainer.train(learningCoeff, momentumCoeff, targetError, maxIterations);
	Trainer::saveErrorsAsJSArray(chartDataFilePath, result.errorsList);

	cout << "Iterations = " << result.iterations << endl;
	cout << "Error = " << result.error << endl;

	if (saveTrainedNetwork == "y") {
		neuralNet.saveToFile(saveNetworkFilePath);
	}

	system("PAUSE");
    return 0;
}