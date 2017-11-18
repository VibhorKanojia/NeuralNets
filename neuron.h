//neuron.h
#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Edge;

class Neuron{
    private:
        float val;
        std::vector<Edge *> inList;
        std::vector<Edge *> outList;

    public:
        Neuron(float val);
        float getVal();
        void setVal(float newval);
        void addInEdge(Edge * in);
        void addOutEdge(Edge * out);
        std::vector<Edge *> getInEdgeList();
        std::vector<Edge *> getOutEdgeList();
};

#endif
