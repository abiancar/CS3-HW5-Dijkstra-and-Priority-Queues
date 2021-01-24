#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;
struct GraphNode {
	char key;
	int data; // Not necessary or used for Dijkstra algorithm
};


struct GraphEdge {
	GraphNode *from;
	GraphNode *to;	
	unsigned int weight;
};


class Graph{
	
	public:
		~Graph();
	
		GraphNode *AddNode(char key, int data = 0); // adds a node to graph with a key and value
		GraphEdge *AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight = 0); // creates an edge between two nodes
		
		string NodesToString() const;
		string ToString() const;

		static string GraphNodeToString(const GraphNode *gn);
		static string GraphEdgeToString(const GraphEdge *ge);
		
		const vector<GraphEdge*>& GetEdges(const GraphNode *gn) const;
		const vector<GraphNode*>& GetNodes() const;
		const GraphNode* NodeAt(unsigned int idx) const;

		size_t Size() const; // the number of edges
		size_t Order() const; // the number of nodes

	private:
		vector<vector<GraphEdge*>> adjacencyList; // list of lists ... in plain english: list containing the vectors of numbers that represent edges between nodes
	    vector<GraphNode*> nodes;
		const int findNode(const GraphNode* target); //finds the position of the wanted node pointer in nodes


};
#endif
