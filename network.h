//network.h
#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.h"
#include "edge.h"
#include <string>
using namespace std;

class Network{
    private:
        vector<vector<Neuron *> > graph;
        vector<vector<float> > data;
        void loadInput(int index);
        void forwardPropagation();
        float lossFunction();
        void backwardPropagation();
        float sigmoid(float value);

    public:
        Network(int NUM_LAYERS, vector<int> NUM_NEURONS);
        void loadData(string path,string delimiter);
        vector<vector<float> > getData();
        void train(); 
        void printData();
        void printNetwork();
};

#endif
