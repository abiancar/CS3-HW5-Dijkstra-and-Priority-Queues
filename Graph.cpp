#include "Graph.h"
#include<iostream>
#include <string>

using namespace std;
	
    Graph::~Graph(){
        delete this; 
    }
    //when adding a node, check if there are any duplicates!
    //We don't need to check if weights are negative
    GraphNode* Graph::AddNode(char key, int data){
        GraphNode *node = new GraphNode; // structs do not need parentheses! // you can never return a pointer on the stack
        node->key = key;
        node->data = data;
        this->nodes.push_back(node);
        // this->adjacencyList.push_back(a)

        cout << "ADDING THE FOLLOWING POINTER TO NODES" << endl;
        cout << this->GraphNodeToString(node) << endl;
        cout << "POINTER ADDED" << endl;
        cout << this->GraphNodeToString(nodes.at(0)) << endl;

        return node;
    }


	GraphEdge* Graph::AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight){
        GraphEdge *edge = new GraphEdge;
        edge->from = gn1;
        edge->to = gn2;
        edge->weight = weight;

        return edge;
    }
		
	string Graph::NodesToString() const{
        std::string nodeString = "[";


        for(size_t i = 0; i < this-> nodes.size(); i++){
            // cout << this->GraphNodeToString(this->nodes.at(i)) << "CURRENT NODE " << endl;
            nodeString = nodeString + this->GraphNodeToString(nodes.at(i));
            if(i != nodes.size()-1){nodeString += ',';}

        }
        nodeString += "]";   
        return nodeString;
    }
	string Graph::ToString() const{
        return "string";
    }

	string Graph::GraphNodeToString(const GraphNode *gn){ //converts a graphNode to a string
        // we are gonna receive a GraphNode pointer
        // get the key and data it refers to
        // put em in a string
        //that's it folks
        GraphNode g = *gn;
        std::string gnString = "(";
        gnString = gnString + g.key + ":" + to_string(g.data) + ")";
        // cout << gnString << endl;

	    //assert(g.NodesToString() == "[(a:15), (b:12)]");
	    //assert(g.ToString() == "a | \nb | \n");        
        
        return gnString;
    }
	std::string Graph::GraphEdgeToString(const GraphEdge *ge){
        return "placeholder";
    }


    	
	const vector<GraphEdge*>& Graph::GetEdges(const GraphNode *gn) const{
    }

	const vector<GraphNode*>& Graph::GetNodes() const{
        return this->nodes;
    }
	const GraphNode* Graph::NodeAt(unsigned int idx) const{
        return this->GetNodes().at(idx);
    }
	size_t Graph::Size() const {
        return 0;

    } // the number of edges
	size_t Graph::Order() const {
        return this->GetNodes().size();

    } // the number of nodes

    int Graph::findKey(GraphNode* target){
        for(size_t i = 0; i < this->Order(); i++){
            if(nodes.at(i)==target){
                return i;
            }
        }
        return -1;

    }


   