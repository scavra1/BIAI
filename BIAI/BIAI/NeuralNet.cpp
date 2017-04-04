#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#include "Neuron.h"
#include "NeuralNetwork.h"

using namespace std;
void presentResults(NeuralNetwork neuralNet, vector<vector<double>> trainingInputValues, vector<vector<double>> trainingOutputValues) {
	for (int i = 0; i < trainingInputValues.size(); i++) {
		neuralNet.setInputValues(trainingInputValues[i]);
		double output = neuralNet.getOutputValues()[1];
		double E = trainingOutputValues[i][0] - output;
		cout << "f(" << trainingInputValues[i][0] << ", " << trainingInputValues[i][1] << ") = " << output << " | E = " << E << endl;
	}
}
void trainNetwork(string outputFile, NeuralNetwork neuralNet, vector<vector<double>> trainingInputValues, vector<vector<double>> trainingOutputValues, double trainingCoeff) {
	ofstream file;
	file.open(outputFile);
	file << "var networkErrors = [\n";

	cout << "Before training: " << endl;
	presentResults(neuralNet, trainingInputValues, trainingOutputValues);

	int maxIterations = 8000;
	double error = 999.0;
	double targetError = 0.01;
	int iteration = 0;
	while (error > targetError && iteration < maxIterations) {
		iteration++;
		error = 0.0;
		for (int i = 0; i < trainingInputValues.size(); i++) {
			neuralNet.setInputValues(trainingInputValues[i]);
			neuralNet.setExpectedOutputValues(trainingOutputValues[i]);
			double output = neuralNet.getOutputValues()[1];
			double E = trainingOutputValues[i][0] - output;
			error += E*E;
			neuralNet.train(trainingCoeff);
		}
		error /= 2;
		file << error << ((error > targetError && iteration < maxIterations) ? "," : "];") << "\n";
	}
	cout << endl << "Learning coefficien: " << trainingCoeff << endl;
	cout << "Error: " << error << endl;
	cout << "Iterations: " << iteration << endl;
	file.close();

	cout << endl << "After training: " << endl;
	presentResults(neuralNet, trainingInputValues, trainingOutputValues);
}
int main(int argc, char* argv[]) {
	string filePath = "../../charts/learningData.js";
	srand((unsigned)time(NULL));
	
	//*
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
	double trainingCoeff = 0.1;
	NeuralNetwork neuralNet({ 2, 2, 1 });
	trainNetwork(filePath, neuralNet, trainingInputValues, trainingOutputValues, trainingCoeff);
	//*/

	/*
	//-----------------------------------------------AND--------------------------------------------------
	//Training set:
	vector<vector<double>> trainingInputValues = {
		{ 0.0, 0.0 },
		{ 1.0, 0.0 },
		{ 0.0, 1.0 },
		{ 1.0, 1.0 }
	};
	vector<vector<double>> trainingOutputValues = {
		{ 0.0 },
		{ 0.0 },
		{ 0.0 },
		{ 1.0 }
	};
	double trainingCoeff = 0.1;
	NeuralNetwork neuralNet({ 2, 1 });
	trainNetwork(filePath, neuralNet, trainingInputValues, trainingOutputValues, trainingCoeff);
	
	//*/
	system("PAUSE");
    return 0;
}