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
	NeuralNetwork neuralNet({ 2, 2, 1 });
	Trainer trainer(&neuralNet);
	trainer.loadTrainingSetFromFile(trainingDataFilePath);
	TrainingResult result = trainer.train(0.4, 0.0, 0.01, 10000);

	cout << "Iterations = " << result.iterations << endl;
	cout << "Error = " << result.error << endl;

	system("PAUSE");
    return 0;
}