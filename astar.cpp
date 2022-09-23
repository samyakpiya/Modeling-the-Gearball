#include "gearball.cpp"
#include <functional>
#include <queue>
#include <vector>

int main()
{
        priority_queue<int, vector<int>, greater<int>> q; // queue in min heap order (lowest value is at the top)
        int elm[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, -1};
        for (int i = 0; i < 10; i++)
        {
                q.push(elm[i]);
        }

        cout << q.top();

        auto cmp = [](int left, int right)
        { return (left) < (right); };
        priority_queue<int, vector<int>, decltype(cmp)> q3(cmp);

        for (int elm : {9, 8, 7, 6, 5, 4, 3, 2, 1, -1})
        {
                q3.push(elm);
        }
}

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
