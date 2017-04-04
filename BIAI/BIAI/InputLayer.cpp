#include "stdafx.h"
#include "InputLayer.h"

std::vector<double> InputLayer::getOutputValues() {
	return this->inputValues;
}

void InputLayer::setInputValues(std::vector<double> values) {
	this->inputValues = values;
	std::vector<double>::iterator it;
	it = this->inputValues.begin();
	it = this->inputValues.insert(it, 1.0);
	//this->inputValues.insert(0, 1.0, 1);
}

void InputLayer::calculateDeltas(std::vector<double> nextLayerDeltas) {
	//Do nothing
}

void InputLayer::adjustWeights(double learningCoeff) {
	this->nextLayer->adjustWeights(learningCoeff, this->inputValues);
}
