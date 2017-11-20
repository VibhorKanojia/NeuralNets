//neuron.h
#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Edge;

class Neuron{
    private:
        float val;
        float error; //used for backpropagation
        std::vector<Edge *> inList;
        std::vector<Edge *> outList;

    public:
        Neuron(float val);
        float getVal();
        void setVal(float new_val);
        void setError(float new_error);
        float getError();
        void addInEdge(Edge * in);
        void addOutEdge(Edge * out);
        std::vector<Edge *> getInEdgeList();
        std::vector<Edge *> getOutEdgeList();
};

#endif
