#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#include "NeuralNetwork.h"

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
	double error;
	int iterations = 10000;
	for (int i = 0; i < iterations; i++) {
		error = 0;
		for (int j = 0; j < trainingInputValues.size(); j++) {
			neuralNet.getOutputValues(trainingInputValues[j]);
			neuralNet.train(trainingOutputValues[j], 0.4, 0.0);
			error += neuralNet.getError(trainingOutputValues[j]);
		}
		if (error < 0.01) {
			iterations = i;
			break;
		}
	}

	for (int j = 0; j < trainingInputValues.size(); j++) {
		cout << neuralNet.getOutputValues(trainingInputValues[j])[0] << endl;
	}
	cout << "Iterations = " << iterations << endl;
	cout << "Error = " << error << endl;

	system("PAUSE");
    return 0;
}