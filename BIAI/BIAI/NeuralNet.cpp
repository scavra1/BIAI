#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#include "Neuron.h"
#include "NeuralNetwork.h"

using namespace std;

vector<vector<double>> OUTPUT_VALUES = {
	{ 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 }
};
struct TrainingData {
	vector<vector<double>> trainingInputValues;
	vector<vector<double>> trainingOutputValues;
	vector<vector<double>> testingInputValues;
	vector<vector<double>> testingOutputValues;
};
TrainingData getTrainingDataFromFiles(string path) {
	TrainingData data;
	ifstream file;
	for (int digit = 0; digit <= 9; digit++) {
		file.open(path + string("digit") + to_string(digit) + string(".txt"));
		if (file.fail()) {
			cout << "File cannot be opened" << endl;
		}
		int i = 0;
		for (std::string line; getline(file, line) && i++ < 10; )
		{
			vector<double> vec;
			for (int i = 0; i < line.size(); i++) {
				vec.push_back(line[i] == '0' ? 0.0 : 1.0);
			}
			data.trainingInputValues.push_back(vec);
			data.trainingOutputValues.push_back(OUTPUT_VALUES[digit]);
		}
		file.close();
	}
	return data;
}

void presentResults(NeuralNetwork neuralNet, vector<vector<double>> trainingInputValues, vector<vector<double>> trainingOutputValues) {
	for (int i = 0; i < trainingInputValues.size(); i++) {
		neuralNet.setInputValues(trainingInputValues[i]);
		double output = neuralNet.getOutputValues()[1];
		double E = neuralNet.getError();
		cout << "f(" << trainingInputValues[i][0] << ", " << trainingInputValues[i][1] << ") = " << output << " | E = " << E << endl;
	}
}
void trainNetwork(string outputFile, NeuralNetwork neuralNet, vector<vector<double>> trainingInputValues, vector<vector<double>> trainingOutputValues, double trainingCoeff, double momentumCoeff) {
	ofstream file;
	file.open(outputFile);
	file << "var networkErrors = [\n";

	int maxIterations = 20;
	double error = 999.0;
	double targetError = 0.01;
	int iteration = 0;
	while (error > targetError && iteration < maxIterations) {
		iteration++;
		cout << "Iteration #" << iteration << endl;
		error = 0.0;
		for (int i = 0; i < trainingInputValues.size(); i++) {
			neuralNet.setInputValues(trainingInputValues[i]);
			neuralNet.setExpectedOutputValues(trainingOutputValues[i]);
			double output = neuralNet.getOutputValues()[1];
			double E = neuralNet.getError();
			error += E*E;
			neuralNet.train(trainingCoeff, momentumCoeff);
		}
		error /= 2;
		file << error << ((error > targetError && iteration < maxIterations) ? "," : "];") << "\n";
	}
	cout << endl << "Learning coefficient: " << trainingCoeff << endl;
	cout << "Momentum coefficient: " << momentumCoeff << endl;
	cout << "Error: " << error << endl;
	cout << "Iterations: " << iteration << endl;
	file.close();
}
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
	
	//-----------------------------------------------DIGITS--------------------------------------------------
	//Training set:
	TrainingData data = getTrainingDataFromFiles(trainingDataFilePath);
	double trainingCoeff = 0.5;
	double momentumCoeff = 0.0;
	NeuralNetwork neuralNet({ 28*28, 7*7, 10 });
	trainNetwork(chartDataFilePath, neuralNet, data.trainingInputValues, data.trainingOutputValues, trainingCoeff, momentumCoeff);

	system("PAUSE");
    return 0;
}