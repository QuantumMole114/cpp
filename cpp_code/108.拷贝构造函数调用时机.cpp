#include <iostream>
using namespace std;

class Person
{
  public:
    Person()
    {
        cout << "Person默认构造函数调用" << endl;
    }
    Person(int age)
    {
        cout << "Person有参构造函数调用" << endl;
        m_age = age;
    }
    Person(const Person &p)
    {
        cout << "Person拷贝构造函数调用" << endl;
        m_age = p.m_age;
    }

    // 析构函数
    ~Person()
    {
        cout << "Person析构函数调用" << endl;
    }
    int m_age;
};

// 拷贝构造函数调用时机

// 1.使用一个已经创建完毕的对象来初始化一个对象
void test01()
{
    Person p1(10);
    Person p2(p1);
    cout << "p2的年龄为: " << p2.m_age << endl;
}

// 2.值传递的方式给函数参数传值
// 3.值方式返回局部对象

int main()
{
    test01();

    return 0;
}