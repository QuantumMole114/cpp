#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

#define MAX 10

using namespace std;

struct techinf
{
    string num;
    string name;
    string title;
    int workage;
    double dSalary[15];
    double dTax;
    double lastsalary;
};
struct techBook
{
    techinf personArray[MAX];
    int m_Size; // 记录表中人数
};

// 计算个调税
double taxCount(double month_income)
{
    double rate;
    if (month_income <= 5000)
    {
        return 0;
    }
    else if (month_income <= 8000)
    {
        rate = 0.03;
        return (month_income - 5000) * rate;
    }
    else if (month_income <= 17000)
    {
        rate = 0.1;
        return (month_income - 5000) * rate;
    }
    else if (month_income <= 30000)
    {
        rate = 0.2;
        return (month_income - 5000) * rate;
    }
    else if (month_income <= 40000)
    {
        rate = 0.25;
        return (month_income - 5000) * rate;
    }
    else if (month_income <= 60000)
    {
        rate = 0.3;
        return (month_income - 5000) * rate;
    }

    else if (month_income <= 85000)
    {
        rate = 0.35;
        return (month_income - 5000) * rate;
    }
    else
    {
        rate = 0.45;
        return (month_income - 5000) * rate;
    }
}

// 计算个调税和实发工资，从setinfo中脱离出便于在调整工资之后重新计算
void calculateTaxLastsalary(techinf *t)
{
    // 计算总收入
    double total = 0;
    for (int i = 0; i < 8; i++)
    {
        total += t->dSalary[i];
    }

    for (int i = 8; i < 15; i++)
    {
        total += t->dSalary[i];
    }

    // 计算个调税和实发工资
    t->dTax = taxCount(total);       // 个调税
    t->lastsalary = total - t->dTax; // 实发工资
}

// 设置员工信息
void setInfo(techBook *abs)
{
    int total; // 录入人数
    cout << "请输入录入人数:";
    cin >> total;

    for (int i = 0; i < total; i++)
    {
        if (abs->m_Size >= MAX) // 确保不超过数组上限
        {
            cout << "人员已达到最大数量，无法继续添加。" << endl;
            break;
        }

        cout << "当前录入第" << i + 1 << "位职工的信息" << endl;
        cout << "请输入职工工号: ";
        cin >> abs->personArray[abs->m_Size].num;
        cout << "请输入姓名: ";
        cin >> abs->personArray[abs->m_Size].name;
        cout << "请输入职称: ";
        cin >> abs->personArray[abs->m_Size].title;
        cout << "请输入工龄: ";
        cin >> abs->personArray[abs->m_Size].workage;

        cout << "请输入职工的15项工资明细: " << endl;
        for (int j = 0; j < 15; j++)
        {
            cout << "请输入第" << j + 1 << "项: ";
            cin >> abs->personArray[abs->m_Size].dSalary[j];
        }

        // 计算个调税和实发工资
        calculateTaxLastsalary(&abs->personArray[abs->m_Size]);

        // 录入完成，m_Size 自增，指向下一个空位置
        abs->m_Size++;
        system("clear");
    }

    cout << "录入完成" << endl;
}

// 求最大最小和平均值
void maxMinAvg(techBook *abs)
{
    if (abs->m_Size == 0)
    {
        cout << "没有任何职工信息，无法计算最值和平均值。" << endl;
        return;
    }

    double sum = 0;
    double salaryArray[MAX];

    // 构建工资数组

    for (int i = 0; i < abs->m_Size; i++)

    {

        salaryArray[i] = abs->personArray[i].lastsalary;
    }

    // 找最大值和最小值的迭代器

    auto maxIt = max_element(salaryArray, salaryArray + abs->m_Size);

    auto minIt = min_element(salaryArray, salaryArray + abs->m_Size);

    // 计算索引

    int maxIndex = distance(salaryArray, maxIt);

    int minIndex = distance(salaryArray, minIt);

    // 计算平均值

    for (int i = 0; i < abs->m_Size; i++)

    {

        sum += salaryArray[i];
    }

    double avg = sum / abs->m_Size;

    // 统计小于平均工资的员工数量

    int countBelowAvg = 0;

    for (int i = 0; i < abs->m_Size; i++)

    {

        if (salaryArray[i] < avg)

        {

            countBelowAvg++;
        }
    }

    // 打印最大值、最小值及对应职工信息

    cout << "最大工资职工信息: 工号 = " << abs->personArray[maxIndex].num

         << ", 姓名 = " << abs->personArray[maxIndex].name

         << ", 实发工资 = " << abs->personArray[maxIndex].lastsalary << endl;

    cout << "最小工资职工信息: 工号 = " << abs->personArray[minIndex].num

         << ", 姓名 = " << abs->personArray[minIndex].name

         << ", 实发工资 = " << abs->personArray[minIndex].lastsalary << endl;

    // 打印平均值和小于平均工资的员工数量

    cout << "职工平均工资 = " << avg << endl;

    cout << "小于平均工资的员工人数 = " << countBelowAvg << endl;
}

