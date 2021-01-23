#include <queue>
#include "DNode_struct.h"
using namespace std;

class BetterPriorityQueue: public priority_queue<DNode, vector<DNode>,
greater<DNode>>::priority_queue {



};