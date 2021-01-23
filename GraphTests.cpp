#include "Graph.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void TestAddNode(){
	cout << "Testing AddNode..." << endl;
	Graph g = Graph();
	// cout<< g.GraphNodeToString(g.AddNode('a', 15)) << endl;
	assert(g.GraphNodeToString(g.AddNode('a', 15)) == "(a:15)");

	// cout << g.GraphNodeToString(g.GetNodes().at(0));
	// cout << "<-- THE POINTER I JUST ADDED SHOULD BE PRINTED HERE" << endl;
	
	// cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << g.ToString() << endl;

	assert(g.NodesToString() == "[(a:15)]");
	assert(g.ToString() == "a | \n");
	
	g.AddNode('b', 12);
	// cout << "nodes: "  << g.NodesToString() << endl;
	// cout << "graph: " << endl << g.ToString() << endl;

	assert(g.NodesToString() == "[(a:15), (b:12)]");
	assert(g.ToString() == "a | \nb | \n");

	g.AddNode('c', 51);
	// cout << "nodes: "  << g.NodesToString() << endl;
	// cout << "graph: " << endl << g.ToString() << endl;

	assert(g.NodesToString() == "[(a:15), (b:12), (c:51)]");
	assert(g.ToString() == "a | \nb | \nc | \n");

	g.AddNode('x', 15656);
	// cout << "nodes: "  << g.NodesToString() << endl;
	// cout << "graph: " << endl << g.ToString() << endl;

	assert(g.NodesToString() == "[(a:15), (b:12), (c:51), (x:15656)]");
	assert(g.ToString() == "a | \nb | \nc | \nx | \n");

	// edge case, user tries to add node with key that already exists! 
	try{
		g.AddNode('a',125124);
		assert(false);
	}
	catch(const invalid_argument& e){
	}
	cout << "PASSED!" << endl << endl;
}
void TestAddEdge(){
	cout << "Testing AddEdge..." << endl;
	Graph g = Graph();
	GraphNode *gn1 = g.AddNode('a', 15);
	
	// cout << "nodes: "  << g.NodesToString() << endl;
	// cout << "graph: " << g.ToString() << endl;
	
	assert(g.NodesToString() == "[(a:15)]");
	assert(g.ToString() == "a | \n");

	GraphNode *gn2 = g.AddNode('b', 12);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;

	assert(g.NodesToString() == "[(a:15), (b:12)]");
	assert(g.ToString() == "a | \nb | \n");
	
	GraphNode *gn3 = g.AddNode('c', 9);
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | \nb | \nc | \n");
	
	g.AddEdge(gn1, gn3, 2);
	// cout << "nodes: "  << g.NodesToString() << endl;
	// cout << "graph: " << endl << g.ToString() << endl;
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | [(a:15)->(c:9) w:2]\nb | \nc | \n");
	
	g.AddEdge(gn3, gn2);
	g.AddEdge(gn1, gn2, 8);
	//cout << "nodes: "  << g.NodesToString() << endl;
	//cout << "graph: " << endl << g.ToString() << endl;
	
	assert(g.NodesToString() == "[(a:15), (b:12), (c:9)]");
	assert(g.ToString() == "a | [(a:15)->(c:9) w:2], [(a:15)->(b:12) w:8]\nb | \nc | [(c:9)->(b:12) w:0]\n");
	

	//Edge case, user tries to create an edge between two nodes, one or both of them have not been added to graph yet!
	GraphNode* a = new GraphNode();
	a->key = 'q';
	a->data = 214124;

	try{
		g.AddEdge(a,gn3,123);
		assert(false);
	}
	catch(const invalid_argument& e){
	}
	delete a;

	// Test, if the edge already exists, throw error
	try{
		g.AddEdge(gn3,gn2);
		assert(false);
	}
	catch(const invalid_argument& e){
	}

	cout << "PASSED!" << endl << endl;
}

void TestNodesToString(){
	cout << "Testing NodesToString..." << endl;
	Graph g = Graph();
	// zero node graph test
	assert(g.NodesToString() == "[]");
	
	// one node graph test
	g.AddNode('a', 15);
	assert(g.NodesToString() == "[(a:15)]");

	// double node graph test
	g.AddNode('1',20);
	assert(g.NodesToString() == "[(a:15), (1:20)]");

	// stress test
	g.AddNode('x',200);
	g.AddNode('o',1);
	g.AddNode('R',12);
	g.AddNode('r',13);
	g.AddNode('z',14);
	g.AddNode('W',15);
	g.AddNode('m',16);
	assert(g.NodesToString() == "[(a:15), (1:20), (x:200), (o:1), (R:12), (r:13), (z:14), (W:15), (m:16)]");
	cout << "PASSED!" << endl <<endl;
}
void TestToString(){
	cout << "Testing ToString..." << endl;
	Graph g = Graph();
	// empty graph, ToString should retun absolutely nothing
	assert(g.ToString() == "");
	
	// single node, no edges
	GraphNode* g0 = g.AddNode('a', 15);
	assert(g.ToString() == "a | \n");
	
	// multiple nodes, no edges
	GraphNode* g1 = g.AddNode('1',20);
	g.AddNode('x',200);
	g.AddNode('o',1);
	g.AddNode('R',12);
	g.AddNode('r',13);
	g.AddNode('z',14);
	GraphNode* g7 =	g.AddNode('W',15);
	GraphNode* g8 =	g.AddNode('m',16);

	assert(g.ToString() == "a | \n1 | \nx | \no | \nR | \nr | \nz | \nW | \nm | \n");

	// multiple nodes, one edge
	g.AddEdge(g0,g1,125);
	assert(g.ToString() == "a | [(a:15)->(1:20) w:125]\n1 | \nx | \no | \nR | \nr | \nz | \nW | \nm | \n");

	// multiple nodes, multiple edges
	g.AddEdge(g8,g1,12);
	assert(g.ToString() == "a | [(a:15)->(1:20) w:125]\n1 | \nx | \no | \nR | \nr | \nz | \nW | \nm | [(m:16)->(1:20) w:12]\n");

	g.AddEdge(g0,g7,123);
	assert(g.ToString() == "a | [(a:15)->(1:20) w:125], [(a:15)->(W:15) w:123]\n1 | \nx | \no | \nR | \nr | \nz | \nW | \nm | [(m:16)->(1:20) w:12]\n");
	cout << "PASSED!" << endl <<endl;

}


