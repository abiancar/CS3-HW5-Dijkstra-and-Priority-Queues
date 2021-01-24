#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <cassert>
#include <iostream>

using namespace std;



void ContainsTest() {
	cout << "Testing Contains Helper Method..." << endl;
	
	Graph g = Graph();
	BetterPriorityQueue q;
	
	GraphNode *a = g.AddNode('a');
	GraphNode *b = g.AddNode('b');
	GraphNode *c = g.AddNode('c');
	
	DNode n;
	DNode bravo;
	DNode charlie;
	
	n.node = a;
	bravo.node = b;
	charlie.node = c;
	
	q.push(n);
	q.push(bravo);
	
	// cout << q.DnodeToString(n);
	cout << q.ToString() << endl;

	assert(q.Contains(n) == true);
	assert(q.Contains(bravo) == true);
	
	//testing, node that has not yet been pushed onto PQ
	assert(q.Contains(charlie) == false);

	q.push(charlie);
	assert(q.Contains(charlie) == true);

	// more tests go here!
	
	
	cout << "PASSED!" << endl;
}



void UpdateTest() {
	cout << "Testing Update Helper Method..." << endl;
	
	Graph g = Graph();
	BetterPriorityQueue q;
	
	g.AddNode('a');
	g.AddNode('b');
	g.AddNode('c');
	g.AddNode('d');

	GraphNode *e = g.AddNode('e');
	GraphNode *f = g.AddNode('f');

	vector<GraphNode*> nodes = g.GetNodes();

	for(size_t i = 0; i < nodes.size(); i++){
		DNode cur;
		cur.pri = i;
		cur.node = nodes.at(i);
		cout << "inserting cur.pri: " << cur.pri << "  node: " << cur.node->key << endl;
		q.push(cur);
		cout << "size: " << q.size() << endl;
	}
	

	//cout << "q before: " << queue_to_string(q) << endl;

	DNode positive;
	positive.node = f;
	positive.pri = 0;
	cout << "q before: " << q.ToString() << endl;
	assert(q.Update(positive) == true);
	cout << "q after: " << q.ToString() << endl;


	// Either one of these solutions is correct depending on
	// how you implement the priority queue
	string soln1 = "[(a: 0), (b: 1), (f: 0), (d: 3), (e: 4), (c: 2)]";
	string soln2 = "[(f: 0), (b: 1), (a: 0), (d: 3), (e: 4), (c: 2)]";
	assert(q.ToString() == soln1 || q.ToString() == soln2);
	
	
	
	Graph g1 = Graph();
	BetterPriorityQueue q1;

	GraphNode* a = g1.AddNode('a');
	GraphNode* b = g1.AddNode('b');
	GraphNode* c = g1.AddNode('c');
	GraphNode* d = g1.AddNode('d');
	GraphNode* z = g1.AddNode('z');
	GraphNode* o = g1.AddNode('o');
	GraphNode* r = g1.AddNode('r');

	DNode alpha;
	alpha.node = a;
	alpha.pri = 5;
	
	DNode bravo;
	bravo.node = b;
	bravo.pri = 4;
	
	DNode charlie;
	charlie.node = c;
	charlie.pri = 20;
	
	DNode delta;
	delta.node = d;
	delta.pri = 30;
	
	DNode zulu;
	zulu.node = z;
	zulu.pri = 10;
	
	DNode oscar;
	oscar.node = o;
	oscar.pri = 0;	
	
	DNode romeo;
	romeo.node = r;
	romeo.pri = 15;
	
	DNode replacer;
	replacer.node = d;
	replacer.pri = 6;

	q1.push(alpha);
	q1.push(bravo);
	q1.push(charlie);
	q1.push(delta);
	q1.push(zulu);
	q1.push(oscar);
	q1.push(romeo);
	
	cout << "q1 before: " << q1.ToString() << endl;
	assert(q1.Update(replacer) == true);
	cout << "q1 after: " << q1.ToString() << endl;


	// more tests go here...
	
	
	cout << "PASSED!" << endl;
}


int main(){
	
	ContainsTest();
	UpdateTest();
	
	cout << "ALL TESTS PASSED!!" << endl;
	
	return 0;
	
}
