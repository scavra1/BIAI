#include "stdafx.h"
#include "BiasNeuron.h"


BiasNeuron::BiasNeuron() {

}


BiasNeuron::~BiasNeuron() {

}

double BiasNeuron::getOutputValue(std::vector<double> inputValues) {
	return 1.0;
}
