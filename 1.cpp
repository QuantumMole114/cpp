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

// 冒泡排序
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

// 删除工资记录
void deleteSalaryInfo(techBook *abs)
{
    string num;
    int index = -1;
    cout << "请输入要删除的员工工号：";
    cin >> num;
    for (int i = 0; i < abs->m_Size; i++)
    {
        if (num == abs->personArray[i].num)
        {
            index = i;
        }
    }
    // 检查是否找到员工记录
    if (index == -1)
    {
        cout << "未找到工号为 " << num << " 的员工信息，删除失败！" << endl;
        return;
    }
    for (int j = index; j < abs->m_Size - 1; j++)
    {
        abs->personArray[j] = abs->personArray[j + 1];
    }
    saveToFile(abs, "source.txt");
    cout << "删除成功" << endl;
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
    // 检查是否找到员工记录
    if (index == -1)
    {
        cout << "未找到工号为 " << num << " 的员工信息，删除失败！" << endl;
        return;
    }
    cout << "请重新输入15项工资(空格隔开):";
    for (int j = 0; j < abs->m_Size; j++)
    {
        cin >> abs->personArray[index].dSalary[j];
    }
    cout << "修改成功" << endl;

    saveToFile(abs, "source.txt");
}