#include "Graph.h"
#include<iostream>
#include <string>

using namespace std;
	
    Graph::~Graph(){
        // for(size_t i =this->Order()-1; i >=0; i--){
        //     cout << i;
        //     delete this->nodes.at(i); 

        //     for(size_t j = this->adjacencyList[i].size()-1; j >= 0; j--){
        //         cout << i;
        //         cout << j;
        //         delete this->adjacencyList[i][j];
        //     }     
        // }
        delete this;
    }
    //when adding a node, check if there are any duplicates!
    //We don't need to check if weights are negative
    GraphNode* Graph::AddNode(char key, int data){
        GraphNode *node = new GraphNode; // structs do not need parentheses! // you can never return a pointer on the stack
        node->key = key;
        node->data = data;
        this->nodes.push_back(node);
        this->adjacencyList.resize(this->adjacencyList.size()+ 1); // expands adjacencyList so that we can later insert edges into it without error in Graph::addEdge()
        
        // cout << "ADDING THE FOLLOWING POINTER TO NODES" << endl;
        // cout << this->GraphNodeToString(node) << endl;
        // cout << "POINTER ADDED" << endl;
        // cout << this->GraphNodeToString(nodes.at(0)) << endl;

        return node;
    }


	GraphEdge* Graph::AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight){
        GraphEdge *edge = new GraphEdge;
        edge->from = gn1;
        edge->to = gn2;
        edge->weight = weight;

        int index = findNode(gn1);
        
        // let's access the appropriate slot in adjacencyList (1st dimension), and add the edge there
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
            
            // cout << "graphString: " << graphString << endl;

            //if no edges were created for this node, just print \n
            // cout << this->adjacencyList[i].size() << " ADJ SIZE" << endl;
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
        cout << graphString << endl;

        return graphString;
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
        //receive an edge, convert it to string
        // getNode from -> getNode to
        std::string edgeString = "[";
       
        GraphNode* to = ge->to;
        GraphNode* from = ge->from;
        
        std::string destinationString = GraphNodeToString(to);
        std::string fromString = GraphNodeToString(from);


        cout << "from: " << fromString << endl << endl << endl;
        cout << "to: " << destinationString << endl;


        edgeString = edgeString + fromString + "->" + destinationString + " w:" + to_string(ge->weight) + "]";

        cout << edgeString << endl;

        return edgeString;
	// assert(g.ToString() == "a | [(a:15)->(c:9) w:2]\nb | \nc | \n");

    
    }


    	
	const vector<GraphEdge*>& Graph::GetEdges(const GraphNode *gn) const{ // this function needs to return a reference to a vector of GraphEdge pointers
    //    int i = this->findNode(gn); // locate the node


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


    // to place new edges in the appropriate slot in the adjacencyList, we will search for its corresponding slot in the nodes vector
    const int Graph::findNode(const GraphNode* target){
        for(size_t i = 0; i < this->Order(); i++){
            if(nodes.at(i)==target){
                return i;
            }
        }
        return -1;

    }


   