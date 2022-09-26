#ifndef ASTAR
#define ASTAR

#include "gearball.cpp"
#include "node.cpp"
#include <functional>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>

// Admissible Heuristic 1: The number of pieces out of position divided by 36. 36 is the number of pieces that go out of position when one rotation is performed on a solved gearball.
// AH1 is faulty in our case because if all the faces were solved but the front face changed from red to blue in the final solved state, every single piece would be out of position.
// Admissible Heurist 2: The number of pieces that do not match the color of the center piece divided by 32 (i.e. the number of pices that do not match the center piece color when a rotation is performed)
class AStar
{

public:
        float heuristic(Gearball ball)
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
                                                // if (sides == TOP && currPieceColor != "Y")
                                                // {
                                                //         piecesOutOfPos++;
                                                // }
                                                // else if (sides == BOTTOM && currPieceColor != "O")
                                                // {
                                                //         piecesOutOfPos++;
                                                // }
                                                // else if (sides == LEFT && currPieceColor != "B")
                                                // {
                                                //         piecesOutOfPos++;
                                                // }
                                                // else if (sides == RIGHT && currPieceColor != "G")
                                                // {
                                                //         piecesOutOfPos++;
                                                // }
                                                // else if (sides == FRONT && currPieceColor != "R")
                                                // {
                                                //         piecesOutOfPos++;
                                                // }
                                                // else if (sides == REAR && currPieceColor != "P")
                                                // {
                                                //         piecesOutOfPos++;
                                                // }
                                        }
                                }
                        }
                }

                // Comment
                float hValue = piecesOutOfPos / 32;

                cout << "The pieces that are out of position are: " << piecesOutOfPos << endl;
                cout << "The h Values for this Gearball state is: " << hValue << endl;

                return hValue;
        }

        bool find(Node nodeToFind, vector<Node> vecNodes)
        {
                for (auto &node : vecNodes)
                {
                        if (node.currGearballState.isEqual(nodeToFind.currGearballState))
                        {
                                return true;
                        }
                }
                return false;
        }

        // Using the AStar algorithm to pathfind a sequence of moves that solves the current gearball
        void solve(Gearball ball)
        {
                Gearball solvedBall = Gearball();

                Node startNode = Node(ball);
                Node targetNode = Node(solvedBall);

                // min heap comparator
                auto cmp = [](Node x, Node y)
                {
                        if (x.fCost != y.fCost)
                        {
                                return x.fCost > y.fCost;
                        }
                        else
                        {
                                return x.hCost > y.hCost;
                        };
                };

                // OPEN //the set of nodes to be evaluated
                priority_queue<Node, vector<Node>, decltype(cmp)> OPENED(cmp);

                // CLOSED //the set of nodes already evaluated
                vector<Node> CLOSED;

                // add the start node to OPEN
                Node root = Node(ball, this->heuristic(ball));
                OPENED.push(root);

                stack<int> movesPerformed;
                // loop until the ball is solved
                // while (!OPENED.empty())
                for (int i = 0; i < 2; i++)
                {
                        // current = node in OPEN with the lowest f_cost
                        Node currentNode = OPENED.top();

                        // remove current from OPEN
                        OPENED.pop();

                        // add current to CLOSED
                        CLOSED.push_back(currentNode);

                        // if current is the target node //path has been found
                        // return
                        if (currentNode.currGearballState.isSolved())
                        {
                                cout << endl;
                                cout << "-----------The gearball has been solved! -----------" << endl;
                                cout << endl;
                                while (currentNode.parent != NULL)
                                {
                                        movesPerformed.push(currentNode.movePerformed);
                                        currentNode = *currentNode.parent;
                                }

                                while (!movesPerformed.empty())
                                {
                                        ball.rotate(movesPerformed.top());
                                        movesPerformed.pop();
                                }
                                return;
                        }

                        cout << "Neighbors Start:" << endl;
                        Gearball neighborBalls[4] = {currentNode.currGearballState.rotate(ROTATE_TCCW), currentNode.currGearballState.rotate(ROTATE_BCCW), currentNode.currGearballState.rotate(ROTATE_LCCW), currentNode.currGearballState.rotate(ROTATE_RCCW)};
                        Node neighbors[4] = {Node(ROTATE_TCCW, neighborBalls[0], this->heuristic(neighborBalls[0]), &currentNode),
                                             Node(ROTATE_BCCW, neighborBalls[1], this->heuristic(neighborBalls[1]), &currentNode),
                                             Node(ROTATE_LCCW, neighborBalls[2], this->heuristic(neighborBalls[2]), &currentNode),
                                             Node(ROTATE_RCCW, neighborBalls[3], this->heuristic(neighborBalls[3]), &currentNode)};

                        cout << "Neighbors End" << endl;

                        // foreach neighbour of the current node
                        for (Node neighbor : neighbors)
                        {
                                // if neighbour is not traversable or neighbour is in CLOSED
                                if (find(neighbor, CLOSED))
                                {
                                        // skip to the next neighbour
                                        continue;
                                }

                                // if new path to neighbour is shorter OR neighbour is not in OPEN
                                //         set f_cost of neighbour
                                //         set parent of neighbour to current
                                //         if neighbour is not in OPEN
                                //                  add neighbour to OPEN
                                bool newPathShorter = false;
                                int newMovementCostToNeighbor = currentNode.gCost + 10;
                                cout << "newMovemntCostToNeighbor < neighbor.gCost evaluates to: " << (newMovementCostToNeighbor < neighbor.gCost) << endl;
                                if (newMovementCostToNeighbor < neighbor.gCost)
                                {
                                        neighbor.setGCost(newMovementCostToNeighbor);
                                        neighbor.setParent(&currentNode);
                                }
                                OPENED.push(neighbor);

                                // bool neighborInOpen = false;
                                // priority_queue<Node, vector<Node>, decltype(cmp)> OPENED_COPY(cmp);
                                // OPENED_COPY = OPENED;

                                // while (!OPENED_COPY.empty())
                                // {
                                //         if (OPENED_COPY.top().currGearballState.isEqual(neighbor.currGearballState))
                                //         {
                                //                 OPENED_COPY.pop();
                                //                 neighborInOpen = true;
                                //                 break;
                                //         }
                                // }

                                // if (!neighborInOpen)
                                // { // add condition: new path to neighbour is shorter
                                //         if (!neighborInOpen)
                                //         {
                                //                 OPENED.push(neighbor)
                                //         }
                                // }
                        }
                }
        }

        AStar()
        {
        }
};

/*
Heuristic:

Calculate the number of pieces that are out of place and divide that by 36.
If we take a gearball that is in a solved state and perform one rotation on it,
36 pieces are displaced as a result. Hence, we divide the number of pieces
that are out of place by 36.

*/

/*
OPEN //the set of nodes to be evaluated
CLOSED //the set of nodes already evaluated
g_cost = distance from starting node
h_cost = distance from end node
f_cost = g_cost + h_cost


add the start node to OPEN

loop
        current = node in OPEN with the lowest f_cost
        remove current from OPEN
        add current to CLOSED

        if current is the target node //path has been found
                return

        foreach neighbour of the current node
                if neighbour is not traversable or neighbour is in CLOSED
                        skip to the next neighbour

                if new path to neighbour is shorter OR neighbour is not in OPEN
                        set f_cost of neighbour
                        set parent of neighbour to current
                        if neighbour is not in OPEN
*/

#endif