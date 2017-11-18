//network.h
#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.h"
#include "edge.h"

class Network{
    private:
        std::vector< std::vector< Neuron *> > graph;

    public:
        Network(int NUM_LAYERS,  std::vector<int> NUM_NEURONS);       
        void printNetwork();
};

#endif
