#include "network.h"
#include <vector>

int main(){
    int num_layers = 3;
    std::vector<int> num_neurons(3,0);
    num_neurons[0] = 3;
    num_neurons[1] = 2;
    num_neurons[2] = 1;
    
    Network * nn = new Network(num_layers, num_neurons);
    //nn->printNetwork();
    nn->loadData("data/IRIS.csv", ",");
    nn->printData();
    return 0;
}