// 用于依次打印工资细则，与showInfo配合
void showSalary(techBook *abs, int j)
{

    for (int i = 0; i < (sizeof(abs->personArray[0].dSalary) / sizeof(abs->personArray[0].dSalary[0])); i++)
    {
        cout << abs->personArray[j].dSalary[i] << "\t";
    }
}

// 显示信息
void showInfo(techBook *abs)
{
    cout << "工号\t"

         << "姓名\t"

         << "职称\t"

         << "岗位工资\t"

         << "薪级工资\t"

         << "岗位津贴\t"

         << "生活补贴\t"

         << "奖励绩效\t"

         << "公积金贴\t"

         << "逐月房贴\t"

         << "交通贴\t"

         << "应缴公积金 \t"

         << "失业险 \t"

         << "养老险 \t"

         << "职业年金 \t"

         << "医疗险 \t"

         << "工会费\t"

         << "医互金\t"

         << "个调税\t"

         << "实发工资\t" << endl;

    for (int i = 0; i < abs->m_Size; i++)
    {
        cout << abs->personArray[i].num << "\t"
             << abs->personArray[i].name << "\t"
             << abs->personArray[i].title << "\t";

        showSalary(abs, i);

        cout << abs->personArray[i].dTax << "\t";
        cout << abs->personArray[i].lastsalary << "\t";
    }
}

// 调整工资
void adjustSalary(techBook *abs)
{
    for (int i = 0; i < abs->m_Size; i++)
    {
        // 按职称调整岗位工资
        if (abs->personArray[i].title == "教授")
        {
            abs->personArray[i].dSalary[0] *= 1.1;
        }
        else if (abs->personArray[i].title == "副教授")
        {
            abs->personArray[i].dSalary[0] *= 1.08;
        }
        else if (abs->personArray[i].title == "讲师")
        {
            abs->personArray[i].dSalary[0] *= 1.05;
        }

        else if (abs->personArray[i].title == "初级")
        {
            abs->personArray[i].dSalary[0] *= 1.04;
        }

        else if (abs->personArray[i].title == "其他")
        {
            abs->personArray[i].dSalary[0] *= 1.03;
        }

        // 按工作时间调整薪级工资
        if (abs->personArray[i].workage >= 25)
        {
            abs->personArray[i].dSalary[1] += 60;
        }

        else if (abs->personArray[i].workage > 20)
        {
            abs->personArray[i].dSalary[1] += 55;
        }

        else if (abs->personArray[i].workage > 15)
        {
            abs->personArray[i].dSalary[1] += 50;
        }

        else if (abs->personArray[i].workage > 10)
        {
            abs->personArray[i].dSalary[1] += 45;
        }

        else if (abs->personArray[i].workage >= 1)
        {
            abs->personArray[i].dSalary[1] += 40;
        }

        calculateTaxLastsalary(&abs->personArray[i]); // 重新计算个调税和实发工资
    }
}

// 删除工资记录
void deleteSalaryInfo(techBook *abs)
{
    string num;
    int index;
    cout << "请输入要删除的员工工号：";
    cin >> num;
    for (int i = 0; i < abs->m_Size; i++)
    {
        if (num == abs->personArray[i].num)
        {
            index = i;
        }
    }
    for (int j = index; j < abs->m_Size - 1; j++)
    {
        abs->personArray[j] = abs->personArray[j + 1];
    }
    cout << "删除成功" << endl;
}

