//edge.h
#ifndef EDGE_H
#define EDGE_H

class Neuron;

class Edge{
    private:
        float val;
        Neuron * in;
        Neuron * out;
   public:
        Edge(float val, Neuron * in, Neuron * out);
        float getVal();
        void setVal(float newval);
        Neuron * getIn();
        Neuron * getOut();
};

#endif
