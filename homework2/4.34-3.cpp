#include <iostream>
using namespace std;

double factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }

    double count = 1;
    while (n > 0)
    {
        count *= n;
        n--;
    }
    return count;
}

int main()
{
    int n, x;
    cout << "请输入想要的e^x的精度(累加的项数): ";
    cin >> n;
    cout << "请输入x: ";
    cin >> x;

    double e_x = 0;
    int i = 1;

    int x_count = x;
    while (i <= n)
    {
        x_count *= x;
        e_x += x_count / factorial(i);
        i++;
    }

    return 0;
}
