
#include "gearball.cpp"
#include "node.cpp"
#include <queue>
#include <vector>
// #include "astar.cpp"

// Admissible Heuristic: The number of pieces out of position divided by 36. 36 is the number of pieces that go out of position when one rotation is performed on a solved gearball.
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
     cout << "The pieces that are out of position are: " << piecesOutOfPos;

     int hValue = piecesOutOfPos / 36;
     return hValue;
}

void solve(Gearball ball)
{
     // auto cmp = [](int left, int right)
     // { return (left) < (right); };
     // priority_queue<int, vector<int>, decltype(cmp)> OPEN(cmp);

     // for (int elm : {9, 8, 7, 6, 5, 4, 3, 2, 1, -1})
     // {
     //      OPEN.push(elm);
     // }
     // OPEN //the set of nodes to be evaluated
     // CLOSED //the set of nodes already evaluated
     // g_cost = distance from starting node
     // h_cost = distance from end node
     // f_cost = g_cost + h_cost

     // priority_queue<int, vector<int>, greater<int>> OPEN;

     // Use two min heaps one for f-value, the other for h-cost sorting

     // add the start node to OPEN

     // while (ball.isSolved() != 1)
     // {
     //      for (int i = 0; i < 4; i++)
     //      {
     //           OPEN.push(ball.rotate(i));
     //      }
     // }

     // loop
     //         current = node in OPEN with the lowest f_cost
     //         remove current from OPEN
     //         add current to CLOSED

     //         if current is the target node //path has been found
     //                 return

     //         foreach neighbour of the current node
     //                 if neighbour is not traversable or neighbour is in CLOSED
     //                         skip to the next neighbour

     //                 if new path to neighbour is shorter OR neighbour is not in OPEN
     //                         set f_cost of neighbour
     //                         set parent of neighbour to current
     //                         if neighbour is not in OPEN
}

int main()
{
     // Creates a gearball object that is initially solved
     Gearball ball = Gearball();

     cout
         << endl
         << "Solved Gearball GUI Output: " << endl
         << endl;

     // Print the gearball in its solved state
     ball.printBall();

     string numOfRotations;
     cout << "Enter the number of random rotations to perform on the gearball: ";
     cin >> numOfRotations;

     // Perform "numOfRotations" random rotations on the gearball
     ball.randomizeCC(stoi(numOfRotations));

     int h_value = heuristic(ball);

     return 0;
}