#ifndef ASTAR
#define ASTAR

#include "gearball.cpp"
#include <functional>
#include <queue>
#include <vector>

// Admissible Heuristic: The number of pieces out of position divided by 36. 36 is the number of pieces that go out of position when one rotation is performed on a solved gearball.
class AStar
{
public:
        double heuristic(Gearball ball)
        {
                Side *currentBall = ball.getSides();

                int piecesOutOfPos = 0;
                string currPieceColor;

                // iterate through each face of the gearball
                for (int sides = 0; sides < SIDES; sides++)
                {
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
                                                if (sides == TOP && currPieceColor != "Y")
                                                {
                                                        piecesOutOfPos++;
                                                }
                                                else if (sides == BOTTOM && currPieceColor != "O")
                                                {
                                                        piecesOutOfPos++;
                                                }
                                                else if (sides == LEFT && currPieceColor != "B")
                                                {
                                                        piecesOutOfPos++;
                                                }
                                                else if (sides == RIGHT && currPieceColor != "G")
                                                {
                                                        piecesOutOfPos++;
                                                }
                                                else if (sides == FRONT && currPieceColor != "R")
                                                {
                                                        piecesOutOfPos++;
                                                }
                                                else if (sides == REAR && currPieceColor != "P")
                                                {
                                                        piecesOutOfPos++;
                                                }
                                        }
                                }
                        }
                }

                // Comment
                int hValue = piecesOutOfPos / 36;

                cout << "The pieces that are out of position are: " << piecesOutOfPos << endl;
                cout << "The h Values for this Gearball state is: " << hValue << endl;

                return hValue;
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