#ifndef NODE
#define NODE
#include "gearball.cpp"

class Node
{
public:
    int gCost;
    int hCost;
    int fCost;
    int movePerformed;
    Gearball currGearballState;
    Node *parent;

    // Might not need these lines of code as we are storing the current state of the Gearball
    // stack<int> movesPerformed;
    // stack.push(elm)
    // stack.pop()
    //
    // while (!stack.empty()) {
    //     cout << stack.top() <<" ";
    //     stack.pop();
    // }
    void setFCost()
    {
        this->fCost = this->gCost + this->hCost;
    }

    void setHCost(int h)
    {
        this->hCost = h;
        this->setFCost();
    }

    void setGCost(int g)
    {
        this->gCost = g;
        this->setFCost();
    }

    void setCosts(int g, int h)
    {
        this->setGCost(g);
        this->setHCost(h);
    }

    // for initializing the root node use this constructor
    Node(Gearball ball, int hCost)
    {
        // AStar aStar;
        this->currGearballState = ball;
        this->parent = NULL;
        this->movePerformed = -1;
        this->hCost = hCost;
        this->gCost = 0;
        this->setFCost();
    }

    Node(Gearball ball, Node *parent)
    {
        // AStar aStar;
        this->currGearballState = ball;
        this->parent = parent;
        // this->hCost = aStar.heuristic(this->currGearballState);
        // if (this->parent != NULL)
        // {
        //     this->gCost = this->parent->gCost + 10;
        // }
        // else
        // {
        //     this->gCost = 0;
        // }
    }

    Node(int movePerformed, Gearball ball, int hCost, Node *parent)
    {
        // AStar aStar;
        this->currGearballState = ball;
        this->parent = parent;
        this->setHCost(hCost);
        this->setGCost(this->parent->gCost + 10);
        this->movePerformed = movePerformed;
    }

    void setParent(Node *parent)
    {
        this->parent = parent;
        this->setGCost(this->parent->gCost + 10);
        this->setFCost();
    }
};

#endif