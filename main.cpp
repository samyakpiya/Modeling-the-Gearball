
#include "gearball.cpp"
#include "node.cpp"
#include <queue>
#include <vector>
#include "astar.cpp"

string showMenu(Gearball ball)
{
     string userChoice;
     cout
         << "Please choose from the following menu options: " << endl;
     cout << "1. Randomize the gearball" << endl;
     cout << "2. Solve the gearball" << endl;
     cout << "3. Perform manual rotations on the ball" << endl;
     cout << "4. Check if the gearball is solved" << endl;
     cout << "5. Quit" << endl;
     cout << "Enter the menu option you want: ";
     cin >> userChoice;
     if (userChoice == "2" && ball.isSolved())
     {
          cout << "The ball is already solved. You need to randomize it first!" << endl
               << endl;
          return "1";
     }

     if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4" || userChoice == "5")
     {
          return userChoice;
     }
     else
     {
          cout << "You chose an invalid menu option (valid choices are 1, 2, 3, 4 , 5)." << endl
               << endl;
          return showMenu(ball);
     }
}

string rotationMenu(Gearball ball)
{
     string userChoice;
     cout << endl;
     cout << "Please choose from the following rotation options:" << endl;
     cout << "1. Rotate the Gearball Top Clockwise" << endl;
     cout << "2. Rotate the Gearball Bottom Clockwise" << endl;
     cout << "3. Rotate the Gearball Left Clockwise" << endl;
     cout << "4. Rotate the Gearball Right Clockwise" << endl;
     cout << "5. Rotate the Gearball Top Counter Clockwise" << endl;
     cout << "6. Rotate the Gearball Bottom Counter Clockwise" << endl;
     cout << "7. Rotate the Gearball Left Counter Clockwise" << endl;
     cout << "8. Rotate the Gearball Right Counter Clockwise" << endl;
     cout << "Enter the rotation number you want to perform: ";
     cin >> userChoice;

     if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4" || userChoice == "5" || userChoice == "6" || userChoice == "7")
     {
          return userChoice;
     }
     else
     {
          cout << "You chose an invalid menu option (valid choices are 1, 2, 3, 4, 5, 6, 7)." << endl
               << endl;
          return rotationMenu(ball);
     }
}

int main()
{
     // Creates a gearball object that is initially solved
     Gearball ball = Gearball();
     AStar aStar;

     cout << "Welcome to the Gearball Puzzle!" << endl;

     cout
         << endl
         << "Solved Gearball GUI Output: " << endl
         << endl;

     // Print the gearball in its solved state
     ball.printBall();

     bool resume = true;
     while (resume)
     {
          cout << endl;

          string userChoice = showMenu(ball);
          if (userChoice == "1")
          {
               cout << endl;
               string numOfRotations;
               cout << "Enter the number of random rotations to perform on the gearball: ";
               cin >> numOfRotations;

               // Perform "numOfRotations" random rotations on the gearball
               ball.randomizeCC(stoi(numOfRotations), true);
          }
          else if (userChoice == "2")
          {
               cout << endl;
               aStar.solve(ball);
          }
          else if (userChoice == "3")
          {
               cout << endl;
               string moveToPerform = rotationMenu(ball);
               int rotation = stoi(moveToPerform) - 1;
               ball.rotate(rotation, true);
          }
          else if (userChoice == "4")
          {
               if (ball.isSolved())
               {
                    cout << endl;
                    cout << "The Gearball is in a solved state!" << endl;
               }
               else
               {
                    cout << endl;
                    cout << "The Gearball is in an unsolved state!" << endl;
               }
          }
          else
          {
               cout << "Quitting the program!" << endl;
               resume = false;
          }
     }

     return 0;
}