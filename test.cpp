#include <iostream>
using namespace std;

class Test
{
public:
    int testNumber;

    Test getTest()
    {
        return *this;
    }

    void setTestNumber(int testNumber)
    {
        this->testNumber = testNumber;
    }

    Test(int testNumber)
    {
        this->setTestNumber(testNumber);
    }

    Test()
    {
        this->testNumber = 0;
    }
};

int main()
{
    Test test1 = Test(1);
    Test test2;
    test2 = test1.getTest();
    test2.setTestNumber(2);

    cout << test1.testNumber << endl;
    cout << test2.testNumber;
}