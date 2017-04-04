#pragma once
#include "Layer.h"

class InputLayer : public Layer {
public:
	using Layer::Layer;
	virtual std::vector<double> getOutputValues();
	void setInputValues(std::vector<double> values);
	virtual void calculateDeltas(std::vector<double> nextLayerDeltas);
	void adjustWeights(double learningCoeff, double momentumCoeff);
private:
	std::vector<double> inputValues;
};

