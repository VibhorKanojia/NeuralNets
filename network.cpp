//network.cpp

//Step by step backpropagation: https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/

#include "network.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

Network::Network(int num_layers, vector<int> num_neurons){
    
    //Adding Neurons in the graph
    for (int i = 0 ; i < num_layers; i++){
        vector<Neuron *> layer;
        for(int j = 0 ; j < num_neurons[i]; j++){
            Neuron * node = new Neuron(0);
            layer.push_back(node);    
        }
        graph.push_back(layer);
    }

    srand(time(NULL));

    //Adding Edges between Neurons   
    for (int i = 0 ; i < num_layers -1; i++){
        for (int j = 0 ; j < num_neurons[i]; j++){
            for (int k = 0 ; k  < num_neurons[i+1]; k++){
                float randWeight = (float)( (rand()%100000)/100000.0) ;
                Edge * e = new Edge(randWeight, graph[i][j], graph[i+1][k]);
                graph[i][j]->addOutEdge(e);
                graph[i+1][k]->addInEdge(e);
            }
        }
    }
    
    //Adding bias node and edges
    Neuron * bias_node = new Neuron(1.0);
    for (int i = 1 ; i < num_layers ; i++){
        for (int j = 0; j < num_neurons[i]; j++){
            float randWeight = (float)( (rand()%100000)/100000.0) ;
            Edge * e = new Edge(randWeight, bias_node, graph[i][j]);
            bias_node->addOutEdge(e);
            graph[i][j]->addInEdge(e);
        }
    }
}

void Network::loadData(string path, string delimiter){
    ifstream myfile(path);
    string line;
    if (myfile.is_open()){
        while (getline(myfile, line)){
            size_t pos = 0;
            vector<float> input;
            string token;
            while ((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0, pos);
                input.push_back(atof(token.c_str()));
                line.erase(0, pos + delimiter.length());
            }
            input.push_back(atof(line.c_str()));
            data.push_back(input);
        }
    }
    return;
}

void Network::printData(){
    for (int i =0 ; i < data.size() ; i++){
        for (int j = 0 ; j < data[i].size(); j++){
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
}


vector<vector<float> > Network::getData(){
    return data;
}

void Network::loadInput(int index){
    for (int i = 0 ; i < graph[0].size(); i++){
        graph[0][i] = data[index][i];
    }
    return;
}


float Network::sigmoid(float value){
    return (1/(1+exp(-value)));
}

void Network::forwardPropagation(){
    for (int i = 1 ; i < graph.size(); i++){
        for (int j = 0; j < graph[i].size() ; j++){
            Neuron * node = graph[i][j];
            vector<Edge *> edges = node->getInEdgeList();
            float sum = 0.0;
            for (int k = 0 ; k < edges.size() ; k++){
                sum += (edges[k]->getIn)->getVal()*(edges[k]->getWeight());
            }
            node->setVal(sigmoid(sum, false));
        }
    }
    return;
}

float Network::lossFunction(int index){
    int N = graph.size();
    int out_neurons = graph[N-1].size();
    int input_size = data[index].size();
    //only used for logs; error will be used for backpropagation
    float l2_loss = 0.0; 
    for (int i = 0 ; i < out_neurons; i++){
        Neuron * node = graph[N-1][i];
        float label = data[index][input_size + i-out_neurons];
        float output = node->getVal();
        
        float node_error = (label-output)*output*(1-output);
        node->setError(node_error);
        
        l2_loss += sqr(label-output)/2;
    }
    
    return l2_loss;
}

void Network::backwardPropagatio(float learning_rate){
    //updating weights of last layer;
    // delta_w = error * output of incoming layer;
    int N = graph.size();
    int out_neurons = graph[N-1].size();
    
    
    
    //We perform the actual updates in the neural network after we have the new weights leading into the hidden layer neurons (ie, we use the original weights, not the updated weights, when we continue the backpropagation algorithm below).
    //sum will be used to calculate the error for hidden layers;
    float sum = 0.0;
    for (int i = 0 ; i < out_neurons ; i++){
        Neuron * node = graph[N-1][i];
        vector<Edge *> edges = node->getInEdgeList();
        for (int j = 0 ; j < edges.size() ; j++){
            float delta_weight = (node->getError())*((edges[j]->getIn())->getVal());
            //setting the delta but not changing the weight right now as it is needed for other layers;
            edges[j]->setDelta(delta_weight); // this delta can be used if we want to add momentum as well;
            sum += (edges[j]->getWeight())*(node->getError()); //here we wanted to use the original weight;
            float new_weight = edges[j]->getWeight() + learning_rate*(delta_weight);
            edges[j]->setWeight(new_weight);
        }
    }

    //updating weights of hidden layers
    for (int i = N-2 ; i > 0 ; i--){
        float lsum = 0.0;
        for (int j = 0; j < graph[i].size() ; j++){
            Neuron * node = graph[i][j];
            float node_error = sum*(node->getVal())*(1-(node->getVal()));
            node->setError(node_error);
            vector<Edge *> edges = node->getInEdgeList();
            for (int k = 0; k < edges.size(); k++){
                float delta_weight = (node->getError())*((edges[k]->getIn())->getVal());
                edges[k]->setDelta(delta_weight);
                lsum += (edges[k]->getWeight())*(node_error);
                float new_weight = edges[k]->getWeight() + learning_rate*(delta_weight);
                edges[k]->setWeight(new_weight);
            }
        }
        // Set sum to lsum, to be used for calculation layer error of further layers;
        sum = lsum;
    }

    return;
}

void Network::train(int epochs, float learning_rate){
    int data_size = data.size();
    for (int i = 0 ; i < epochs ; i++){
        cout<<"Epoch : "<<i<<endl;
        for (int j = 0 ; j < data_size; j++){
            loadInput(j);
            forwardPropagation();
            float loss = lossFunction(j);
            backwardPropagation(learning_rate);
            cout<<j<<"\t"<<loss<<endl;
        }
        cout<<endl;
    }
}

void Network::printNetwork(){
    for (int i = 0 ; i < graph.size(); i++){
        cout<<"Layer :"<<i<<endl;
        for (int j = 0 ; j < graph[i].size(); j++){
            cout<<"Neuron :"<<j<<endl<<endl;;    
            cout<<"Value :"<<graph[i][j]->getVal()<<endl<<endl;
            vector<Edge *> oList = graph[i][j]->getOutEdgeList();
            for (int k = 0 ; k < oList.size() ; k++){
                cout<<"Edge :"<<oList[k]->getWeight()<<endl;
            }
            cout<<endl;
        }
    }
    return;
}

