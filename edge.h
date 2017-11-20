//edge.h
#ifndef EDGE_H
#define EDGE_H

class Neuron;

class Edge{
    private:
        float weight;
        float delta; //change in weight value
        Neuron * in;
        Neuron * out;
   public:
        Edge(float weight, Neuron * in, Neuron * out);
        float getWeight();
        float getDelta();
        void setWeight(float new_weight);
        void setDelta(float new_delta);
        Neuron * getIn();
        Neuron * getOut();

};

#endif