// 查询工资记录
void searchInfo(techBook *abs)
{
    string num;
    cout << "请输入要查询的员工工号：";
    cin >> num;
    for (int i = 0; i < abs->m_Size; i++)
    {
        if (num == abs->personArray[i].num)
        {
            cout << "工号\t"
                 << "姓名\t"
                 << "职称\t"
                 << "岗位工资\t"
                 << "薪级工资\t"
                 << "岗位津贴\t"
                 << "生活补贴\t"
                 << "奖励绩效\t"
                 << "公积金贴\t"
                 << "逐月房贴\t"
                 << "交通贴\t"
                 << "应缴公积金\t"
                 << "失业险\t"
                 << "养老险\t"
                 << "职业年金\t"
                 << "医疗险\t"
                 << "工会费\t"
                 << "医互金\t"
                 << "个调税\t"
                 << "实发工资\t" << endl;
            cout << abs->personArray[i].num << "\t" << abs->personArray[i].name
                 << "\t" << abs->personArray[i].title << "\t";

            showSalary(abs, i);

            cout << abs->personArray[i].dTax << "\t";
            cout << abs->personArray[i].lastsalary << "\t";
        }
    }
}

// 修改工资记录
void editSalary(techBook *abs)
{
    string num;
    int index;
    cout << "请输入需要修改的员工工号: ";
    cin >> num;
    for (int i = 0; i < abs->m_Size; i++) // 查找该员工在数组中的索引
    {
        if (num == abs->personArray[i].num)
        {
            index = i;
            cout << "已找到该员工" << endl;
        }
    }
    cout << "请重新输入15项工资(空格隔开):";
    for (int j = 0; j < abs->m_Size; j++)
    {
        cin >> abs->personArray[index].dSalary[j];
    }
    cout << "修改成功" << endl;
}

// 根据实发工资排序
void lastSalarySort(techBook *abs)
{
    for (int i = 0; i < abs->m_Size - 1; i++)
    {
        for (int j = 0; j < abs->m_Size - i - 1; j++)
        {
            if (abs->personArray[j].lastsalary > abs->personArray[j + 1].lastsalary)
            {
                techinf temp = abs->personArray[j];
                abs->personArray[j] = abs->personArray[j + 1];
                abs->personArray[j + 1] = temp;
            }
        }
    }
    showInfo(abs);
}

// 插入工资信息
void insertSalary(techBook *abs)
{
}

int main()
{
    techBook abs;
    abs.m_Size = 0;
    int quit = 1;
    while (quit != 0)
    {
        int select;
        cout << "*************************工资管理系统***************************" << endl;
        cout << "*****************************菜单******************************" << endl;
        cout << "1、录入工资(批量)          2、删除工资记录" << endl;
        cout << "3、查询工资记录            4、修改工资记录" << endl;
        cout << "5、插入工资(单条)          6、统计分析" << endl;
        cout << "7、工资记录排序		    8、调整工资" << endl;
        cout << "9、显示工资记录            0、退出管理系统" << endl;
        cout << "****************************************************************" << endl;
        cout << "************************* 请选择0-9: ****************************" << endl;
        cin >> select;
        switch (select)
        {
        case 1:
            setInfo(&abs);
            cout << "按回车返回菜单" << endl;
            cin.get();
            cin.get();
            system("clear");
            break;
        case 2:
            deleteSalaryInfo(&abs);
            cout << "按回车返回菜单" << endl;
            cin.get();
            cin.get();
            system("clear");
            break;
        case 3:
            searchInfo(&abs);
            cout << "按回车返回菜单" << endl;
            cin.get();
            cin.get();
            system("clear");
            break;
        case 4:
            editSalary(&abs);
            cout << "按回车返回菜单" << endl;
            cin.get();
            cin.get();
            system("clear");
            break;
        case 5:
            break;
        case 6:
            maxMinAvg(&abs);
            cout << "按回车返回菜单" << endl;
            cin.get();
            cin.get();
            system("clear");
            break;
        case 7:
            lastSalarySort(&abs);
            cout << "按回车返回菜单" << endl;
            cin.get();
            cin.get();
            system("clear");
            break;
        case 8:
            maxMinAvg(&abs);
            cout << "按回车返回菜单" << endl;
            cin.get();
            cin.get();
            system("clear");
            break;
        case 9:
            showInfo(&abs);
            cout << "按回车返回菜单" << endl;
            cin.get();
            cin.get();
            system("clear");
            break;
        case 0:
            cout << "欢迎下次使用" << endl;
            quit = 0;
            break;
        }
    }
}