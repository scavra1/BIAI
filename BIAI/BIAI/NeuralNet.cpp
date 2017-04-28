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
	string trainingDataFilePath;
	if (argc < 2) {
		cout << "Argument is missing!" << endl;
		return 0;
	}
	else {
		trainingDataFilePath = argv[1];
	}
	srand((unsigned)time(NULL));

	//-----------------------------------------------XOR--------------------------------------------------
	//Training set:
	std::vector<std::vector<double>> trainingInputValues = {
		{ 0.0, 0.0 },
		{ 1.0, 0.0 },
		{ 0.0, 1.0 },
		{ 1.0, 1.0 }
	};
	std::vector<std::vector<double>> trainingOutputValues = {
		{ 0.0 },
		{ 1.0 },
		{ 1.0 },
		{ 0.0 }
	};

	NeuralNetwork neuralNet({ 2, 2, 1 });
	Trainer trainer(&neuralNet);
	trainer.setTrainingDataSet(trainingInputValues, trainingOutputValues);
	TrainingResult result = trainer.train(0.4, 0.0, 0.01, 10000);

	for (int j = 0; j < trainingInputValues.size(); j++) {
		cout << neuralNet.getOutputValues(trainingInputValues[j])[0] << endl;
	}

	cout << "Iterations = " << result.iterations << endl;
	cout << "Error = " << result.error << endl;

	system("PAUSE");
    return 0;
}