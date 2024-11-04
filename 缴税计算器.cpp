#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>


using namespace std;

// 定义税率和速算扣除数的结构体
struct TaxRate
{
    double upperLimit;
    double rate;
    double quickDeduction;
};

// 初始化方案2的税率表（累计预扣预缴税率）
const TaxRate cumulativeTaxRates[] = {
    {36000, 0.03, 0},
    {144000, 0.10, 2520},
    {300000, 0.20, 16920},
    {420000, 0.25, 31920},
    {660000, 0.30, 52920},
    {960000, 0.35, 85920},
    {1e9, 0.45, 181920} // 使用较大数值代替无穷大
};

// 方案1的月度预扣税率表
const TaxRate monthlyTaxRates[] = {
    {5000, 0.00, 0},
    {8000, 0.03, 0},
    {17000, 0.10, 0},
    {30000, 0.20, 0},
    {40000, 0.25, 0},
    {60000, 0.30, 0},
    {85000, 0.35, 0},
    {1e9, 0.45, 0}};

// 读取txt文件，计算工资收入和扣费
void readMonthlyIncome(const string &fileName, double &monthlyIncome, double &monthlyDeductions)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "无法打开文件: " << fileName << endl;
        exit(1);
    }

    string line;
    bool isIncomePart = true; // 用于判断是工资收入部分还是扣费部分

    while (getline(file, line))
    {
        size_t spacePos = line.find(' ');
        if (spacePos != string::npos)
        {
            string valueStr = line.substr(spacePos + 1);
            try
            {
                double value = stod(valueStr);

                // 根据项目顺序划分工资收入部分和扣费部分
                if (isIncomePart)
                {
                    monthlyIncome += value;
                }
                else
                {
                    monthlyDeductions += value;
                }
            }
            catch (const invalid_argument &e)
            {
                cout << "转换错误: 文件 " << fileName << " 中的金额数据无效，行内容: " << line << endl;
                cout << "错误信息: " << e.what() << endl;
                exit(1);
            }
        }

        // 到达扣费部分时，切换 `isIncomePart` 为 false
        if (line.find("应缴公积金") != string::npos)
        {
            isIncomePart = false;
        }
    }

    file.close();
}

// 方案1：计算每月预扣纳税的个税
double calculateMonthlyTax(double monthlyTaxableIncome)
{
    for (const auto &rate : monthlyTaxRates)
    {
        if (monthlyTaxableIncome <= rate.upperLimit)
        {
            return monthlyTaxableIncome * rate.rate - rate.quickDeduction;
        }
    }
    return 0;
}

// 方案2：累计预扣预缴税法
double calculateCumulativeTax(double cumulativeTaxableIncome, double cumulativeTaxPaid)
{
    double tax = 0;

    // 按累计应纳税所得额分段查找适用税率和速算扣除数
    for (const auto &rate : cumulativeTaxRates)
    {
        if (cumulativeTaxableIncome <= rate.upperLimit)
        {
            tax = cumulativeTaxableIncome * rate.rate - rate.quickDeduction;
            break;
        }
    }

    return tax - cumulativeTaxPaid;
}

// 主函数
int main()
{
    double cumulativeIncome = 0;     // 累计收入
    double cumulativeDeductions = 0; // 累计扣除
    double cumulativeTaxPaid = 0;    // 累计已缴税款

    while (true)
    {
        int choice;
        cout << "请选择纳税计算方案（1：每月预扣法，2：累计预扣法，0：退出程序）: ";
        cin >> choice;

        if (choice == 0)
        {
            break; // 退出程序
        }

        if (choice == 1)
        {
            int month;
            cout << "请输入要计算的月份（1-12）: ";
            cin >> month;

            if (month < 1 || month > 12)
            {
                cout << "无效的月份，请输入1到12之间的数字。" << endl;
                continue;
            }

            string fileName;
            cout << "请输入第" << month << "个月的工资明细文件路径: ";
            cin >> fileName;

            double monthlyIncome = 0;
            double monthlyDeductions = 0;
            readMonthlyIncome(fileName, monthlyIncome, monthlyDeductions);

            // 月度应纳税所得额
            double monthlyTaxableIncome = monthlyIncome - monthlyDeductions - 5000;

            double tax = 0;
            if (monthlyTaxableIncome > 0)
            {
                tax = calculateMonthlyTax(monthlyTaxableIncome);
            }

            // 计算实发工资
            double trueIncome = monthlyIncome - monthlyDeductions - tax;

            // 输出当前月份工资明细
            cout << "第" << month << "月的工资明细:" << endl;
            cout << "应纳税额: " << fixed << setprecision(2) << tax << endl;
            cout << "实发工资: " << trueIncome << endl;
            cout << "--------------------------" << endl;
        }
        else if (choice == 2)
        {
            for (int month = 1; month <= 12; ++month)
            {
                string fileName;
                cout << "请输入第" << month << "个月的工资明细文件路径: ";
                cin >> fileName;

                double monthlyIncome = 0;
                double monthlyDeductions = 0;
                readMonthlyIncome(fileName, monthlyIncome, monthlyDeductions);

                // 更新累计收入和扣除
                cumulativeIncome += monthlyIncome;
                cumulativeDeductions += monthlyDeductions;

                // 累计应纳税所得额
                double cumulativeTaxableIncome = cumulativeIncome - cumulativeDeductions - 5000 * month;

                double tax = 0;
                if (cumulativeTaxableIncome > 0)
                {
                    tax = calculateCumulativeTax(cumulativeTaxableIncome, cumulativeTaxPaid);
                    cumulativeTaxPaid += tax;
                }

                // 计算实发工资
                double trueIncome = monthlyIncome - monthlyDeductions - tax;

                // 输出当前月份工资明细
                cout << "第" << month << "月的工资明细:" << endl;
                cout << "累计预扣预缴应纳税所得额: " << fixed << setprecision(2) << cumulativeTaxableIncome << endl; // 输出累计应纳税所得额
                cout << "应纳税额: " << fixed << setprecision(2) << tax << endl;
                cout << "实发工资: " << trueIncome << endl;
                cout << "--------------------------" << endl;
            }
        }
        else
        {
            cout << "无效的选择，请重新输入。" << endl;
        }
    }

    return 0;
}
