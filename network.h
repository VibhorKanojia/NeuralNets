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
        float lossFunction(int index);
        void backwardPropagation(float learning_rate);
        float sigmoid(float value);

    public:
        Network(int NUM_LAYERS, vector<int> NUM_NEURONS);
        void loadData(string path,string delimiter);
        vector<vector<float> > getData();
        void train(int epochs, float learning_rate); 
        void printData();
        void printNetwork();
};

#endif