void TestGetEdges(){
	cout << "Testing GetEdges..." << endl;
	Graph g = Graph();

	GraphNode* g1 = g.AddNode('1',20);
	GraphNode* g2 =	g.AddNode('W',15);
	GraphNode* g3 =	g.AddNode('m',16);

	g.AddEdge(g1,g2,4);
	g.AddEdge(g1,g3,5);

	// if this works, then we can convert each edge to a string 
	assert(g.GraphEdgeToString(g.GetEdges(g1).at(0)) == "[(1:20)->(W:15) w:4]");
	assert(g.GraphEdgeToString(g.GetEdges(g1).at(1)) == "[(1:20)->(m:16) w:5]");


	cout << "PASSED!" << endl <<endl;
}
void TestGetNodes(){
	cout << "Testing GetNodes..." << endl;
	Graph g = Graph();

	g.AddNode('1',20);
	g.AddNode('W',15);
	g.AddNode('m',16);

	assert(g.GraphNodeToString(g.GetNodes().at(0)) == "(1:20)");
	assert(g.GraphNodeToString(g.GetNodes().at(1)) == "(W:15)");
	assert(g.GraphNodeToString(g.GetNodes().at(2)) == "(m:16)");

	cout << "PASSED!" << endl <<endl;
}
void TestGraphNodeAt(){
	cout << "Testing GetNodeAt..." << endl;
	
	Graph g = Graph();
	g.AddNode('1',20);
	g.AddNode('W',15);
	g.AddNode('m',16);
	g.AddNode('x',200);
	g.AddNode('o',1);
	g.AddNode('R',12);
	g.AddNode('r',13);
	g.AddNode('z',14);

	assert(g.GraphNodeToString(g.NodeAt(6)) == "(r:13)");
	assert(g.GraphNodeToString(g.NodeAt(0)) == "(1:20)");

	//testing: if user tries to find a node that does not exist
	try{
		g.NodeAt(8);
		assert(false);
	}
	catch(const invalid_argument& e){
	}




	cout << "PASSED!" << endl <<endl;
}

void TestSize(){
	cout << "Testing Size..." << endl;

	Graph g = Graph();
	GraphNode* g1 = g.AddNode('1',20);
	GraphNode* g2 =	g.AddNode('x',15);
	GraphNode* g3 =	g.AddNode('s',16);
	GraphNode* g4 = g.AddNode('r',20);
	GraphNode* g5 =	g.AddNode('W',15);
	GraphNode* g6 =	g.AddNode('m',16);


	assert(g.Size() == 0);
	g.AddEdge(g1,g2,4);
	g.AddEdge(g1,g3,5);
	g.AddEdge(g1,g4,4);
	g.AddEdge(g1,g5,5);
	g.AddEdge(g1,g6,4);
	assert(g.Size() ==5);
	g.AddEdge(g2,g3,5);
	g.AddEdge(g4,g2,4);
	g.AddEdge(g4,g3,5);
	g.AddEdge(g3,g1,4);
	g.AddEdge(g3,g2,5);
	g.AddEdge(g5,g2,4);
	g.AddEdge(g6,g3,5);
	assert(g.Size() == 12);

	cout << "PASSED!" << endl <<endl;
}
void TestOrder(){
	cout << "Testing Order..." << endl;
	Graph g = Graph();
	assert(g.Order()== 0);


	g.AddNode('1',20);
	g.AddNode('W',15);
	g.AddNode('m',16);
	g.AddNode('x',200);
	g.AddNode('o',1);
	g.AddNode('R',12);
	g.AddNode('r',13);
	g.AddNode('z',14);

	assert(g.Order() == 8);

	g.AddNode('q',1231241425);
	assert(g.Order() == 9);


	cout << "PASSED!" << endl <<endl;
}
void TestDestructor(){
	cout << "Testing Destructor..." << endl;
	Graph *g = new Graph();
	
	GraphNode *a = g->AddNode('a', 3);
	GraphNode *b = g->AddNode('b', 5);
	g->AddEdge(b, a, 15);
	
	delete g;

	
	Graph g2 = Graph();
	GraphNode *c = g2.AddNode('c', 12);
	g2.AddNode('d', 11);
	assert(c->key == 'c' && c->data == 12);
	
	
	
	cout << "NO ERRORS.  Use valgrind to check!" << endl << endl;
}

int main(){
	TestAddNode();
	TestAddEdge();
	TestNodesToString();
	TestToString();
	TestGetEdges();
	TestGetNodes();
	TestGraphNodeAt();
	TestSize();
	TestOrder();
	TestDestructor();

	cout << "ALL TESTS PASSED!" << endl;
	return 0;
}