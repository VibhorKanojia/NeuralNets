#include "network.h"
#include <vector>
#include <iostream>
using namespace std;

float LEARNING_RATE = 0.5;
int EPOCHS = 20000;
int NUM_INPUTS = 8;
int NUM_OUTPUTS = 3;
int NUM_LAYERS = 3;

int main(){
    vector<int> num_neurons;
    num_neurons.push_back(NUM_INPUTS);
    num_neurons.push_back(10);
    //num_neurons.push_back(6);
    num_neurons.push_back(NUM_OUTPUTS);

    Network * nn = new Network(NUM_LAYERS, num_neurons);
    nn->train("data/train.csv", ",", EPOCHS, LEARNING_RATE); 
    float accuracy = nn->test("data/test.csv",",");
    cout<<"Accuracy :"<<accuracy<<endl;
    return 0;
}
