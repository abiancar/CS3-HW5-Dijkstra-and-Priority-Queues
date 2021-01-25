#include "Graph.h"
#include<iostream>
#include <string>

using namespace std;
	
    Graph::~Graph(){
        for(size_t i =0; i < this->Order(); i++){
            GraphNode* currNode = nodes.at(i);
            delete currNode;

            for(size_t j = 0; j < this->adjacencyList[i].size(); j++){
                GraphEdge* currEdge = this->adjacencyList[i][j];
                delete currEdge;
            }     
        }
    }
    //when adding a node, check if there are any duplicates!
    //We don't need to check if weights are negative
    GraphNode* Graph::AddNode(char key, int data){
        
        GraphNode *node = new GraphNode; // structs do not need parentheses! // you can never return a pointer on the stack
        node->key = key;
        node->data = data;

        // if we cannot find the node already, we can add it
        if(this->findNode(node) == -1){
            this->nodes.push_back(node);
            this->adjacencyList.resize(this->adjacencyList.size()+ 1); // expands adjacencyList so that we can later insert edges into it without error in Graph::addEdge()
            return node;

        }
        // if the node already exists, throw error

        else{
            delete node;
            throw invalid_argument("You cannot add an existing node to the graph!");
        }
    }
	GraphEdge* Graph::AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight){
        if(this->findNode(gn1) == -1){
            throw invalid_argument("The origin node has not yet been added to the graph!");
        }
        if(this->findNode(gn2) == -1){
            throw invalid_argument("The destination node has not yet been added to the graph!");
        }

        GraphEdge *edge = new GraphEdge;
        edge->from = gn1;
        edge->to = gn2;
        edge->weight = weight;

        // check to see if the edge already exists, if so, throw another error!
        for(size_t i = 0; i < GetEdges(gn1).size();i++){
            if(GetEdges(gn1).at(i)->to == edge->to){
                delete edge;
                throw invalid_argument("The edge you are trying to create already exists!");
            }
        }
        
        int index = findNode(gn1);
        
        // let's access the appropriate slot in adjacencyList (1st dimension), and add the edge to its list (2nd dimension)
        this->adjacencyList[index].push_back(edge);
        return edge;
    }
	
    string Graph::NodesToString() const{
        std::string nodeString = "[";
        for(size_t i = 0; i < this-> nodes.size(); i++){
            // cout << this->GraphNodeToString(this->nodes.at(i)) << "CURRENT NODE " << endl;
            nodeString = nodeString + this->GraphNodeToString(nodes.at(i));
            if(i != nodes.size()-1){nodeString += ", ";}
        }
        nodeString += "]";   
        return nodeString;
    }
	string Graph::ToString() const{
        std::string graphString;
        for (unsigned int i = 0; i < this->Order(); i++){
            GraphNode* curr = this->nodes.at(i);
            graphString = graphString + curr->key + " | ";
            
            //if no edges were created for this node, just print \n
            if(this->adjacencyList[i].size()==0 ){
                graphString += "\n";
            }
            else{
                for(size_t row = 0; row < this->adjacencyList[i].size(); row++){
                    graphString += GraphEdgeToString(adjacencyList[i][row]);
                    if(row != adjacencyList[i].size()-1){
                        graphString += ", ";
                    }
                }
                graphString+= "\n";
            }
        }
        // cout << graphString << endl;

        return graphString;
    }
	
    string Graph::GraphNodeToString(const GraphNode *gn){ //converts a graphNode to a string
        GraphNode g = *gn;
        std::string gnString = "(";
        gnString = gnString + g.key + ":" + to_string(g.data) + ")";    
        
        return gnString;
    }
	string Graph::GraphEdgeToString(const GraphEdge *ge){        
        //receive an edge, convert it to string
        // getNode from -> getNode to
        std::string edgeString = "[";
       
        GraphNode* to = ge->to;
        GraphNode* from = ge->from;
        std::string destinationString = GraphNodeToString(to);
        std::string fromString = GraphNodeToString(from);

        // cout << "from: " << fromString << endl << endl << endl;
        // cout << "to: " << destinationString << endl;

        edgeString = edgeString + fromString + "->" + destinationString + " w:" + to_string(ge->weight) + "]";
        // cout << edgeString << endl;

        return edgeString;
    }
	
    const vector<GraphEdge*>& Graph::GetEdges(const GraphNode *gn) const{ // this function needs to return a reference to a vector of GraphEdge pointers
        vector<GraphNode*> nodesList = this->GetNodes();
        int index;
            for(size_t i = 0; i < nodesList.size(); i++){
                if(nodesList.at(i)== gn){
                    index = i;
                }
            }
            return this->adjacencyList[index];

    }
	const vector<GraphNode*>& Graph::GetNodes() const{
        return this->nodes;
    }
	const GraphNode* Graph::NodeAt(unsigned int idx) const{
        if(idx >= this->GetNodes().size()){
            throw invalid_argument("You are trying to access a node that doesn't exist in the graph yet!");
        }
        return this->GetNodes().at(idx);
    }
	
    size_t Graph::Size() const {
        unsigned int sum = 0;
        for(size_t i = 0; i<this->Order(); i++){
            sum += adjacencyList[i].size();
        }
        return sum; // the number of edges
    } 
	size_t Graph::Order() const {
        return this->GetNodes().size();  // the number of nodes
    }

    // to place new edges in the appropriate slot in the adjacencyList, we will search for its corresponding slot in the nodes vector
    const int Graph::findNode(const GraphNode* target){
        vector<GraphNode*> nodesList = this->GetNodes();
        for(size_t i = 0; i < nodesList.size(); i++){
            if(nodesList.at(i)->key == target->key){
                return i;
            }
        }
        return -1;

    }
