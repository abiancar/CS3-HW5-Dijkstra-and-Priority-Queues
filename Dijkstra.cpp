#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

// General algorithm:
// We're gonna take a graph filled with edges and nodes
// We are going to build a priority queue starting on the first value (start)
// This PQ will hold all neighboring nodes of the start
// We will update the priority of each node based on the edge between the start and the node
// Then we will use a boolean to set the start node as checked


int findDNode(vector<DNode> vector, DNode target){
	for(size_t i = 0; i < vector.size(); i++){
		if(vector[i] == target){
			return i;
		}
	}
	return -1;
}

int dijkstra(const GraphNode *start, const GraphNode *end, Graph *g){\

	//create priority queue
	BetterPriorityQueue q;

	//add the start node to the queue
	DNode starter;
	starter.pri = 0;
	starter.node = start;
	q.push(starter);

	DNode endDNode;
	endDNode.node = end;

	DNode last;
	last.pri = 0;
	
	//for storing DNodes that have already been visited
	vector<DNode> visitedDNodes;

	while(q.empty()!= true){
		// we now need to get its edges
		DNode originDNode = q.top();
		vector<GraphEdge*> edges = g->GetEdges(originDNode.node);
		cout <<  "Curr originDNOde " << q.DnodeToString(originDNode) << endl;


		//we will calculate the distance from this point to each edge
		//if it is smaller than the current priority of an edge, we will either add or update that edge
		for(size_t i = 0; i < edges.size(); i++){
			
			GraphNode* destinationGNode = edges.at(i)->to;
			int potentialCost = edges.at(i)->weight + originDNode.pri;
			cout << "Potential cost: " << potentialCost << endl;
			
			//Creating new DNode in case if we should add or update any information
			DNode destinationDNode;
			destinationDNode.node = destinationGNode;

			// if we have never seen this node before, add it to PQ and set its edge as the wight
			if(q.Contains(destinationDNode) == false && findDNode(visitedDNodes, destinationDNode) == -1){
				destinationDNode.pri = potentialCost;
				q.push(destinationDNode);
			}
			// the node is not currently on our priority queue but we have visited it before
			else if(q.Contains(destinationDNode) == false && findDNode(visitedDNodes, destinationDNode) != -1){ 
				int index = findDNode(visitedDNodes, destinationDNode);
				// if we find that 'going backwards' can find us a better solution to an 
				// already completed node, we will 
				if(visitedDNodes[index].pri > potentialCost){
					visitedDNodes[index].pri = potentialCost;
				}

			}
			// the node is currently in the Priority Queue and may need to be updated
			else{
				int index = findDNode(q.getPQList(), destinationDNode);
				DNode PQDNode = q.getPQList()[index];
				if (PQDNode.pri > potentialCost){
					destinationDNode.pri = potentialCost;
					cout << "UPDATING! " << endl;
					q.Update(destinationDNode);
				}
			}
			for(size_t j = 0; j < visitedDNodes.size(); j++){
			cout <<  "Visited Node: " << q.DnodeToString(visitedDNodes[j]) << endl;

			}
		}
		
		
		originDNode.visited = true;
		visitedDNodes.push_back(originDNode);
		q.pop();
		cout << q.ToString() << endl;
	}

	int finder = findDNode(visitedDNodes, endDNode);
	
	cout << "RESULT: " << visitedDNodes[finder].pri << endl;
	return visitedDNodes[finder].pri;
}


int DijkstraTest(){
	// Note, when grading I will replace this with
	// other / more tests.  I recommend you do the same!
	
	Graph *g = new Graph();
	
	GraphNode *a = g->AddNode('1');
	GraphNode *b = g->AddNode('2');
	GraphNode *c = g->AddNode('3');
	GraphNode *d = g->AddNode('4');
	GraphNode *e = g->AddNode('5');
	GraphNode *f = g->AddNode('6');
	
	g->AddEdge(a, b, 7);
	g->AddEdge(b, a, 7);
	g->AddEdge(a, c, 9);
	g->AddEdge(c, a, 9);
	g->AddEdge(a, f, 14);
	g->AddEdge(f, a, 14);
	
	g->AddEdge(b, c, 10);
	g->AddEdge(c, b, 10);
	g->AddEdge(b, d, 15);
	g->AddEdge(d, b, 15);
	
	g->AddEdge(c, f, 2);
	g->AddEdge(f, c, 2);
	g->AddEdge(c, d, 11);
	g->AddEdge(d, c, 11);
	
	g->AddEdge(f, e, 9);
	g->AddEdge(e, f, 9);
	
	g->AddEdge(d, e, 6);
	g->AddEdge(e, d, 6);
	
	
	cout << g->ToString() << endl;
	
	unsigned int ans = dijkstra(g->NodeAt(0), e, g);
	assert(ans == 20);
	cout << "PASSED ALL TESTS " << endl;

	delete g;
		
	return ans;
}


int main(){
	
	int ans = DijkstraTest();
	cout << "ans: "  << ans << endl;
	
	return 0;
}
