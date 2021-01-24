#include <iostream>
#include "BetterPriorityQueue.h"

using namespace std;

    vector<DNode> BetterPriorityQueue::getPQList(){
        return this->c;
    }
    bool BetterPriorityQueue::Contains(DNode dijkstrian){
        for(size_t i = 0 ; i < this->c.size(); i++){
            if(this->c.at(i) == dijkstrian){
                return true;
            }
        }
        return false;
    }
    bool BetterPriorityQueue::Update(DNode dijkstrian){
        //if the Priority Queue contains the desired node, then we can update the PQ
        if(this->Contains(dijkstrian) == true){
            
            //temporay storage of all Nodes
            vector<DNode> tmpVector;
            
            while(this->empty() == false){
                DNode curr = this->top();
                this->pop();

                if(curr == dijkstrian){
                    curr.pri = dijkstrian.pri;
                }
                tmpVector.push_back(curr);
            }
            for(size_t i = 0; i < tmpVector.size(); i++){
                this->push(tmpVector[i]);
            }
            return true;
        }

        // if we have nothing to update, we don't do anything and return false
        return false;

    }
    string BetterPriorityQueue::ToString(){
        std::string DNodeString = "[";
        for(size_t i = 0 ; i < this->c.size(); i++){
            DNodeString += DnodeToString(this->c[i]);
            if(i != this->c.size()-1){
                DNodeString += ", ";
            }
        }
        DNodeString += "]";
        return DNodeString;
    }
    string BetterPriorityQueue::DnodeToString(DNode dijkstrian){
        std::string DnString = "(";
        DnString = DnString + dijkstrian.node->key + ": " + to_string(dijkstrian.pri) + ")";
        return DnString;
    }