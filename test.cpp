#include "node.cpp"
#include <queue>
#include <vector>
#include "gearball.cpp"

template <typename T>
void print_queue(T &q)
{
    while (!q.empty())
    {
        cout << q.top().fCost << " " << q.top().hCost << endl;
        q.pop();
    }
}

int main()
{
    Gearball ball1 = Gearball();
    Gearball ball2 = Gearball();

    ball1.rotate_bcw();
    ball2.rotate_bcw();

    cout << ball1.isEqual(ball2) << endl;

    return 0;
}