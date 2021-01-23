#include <limits.h>
#include "Graph.h"


// This is a "Dijkstra Node" it is used for the Dijkstra algorithm
// and it is used as the items in the BetterPriorityQueue
struct DNode {
	int pri = INT_MAX;
	bool visited = false;
	const GraphNode *node = nullptr;
	
	bool operator<(const DNode &other) const {
		return pri < other.pri;
	}

	bool operator>(const DNode &other) const {
		return pri > other.pri;
	}
	
	bool operator==(const DNode &other) const {
		return node == other.node;
	}
};