#include <stack>

class Node
{
public:
    int gCost;
    int hCost;
    stack<int> movesPerformed;
    // stack.push(elm)
    // stack.pop()
    //
    // while (!stack.empty()) {
    //     cout << stack.top() <<" ";
    //     stack.pop();
    // }

    void storeMove(int movePerformed)
    {
        this->movesPerformed.push(movePerformed);
    }

    Node()
    {
    }

    int getFCost()
    {
        return hCost + gCost;
    }
};
