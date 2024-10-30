#include <iostream>
using namespace std;
int main()
{
    unsigned int count = 1;
    while (count <= 10)
    {
        cout << (count%2 ?"****":"++++++++") << endl;
        ++count;
    }
    
    return 0;
}