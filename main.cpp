
#include "gearball.cpp"
#include "node.cpp"
#include <queue>
#include <vector>
#include "astar.cpp"

// Using the AStar algorithm to pathfind a sequence of moves that solves the current gearball
void solve(Gearball ball)
{
     auto cmp = [](Node x, Node y)
     { if (x.fCost != y.fCost) {
          return x.fCost > y.fCost;
     } else {
          return x.hCost > y.hCost;
     } };

     // OPEN //the set of nodes to be evaluated
     priority_queue<Node, vector<Node>, decltype(cmp)> OPENED(cmp);

     // CLOSED //the set of nodes already evaluated
     vector<Node> CLOSED;

     // g_cost = distance from starting node
     // h_cost = distance from end node
     // f_cost = g_cost + h_cost

     // add the start node to OPEN
     Node root = Node(ball);
     OPENED.push(root);

     // loop until the ball is solved
     while (ball.isSolved() != 1)
     {
          // current = node in OPEN with the lowest f_cost
          Node current = OPENED.top();

          // remove current from OPEN
          OPENED.pop();

          // add current to CLOSED
          CLOSED.push_back(current);

          // if current is the target node //path has been found
          // return
          if (current.currGearballState.isSolved())
          {
               cout << "The gearball has been solved!" << endl;
               return;
          }

          Node neighbours[4] = {current.rotate(ROTATE_TCCW), current.rotate(ROTATE_BCCW), current.rotate(ROTATE_LCCW), current.rotate(ROTATE_RCCW)};

          bool find(Node nodeToFind, vector<Node> vecNodes)
          {
               for (auto &node : vecNodes)
               {
                    if (node.currGearballState.isEqual(nodeToFind))
                    {
                         return true;
                    }
               }
               return false;
          }

          // foreach neighbour of the current node
          for (Node neighbour : neighbours)
          {
               // if neighbour is not traversable or neighbour is in CLOSED
               if (find(neighbour, CLOSED))
               {
                    // skip to the next neighbour
                    continue;
               }

               // if new path to neighbour is shorter OR neighbour is not in OPEN
               if ()
               {
               }
               //         set f_cost of neighbour
               //         set parent of neighbour to current
               //         if neighbour is not in OPEN
               //                  add neighbour to OPEN
          }
     }

     //         foreach neighbour of the current node
     //                 if neighbour is not traversable or neighbour is in CLOSED
     //                         skip to the next neighbour

     //                 if new path to neighbour is shorter OR neighbour is not in OPEN
     //                         set f_cost of neighbour
     //                         set parent of neighbour to current
     //                         if neighbour is not in OPEN
     //                                  add neighbour to OPEN
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

     AStar aStar;

     int h_value = aStar.heuristic(ball);

     return 0;
}