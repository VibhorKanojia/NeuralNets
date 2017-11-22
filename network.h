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
        void loadData(string path,string delimiter);
        bool isCorrect(int index);

    public:
        Network(int NUM_LAYERS, vector<int> NUM_NEURONS);
        vector<vector<float> > getData();
        void train(string path, string delimiter, int epochs, float learning_rate);
        float test(string path, string delimiter); 
        void printData();
        void printNetwork();
};

#endif
