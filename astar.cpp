#ifndef ASTAR
#define ASTAR

#include "gearball.cpp"
#include "node.cpp"
#include <queue> // for min priority_queue
#include <vector>
#include <stack>
#include <algorithm> // needed erase(), count()

// We used Admissible Heurisitc 2
// Admissible Heuristic 1 (intial): The number of pieces out of position divided by 36. 36 is the number
// of pieces that go out of position when one rotation is performed on a solved gearball.
// AH1 is not good in our case because of how our code prints the ball. If all the faces were solved but
// the front face changed from red to blue in the final solved state, every single piece would be out of position.

// Admissible Heuristic 2 (final): The number of pieces that do not match the color of the center piece
// divided by 32 and then multiplied by 10 (i.e. the number of pieces that do not match the center piece
// color when a rotation is performed)

class AStar
{

public:
    // Evaluates the h-value of a gearball state and returns it
    // uses admissible heuristic 2
    float heuristic(Gearball ball, int movePerformed)
    {
        Side *currentBall = ball.getSides();

        float piecesOutOfPos = 0;
        string centerPieceColor;
        string currPieceColor;

        // iterate through each face of the gearball
        for (int sides = 0; sides < SIDES; sides++)
        {
            centerPieceColor = currentBall[sides].getPiece(2, 2).getColor();
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                {

                    currPieceColor = currentBall[sides].getPiece(i, j).getColor();
                    if (currPieceColor == " ")
                    {
                        continue;
                    }
                    else
                    {
                        if (currPieceColor != centerPieceColor)
                        {
                            piecesOutOfPos++;
                        }
                    }
                }
            }
        }

        float hValue = (piecesOutOfPos / 32) * 10;

        // For testing:
        // cout << "The pieces that are out of position are: " << piecesOutOfPos << endl;
        // cout << "The h Values for turning the Gearball " << intToMovePerformed(movePerformed) << " is: " << hValue << endl;

        return hValue;
    }

    string intToMovePerformed(int movePerformed)
    {
        switch (movePerformed)
        {
        case ROTATE_TCW:
            return "Top Clockwise";
        case ROTATE_BCW:
            return "Bottom Clockwise";
        case ROTATE_LCW:
            return "Left Clockwise";
        case ROTATE_RCW:
            return "Right Clockwise";
        case ROTATE_TCCW:
            return "Top Counter Clockwise";
        case ROTATE_BCCW:
            return "Bottom Counter Clockwise";
        case ROTATE_LCCW:
            return "Left Counter Clockwise";
        case ROTATE_RCCW:
            return "Right Counter Clockwise";
        default:
            return "Wrong rotation int entered!";
        }
    }

    // Trace back to the parent node and print the sequence of moves that solved the gearball
    void retracePath(Node &child, Gearball &ball, int nodesExpanded)
    {
        cout << "The gearball has been solved! The number of nodes expanded to solve the gearball is: " << nodesExpanded << "." << endl
             << endl;

        cout << "Gearball state before solving: " << endl;
        ball.printBall();

        cout << "Steps taken to solve the gearball are as follows: " << endl
             << endl;

        stack<int> movesPerformed;
        // Trace back to the parent node while storing the moves performed on the stack
        while (child.parent != NULL)
        {
            movesPerformed.push(child.movePerformed);
            child = *child.parent;
        }

        // Print the sequence while popping the stack
        int movePerformed;
        int rotationsPerformed = 1;
        while (!movesPerformed.empty())
        {
            movePerformed = movesPerformed.top();
            cout << "S" << rotationsPerformed << "." << intToMovePerformed(movePerformed) << endl;
            ball.rotate(movePerformed);
            ball.printBall();
            movesPerformed.pop();
            rotationsPerformed++;
        }

        return;
    }

    // AStar algorithm to pathfind a sequence of moves that solves the current gearball
    // returns the number of nodes expanded when solving the ball
    int solve(Gearball &ball, bool print = true)
    {
        Node startNode = Node(ball);

        // the set of nodes to be evaluated
        vector<Node> openSet;

        // the set of nodes already evaluated
        vector<Node> closedSet;
        int closedSetIndex = 0;

        // Each node has 4 children at max
        Node children[4];

        // add the start node to OPEN
        openSet.push_back(startNode);

        // loop
        while (!openSet.empty())
        {
            // node = node in OPEN with the lowest f_cost
            Node node = openSet.at(0);
            for (int i = 1; i < openSet.size(); i++)
            {
                if (openSet[i].getFCost() < node.getFCost() || (openSet[i].getFCost() == node.getFCost() && openSet[i].hCost < node.hCost))
                {
                    node = openSet[i];
                }
            }

            // remove current node from openSet
            openSet.erase(remove(openSet.begin(), openSet.end(), node));

            // add current node to closedSet
            closedSet.push_back(node);

            // if current is the target node //path has been found
            //    return
            if (node.ball.isSolved())
            {

                // Trace back to the parent node and print the moves performed to solve the gearball
                if (print)
                    retracePath(node, ball, closedSet.size());

                return closedSet.size();
            }

            // make copies of the current node to create children
            Node nodeTCCW = node;
            Node nodeBCCW = node;
            Node nodeLCCW = node;
            Node nodeRCCW = node;

            // Each gearball state has 4 neighbor states (reached by top, bottom, left, or right clockwise rotations)
            children[0] = (Node(ROTATE_TCCW, nodeTCCW.ball.rotate(ROTATE_TCCW)));
            children[1] = (Node(ROTATE_BCCW, nodeBCCW.ball.rotate(ROTATE_BCCW)));
            children[2] = (Node(ROTATE_LCCW, nodeLCCW.ball.rotate(ROTATE_LCCW)));
            children[3] = (Node(ROTATE_RCCW, nodeRCCW.ball.rotate(ROTATE_RCCW)));

            // foreach child of the current node
            for (Node child : children)
            {

                // if child is not traversable or child is in CLOSED
                if ((count(closedSet.begin(), closedSet.end(), child)))
                {
                    // skip to the next child
                    continue;
                }

                float newCostTochild = node.gCost + 10;

                // if new path to child is shorter OR child is not in OPEN
                if (newCostTochild < child.gCost || !(count(openSet.begin(), openSet.end(), child)))
                {
                    // set f_cost of child
                    child.gCost = newCostTochild;
                    child.hCost = heuristic(child.ball, child.movePerformed);

                    // set parent of child to current
                    child.parent = &closedSet[closedSetIndex];

                    // if child is not in openSet
                    if (!(count(openSet.begin(), openSet.end(), child)))
                    {
                        // add child to openSet
                        openSet.push_back(child);
                    }
                }
            }
            closedSetIndex++;
        }
        return closedSet.size();
    }

    // constructor
    AStar()
    {
    }
};

#endif