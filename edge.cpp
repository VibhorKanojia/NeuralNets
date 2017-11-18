//edge.cpp
#include "edge.h"

Edge::Edge(float val, Neuron * in, Neuron * out){
    this->val = val;
    this->in = in;
    this->out = out;
}

float Edge::getVal(){
    return val;
}

void Edge::setVal(float newval){
    this->val = newval;
}

Neuron * Edge::getIn(){
    return in;
}

Neuron * Edge::getOut(){
    return out;
}
