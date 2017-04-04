#pragma once
#include <Vector>

class Neuron {
public:
	Neuron();
	~Neuron();
	void addWeight(double weight);
	void addWeight(double min, double max);
	virtual double getOutputValue(std::vector<double> inputValues);
	double getDelta() { return this->delta; };
	std::vector<double> getWeights() { return this->weights; };
	void calculateDelta(double lastOutput, double variableTerm);
	void adjustWeights(double learningCoeff, double momentumCoeff, std::vector<double> inputValues);
	static double beta;
private:
	double activationFunction(double x);
	std::vector<double> weights;
	std::vector<double> lastWeightChanges;
	double delta;
};

