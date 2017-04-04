#pragma once
#include "Neuron.h"

class BiasNeuron : public Neuron {
public:
	BiasNeuron();
	~BiasNeuron();
	virtual double getOutputValue(std::vector<double> inputValues);
};

