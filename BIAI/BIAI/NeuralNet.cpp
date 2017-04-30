#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#include "NeuralNetwork.h"
#include "Trainer.h"

using namespace std;

int main(int argc, char* argv[]) {
	string chartDataFilePath = "../../charts/learningData.js";
	string trainingDataFilePath, neuralNetworkFilePath, saveTrainedNetwork, saveNetworkFilePath;
	if (argc < 3) {
		cout << "Argument is missing!" << endl;
		return 0;
	}
	else {
		neuralNetworkFilePath = argv[1];
		trainingDataFilePath = argv[2];
		if (argc >= 5) {
			saveTrainedNetwork = argv[3];
			saveNetworkFilePath = argv[4];
		}
		else {
			saveTrainedNetwork = "n";
		}
	}
	srand((unsigned)time(NULL));

	NeuralNetwork neuralNet(neuralNetworkFilePath);
	Trainer trainer(&neuralNet);
	trainer.loadTrainingSetFromFile(trainingDataFilePath);
	TrainingResult result = trainer.train(0.4, 0.0, 0.01, 10000);
	Trainer::saveErrorsAsJSArray(chartDataFilePath, result.errorsList);

	cout << "Iterations = " << result.iterations << endl;
	cout << "Error = " << result.error << endl;

	if (saveTrainedNetwork == "y") {
		neuralNet.saveToFile(saveNetworkFilePath);
	}

	system("PAUSE");
    return 0;
}