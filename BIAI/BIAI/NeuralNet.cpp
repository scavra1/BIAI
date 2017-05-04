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
	string trainingDataFilePath, testDataFilePath, neuralNetworkFilePath, learningParamsFilePath, saveTrainedNetwork, saveNetworkFilePath, chartDataFilePath;
	if (argc < 6) {
		cout << "Argument is missing!" << endl;
		return 0;
	}
	else {
		neuralNetworkFilePath = argv[1];
		trainingDataFilePath = argv[2];
		testDataFilePath = argv[3];
		learningParamsFilePath = argv[4];
		chartDataFilePath = argv[5];
		if (argc >= 8) {
			saveTrainedNetwork = argv[6];
			saveNetworkFilePath = argv[7];
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
	trainer.loadTestSetFromFile(testDataFilePath);

	TrainingResult result = trainer.train(learningCoeff, momentumCoeff, targetError, maxIterations, true);
	Trainer::saveTrainingDataAsJSArray(chartDataFilePath, result.errorsList, result.correctnessList);

	cout << "Iterations = " << result.iterations << endl;
	cout << "Error = " << result.error << endl;

	if (saveTrainedNetwork == "y") {
		neuralNet.saveToFile(saveNetworkFilePath);
	}

	system("PAUSE");
    return 0;
}