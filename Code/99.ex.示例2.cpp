#include <iostream>
#include <string>
using namespace std;
// 设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号

class Student
{
  public: // 公共权限
    // 属性
    string m_name; // 姓名
    int m_id;      // 学号

    // 行为
    void showStudent()
    {
        cout << "姓名: " << m_name << "学号: " << m_id << endl;
    }

    //可以通过行为创建学生信息
    void setName(string name)
    {
        m_name = name;
    }
    void setId(int id)
    {
        m_id = id;
    }

};

int main()
{
    // 创建学生
    Student s1;
    

    return 0;
}