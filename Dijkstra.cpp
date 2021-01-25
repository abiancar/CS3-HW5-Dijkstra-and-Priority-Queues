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

// helper method, used to access nodes that have already been visited
int findDNode(vector<DNode> vector, DNode target){
	for(size_t i = 0; i < vector.size(); i++){
		if(vector[i] == target){
			return i;
		}
	}
	return -1;
}

int dijkstra(const GraphNode *start, const GraphNode *end, Graph *g){\
	BetterPriorityQueue q;	//create priority queue

	//add the start node to the queue
	DNode starter;
	starter.pri = 0;
	starter.node = start;
	q.push(starter);

	// create an end DNode copy to help us return the result at the end
	DNode endDNode;
	endDNode.node = end;

	vector<DNode> visitedDNodes; //for storing DNodes that have already been visited

	while(q.empty()!= true){
		// we now need to get its edges
		DNode originDNode = q.top();
		vector<GraphEdge*> edges = g->GetEdges(originDNode.node);
		cout << q.DnodeToString(originDNode) << endl;

		// each edgeNode will be used to create its respective DNode if it hasn't been done already
		for(size_t i = 0; i < edges.size(); i++){
			GraphNode* destinationGNode = edges.at(i)->to; 			   	 // the edge 'direction'
			int potentialCost = edges.at(i)->weight + originDNode.pri;	 // we calculate potential cost for future comparison
			
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
				// already completed node, we will change that node's value
				if(visitedDNodes[index].pri > potentialCost){
					visitedDNodes[index].pri = potentialCost;
				}
			}
			// the node is currently in the Priority Queue and may need to be updated
			else{
				int index = findDNode(q.getPQList(), destinationDNode);
				DNode PQDNode = q.getPQList()[index];
				
				// if there is a better alternative than the current possible moves, update
				if (PQDNode.pri > potentialCost){
					destinationDNode.pri = potentialCost;
					q.Update(destinationDNode);
				}
			}
		}
		// we have looked at all of this node's edges, mark it as visited and remove from PQ
		originDNode.visited = true;
		visitedDNodes.push_back(originDNode);
		q.pop();
	}
	// for finding endNode after emptying the BetterPriorityQueue
	int finder = findDNode(visitedDNodes, endDNode);
	
	cout << "ans: " << visitedDNodes[finder].pri << endl << endl;
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

	delete g;


	Graph *g1 = new Graph();
	
	GraphNode *a1 = g->AddNode('A');
	GraphNode *b1 = g->AddNode('B');
	GraphNode *c1 = g->AddNode('C');
	GraphNode *d1 = g->AddNode('D');
	GraphNode *e1 = g->AddNode('E');
	
	g1->AddEdge(a1, b1, 3);
	g1->AddEdge(a1, c1, 1);
	g1->AddEdge(b1, a1, 3);
	g1->AddEdge(b1, c1, 7);
	g1->AddEdge(b1, d1, 5);
	g1->AddEdge(b1, e1, 1);
	g1->AddEdge(c1, a1, 1);
	g1->AddEdge(c1, b1, 7);
	g1->AddEdge(c1, d1, 2);
	g1->AddEdge(d1, c1, 2);
	g1->AddEdge(d1, b1, 5);
	g1->AddEdge(d1, e1, 7);
	g1->AddEdge(e1, b1, 1);
	g1->AddEdge(e1, d1, 7);
	
	
	cout << g1->ToString() << endl;
	
	unsigned int ans1 = dijkstra(c1, b1, g1);
	assert(ans1 == 4);

	delete g1;
	// return ans1


	// one directional test	
	Graph *g2 = new Graph();
	
	GraphNode *a2 = g->AddNode('1');
	GraphNode *b2 = g->AddNode('2');
	GraphNode *c2 = g->AddNode('3');
	GraphNode *d2 = g->AddNode('4');
	GraphNode *e2 = g->AddNode('5');
	GraphNode *f2 = g->AddNode('6');

	g2->AddEdge(a2, b2, 7);
	g2->AddEdge(a2, c2, 9);
	g2->AddEdge(a2, f2, 14);
	g2->AddEdge(b2, c2, 10);
	g2->AddEdge(b2, d2, 15);
	g2->AddEdge(c2, f2, 2);
	g2->AddEdge(c2, d2, 11);
	g2->AddEdge(d2, e2, 6);
	g2->AddEdge(f2, e2, 9);
	
	
	cout << g2->ToString() << endl;
	
	unsigned int ans2 = dijkstra(a2, e2, g2);
	assert(ans2 == 20);

	delete g2;
		
	// return ans2;

	// one directional test	
	Graph *g3 = new Graph();
	
	GraphNode *z0 = g->AddNode('0');
	GraphNode *z1 = g->AddNode('1');
	GraphNode *z2 = g->AddNode('2');
	GraphNode *z3 = g->AddNode('3');
	GraphNode *z4 = g->AddNode('4');
	GraphNode *z5 = g->AddNode('5');
	GraphNode *z6 = g->AddNode('6');
	GraphNode *z7 = g->AddNode('7');
	GraphNode *z8 = g->AddNode('8');



	g3->AddEdge(z0,z1,4);
	g3->AddEdge(z0,z7,8);
	g3->AddEdge(z1,z7,11);
	g3->AddEdge(z1,z2,8);
	g3->AddEdge(z7,z8,7);
	g3->AddEdge(z7,z6,1);
	g3->AddEdge(z8,z2,2);
	g3->AddEdge(z8,z6,6);
	g3->AddEdge(z6,z5,2);
	g3->AddEdge(z5,z2,4);
	g3->AddEdge(z2,z3,7);
	g3->AddEdge(z3,z5,14);
	g3->AddEdge(z3,z4,9);
	g3->AddEdge(z5,z4,10);

	cout << g3->ToString() << endl;
	
	unsigned int ans3 = dijkstra(z0, z4, g3);
	assert(ans3 == 21);
	cout << "ALL TESTS PASSED! " << endl << endl;

	delete g3;
		
	return ans3;
}


int main(){
	
	int ans = DijkstraTest();
	cout << "ans: "  << ans << endl;
	
	return 0;
}
