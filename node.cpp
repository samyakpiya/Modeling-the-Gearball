#ifndef NODE
#define NODE

#include <stack>
#include "gearball.cpp"
#include "astar.cpp"

class Node
{
public:
    int gCost = 0;
    int hCost;
    int fCost;
    Gearball currGearballState;

    // Might not need these lines of code as we are storing the current state of the Gearball
    // stack<int> movesPerformed;
    // stack.push(elm)
    // stack.pop()
    //
    // while (!stack.empty()) {
    //     cout << stack.top() <<" ";
    //     stack.pop();
    // }

    Node(Gearball ball)
    {
        AStar aStar;
        this->hCost = aStar.heuristic(this->currGearballState);
        this->gCost = gCost; // parent gCost + 10;
        this->fCost = gCost + hCost;
        this->currGearballState = ball;
    }

    int getFCost()
    {
        this->fCost = gCost + hCost;
        return this->fCost;
    }
};

#endif