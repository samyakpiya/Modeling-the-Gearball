#include "gearball.cpp"
#include "node.cpp"
#include "astar.cpp"

// This program is for testing

int main()
{
    Gearball ball;
    AStar aStar;

    float totalIterations = 5;
    float sum;
    float average;
    int nodesExpanded;

    for (int k = 3; k <= 20; k++)
    {
        sum = 0;

        cout << "Solving " << k << "-randomized puzzle " << totalIterations << " times: " << endl;

        average = 0;
        for (int i = 0; i < 5; i++)
        {
            cout << "Nodes expanded in iteration " << i << ": ";

            ball = Gearball();
            ball.randomize(k, "", 4);

            nodesExpanded = aStar.solve(ball, false);
            cout << nodesExpanded << endl;

            sum += nodesExpanded;
        }
        cout << "Average nodes expanded is: " << sum / totalIterations << endl
             << endl;
    }
}