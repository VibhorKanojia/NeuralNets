//edge.cpp
#include "edge.h"

Edge::Edge(float weight, Neuron * in, Neuron * out){
    this->weight = weight;
    this->in = in;
    this->out = out;
}

float Edge::getWeight(){
    return weight;
}

void Edge::setWeight(float new_weight){
    this->weight = new_weight;
}

float Edge::getDelta(){
    return delta;
}

void Edge::setDelta(float new_delta){
    this->delta = new_delta;
}

Neuron * Edge::getIn(){
    return in;
}

Neuron * Edge::getOut(){
    return out;
}
