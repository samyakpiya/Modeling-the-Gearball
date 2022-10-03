
#include "gearball.cpp"
#include "node.cpp"
#include "astar.cpp"

// Menu Options
string showMenu(Gearball ball)
{
     string userChoice;
     cout
         << "Please choose from the following menu options: " << endl;
     cout << "1. Randomize the gearball" << endl;
     cout << "2. Solve the gearball" << endl;
     cout << "3. Perform manual rotations on the ball" << endl;
     cout << "4. Check if the gearball is solved" << endl;
     cout << "5. Print gearball's current state" << endl;
     cout << "6. Restart program" << endl;
     cout << "7. Quit" << endl;
     cout << "Enter the menu option you want: ";
     cin >> userChoice;
     if (userChoice == "2" && ball.isSolved())
     {
          cout << "The ball is already solved. You need to randomize it first!" << endl
               << endl;
          return "1";
     }

     if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4" || userChoice == "5" || userChoice == "6" || userChoice == "7")
     {
          return userChoice;
     }
     else
     {
          cout << "You chose an invalid menu option (valid choices are 1, 2, 3, 4, 5, 6, 7)." << endl
               << endl;
          return showMenu(ball);
     }
}

// Menu Options for performing manual rotations on the gearball
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
     cout << "9. Go Back" << endl;
     cout << "Enter the rotation number you want to perform: ";
     cin >> userChoice;

     if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4" || userChoice == "5" || userChoice == "6" || userChoice == "7" || userChoice == "8" || userChoice == "9")
     {
          return userChoice;
     }
     else
     {
          cout << "You chose an invalid menu option (valid choices are 1, 2, 3, 4, 5, 6, 7, 8, 9)." << endl
               << endl;
          return rotationMenu(ball);
     }
}

// prints the Welcome Message to display ot users
void printWelcomeMessage(Gearball ball)
{
     cout << "Welcome to the Gearball Puzzle!" << endl;

     cout
         << endl
         << "Solved Gearball GUI Output: " << endl
         << endl;

     // Print the gearball in its solved state
     ball.printBall();
}

int main()
{
     // Creates a gearball object that is initially in a solved state
     Gearball ball = Gearball();
     AStar aStar;

     printWelcomeMessage(ball);

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
               ball.randomize(stoi(numOfRotations), 4, true);
          }
          else if (userChoice == "2")
          {
               cout << endl;
               int rotationsPerformed = 1;
               bool condition = true;

               aStar.solve(ball);
          }
          else if (userChoice == "3")
          {
               bool rotationMenuResume = true;
               while (rotationMenuResume)
               {
                    cout << endl;
                    string moveToPerform = rotationMenu(ball);
                    if (moveToPerform == "1" || moveToPerform == "2" || moveToPerform == "3" || moveToPerform == "4" || moveToPerform == "5" || moveToPerform == "6" || moveToPerform == "7" || moveToPerform == "8")
                    {
                         int rotation = stoi(moveToPerform) - 1;
                         ball.rotate(rotation, true);
                    }
                    else
                    {
                         rotationMenuResume = false;
                    }
               }
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
          else if (userChoice == "5")
          {
               cout << endl;

               cout << "Printing the Gearball's current state: " << endl
                    << endl;
               ball.printBall();
          }
          else if (userChoice == "6")
          {
               cout << endl;
               cout << "Restarting Program..." << endl
                    << endl;

               ball = Gearball();
               printWelcomeMessage(ball);
          }
          else
          {
               cout << "Quitting the program!" << endl;
               resume = false;
          }
     }

     return 0;
}