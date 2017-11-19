//network.cpp

#include "network.h"
#include <time.h>
#include <iostream>
#include <fstream>

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
                float randVal = (float)( (rand()%100000)/100000.0) ;
                Edge * e = new Edge(randVal, graph[i][j], graph[i+1][k]);
                graph[i][j]->addOutEdge(e);
                graph[i+1][k]->addInEdge(e);
            }
        }
    }
    
    //Adding bias node and edges
    Neuron * bias_node = new Neuron(1.0);
    for (int i = 1 ; i < num_layers ; i++){
        for (int j = 0; j < num_neurons[i]; j++){
            float randVal = (float)( (rand()%100000)/100000.0) ;
            Edge * e = new Edge(randVal, bias_node, graph[i][j]);
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

void Network::printNetwork(){
    for (int i = 0 ; i < graph.size(); i++){
        cout<<"Layer :"<<i<<endl;
        for (int j = 0 ; j < graph[i].size(); j++){
            cout<<"Neuron :"<<j<<endl<<endl;;    
            cout<<"Value :"<<graph[i][j]->getVal()<<endl<<endl;
            vector<Edge *> oList = graph[i][j]->getOutEdgeList();
            for (int k = 0 ; k < oList.size() ; k++){
                cout<<"Edge :"<<oList[k]->getVal()<<endl;
            }
            cout<<endl;
        }
    }
    return;
}

