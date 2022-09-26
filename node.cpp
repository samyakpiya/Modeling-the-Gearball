#ifndef NODE
#define NODE
#include "gearball.cpp"

class Node
{
public:
    int movePerformed;
    Gearball ball;

    float gCost;
    float hCost;
    Node *parent;

    float getFCost()
    {
        return gCost + hCost;
    }

    // initialize the root node use this constructor
    Node(Gearball _ball)
    {
        ball = _ball;
        parent = NULL; // making the object the root node
    }

    Node(int _movePerformed, Gearball _ball)
    {
        movePerformed = _movePerformed;
        ball = _ball;
    }

    bool operator==(const Node &other)
    {
        return ball.isEqual(other.ball);
    }
};

#endif