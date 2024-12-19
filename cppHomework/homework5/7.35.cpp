#include <iostream>
#include <string>
using namespace std;

int main()
{
    string topics[5] = {"Q1(1-10): ", "Q2(1-10): ", "Q3(1-10): ", "Q4(1-10): ", "Q5(1-10): "};
    int responses[5][10];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << topics[j] << endl;
            cin >> responses[i][j];
        }
    }

    // 赋初始值
    int responsesCount[5][12];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            responsesCount[i][j] = 0;
        }
    }

    // 统计各得分
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                if (responses[i][j] == k + 1)
                {
                    responsesCount[i][k]++;
                }
            }
        }
    }

    // 计算总分和平均分
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            responsesCount[i][10] += responsesCount[i][j] * (j + 1); // 第11项存放总分
            responsesCount[i][11] = responsesCount[i][10] / 10;      // 第12项存放平均分
        }
    }

    // 打印表格
    cout << "\t";
    for (int i = 0; i < 10; i++)
    {
        cout << i + 1 << "\t";
    }
    cout << "总分\t" << "平均分\t";
    cout << "\n";

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            cout << "Q" << i + 1 << ": \t";
            cout << responsesCount[i][j];
        }
    }
    cout << endl;

    // 找出最大最小值
    int totalTemp[5];
    for (int i = 0; i < 5; i++)
    {
        totalTemp[i] = responsesCount[i][10];
    }

    sort(totalTemp, totalTemp + 5);
    int MAX = totalTemp[4];
    int MIN = totalTemp[0];

    for (int i = 0; i < 5; i++)
    {
        if (responsesCount[i][11] == MAX)
        {
            cout << "总分最高的是Q" << i + 1 << endl;
        }
        if (responsesCount[i][11] == MIN)
        {
            cout << "总分最低的是Q" << i + 1 << endl;
        }
    }

    return 0;
}