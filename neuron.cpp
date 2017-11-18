//neuron.cpp
#include "neuron.h"

Neuron::Neuron(float val){
    this->val = val;
}

float Neuron::getVal(){
    return val;
}

void Neuron::setVal(float newval){
    this->val = newval;
    return;
}

void Neuron::addInEdge(Edge * in){
    inList.push_back(in);    
}

void Neuron::addOutEdge(Edge * out){
    outList.push_back(out);
}

std::vector<Edge *> Neuron::getInEdgeList(){
    return this->inList;
}

std::vector<Edge *> Neuron::getOutEdgeList(){
    return this->outList;
}


