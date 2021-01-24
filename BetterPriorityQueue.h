#include <queue>
#include "DNode_struct.h"

using namespace std;

class BetterPriorityQueue: public priority_queue<DNode, vector<DNode>,
greater<DNode>>::priority_queue {
public:
    bool Contains(DNode dijkstrian);
    bool Update(DNode dijkstrian);
    string ToString();
    static string DnodeToString(DNode);
    vector<DNode> getPQList();
};