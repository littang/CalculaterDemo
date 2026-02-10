#include <iostream>
#include <cmath>
#include <iomanip>      // 用于格式化输出
#include <limits>       // 用于输入验证
#include <windows.h>    // Windows 系统编码设置
using namespace std;

// 函数声明
void displayMenu();
double getValidNumber(const string& prompt);
int getValidOperation();
void performOperation(int operation, double num1, double num2 = 0);
void clearInputBuffer();

int main()
{
    // 设置控制台编码为 UTF-8
    SetConsoleOutputCP(65001);
    // 或者使用：system("chcp 65001");
    
    cout << "======================================\n";
    cout << "         高级科学计算器             \n";
    cout << "======================================\n";
    
    while (true)
    {
        double num1, num2;
        int operation;
        
        // 显示菜单
        displayMenu();
        operation = getValidOperation();
        
        // 退出程序
        if (operation == 0) {
            cout << "\n感谢使用！再见！\n";
            cout << "======================================\n";
            break;
        }
        
        // 获取第一个数字
        num1 = getValidNumber("\n请输入第一个数字: ");
        
        // 根据操作类型决定是否需要第二个数字
        switch (operation)
        {
            case 5:  // 开平方根
            case 6:  // 绝对值
            case 7:  // 自然对数
            case 8:  // 常用对数
            case 9:  // 正弦
            case 10: // 余弦
            case 11: // 正切
                performOperation(operation, num1);
                break;
                
            default:  // 需要第二个数字的操作
                num2 = getValidNumber("请输入第二个数字: ");
                performOperation(operation, num1, num2);
                break;
        }
        
        cout << "--------------------------------------\n";
    }
    
    return 0;
}

// 显示菜单
void displayMenu() {
    cout << "\n========== 运算菜单 ==========\n";
    cout << "1:  加法 (+)         2:  减法 (-)\n";
    cout << "3:  乘法 (×)         4:  除法 (÷)\n";
    cout << "5:  开平方根 (√)     6:  绝对值 (|x|)\n";
    cout << "7:  自然对数 (ln)    8:  常用对数 (log₁₀)\n";
    cout << "9:  正弦 (sin)       10: 余弦 (cos)\n";
    cout << "11: 正切 (tan)       12: 幂运算 (x^y)\n";
    cout << "13: 取余 (%)         14: 最大值\n";
    cout << "15: 最小值           0:  退出程序\n";
    cout << "===============================\n";
    cout << "请输入操作编号 (0-15): ";
}

// 获取有效的数字输入
double getValidNumber(const string& prompt) {
    double num;
    
    while (true) {
        cout << prompt;
        cin >> num;
        
        if (cin.fail()) {
            cout << "⚠️  输入错误！请输入有效的数字: ";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return num;
        }
    }
}

// 获取有效的操作选择
int getValidOperation() {
    int op;
    
    while (true) {
        if (!(cin >> op)) {
            cout << "⚠️  请输入有效的数字 (0-15): ";
            clearInputBuffer();
            continue;
        }
        
        clearInputBuffer();
        
        if (op >= 0 && op <= 15) {
            return op;
        } else {
            cout << "⚠️  请输入 0-15 之间的数字: ";
        }
    }
}

// 清空输入缓冲区
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// 执行运算操作
void performOperation(int operation, double num1, double num2) {
    // 设置输出格式：固定小数，保留6位
    cout << fixed << setprecision(6);
    
    cout << "\n🔄 计算: ";
    
    switch (operation)
    {
        // 基本运算
        case 1:  // 加法
            cout << num1 << " + " << num2 << " = " << num1 + num2;
            break;
            
        case 2:  // 减法
            cout << num1 << " - " << num2 << " = " << num1 - num2;
            break;
            
        case 3:  // 乘法
            cout << num1 << " × " << num2 << " = " << num1 * num2;
            break;
            
        case 4:  // 除法
            if (num2 == 0) {
                cout << "❌ 错误：除数不能为零！";
            } else {
                cout << num1 << " ÷ " << num2 << " = " << num1 / num2;
            }
            break;
            
        case 5:  // 开平方根
            if (num1 < 0) {
                cout << "❌ 错误：不能对负数开平方根！";
            } else {
                cout << "√" << num1 << " = " << sqrt(num1);
            }
            break;
            
        case 6:  // 绝对值
            cout << "|" << num1 << "| = " << fabs(num1);
            break;
            
        // 对数运算
        case 7:  // 自然对数
            if (num1 <= 0) {
                cout << "❌ 错误：ln(x) 中 x 必须大于0！";
            } else {
                cout << "ln(" << num1 << ") = " << log(num1);
            }
            break;
            
        case 8:  // 常用对数
            if (num1 <= 0) {
                cout << "❌ 错误：log₁₀(x) 中 x 必须大于0！";
            } else {
                cout << "log₁₀(" << num1 << ") = " << log10(num1);
            }
            break;
            
        // 三角函数（角度制）
        case 9:  // 正弦
            {
                double radians = num1 * M_PI / 180.0;
                cout << "sin(" << num1 << "°) = " << sin(radians);
            }
            break;
            
        case 10: // 余弦
            {
                double radians = num1 * M_PI / 180.0;
                cout << "cos(" << num1 << "°) = " << cos(radians);
            }
            break;
            
        case 11: // 正切
            {
                double radians = num1 * M_PI / 180.0;
                double tan_val = tan(radians);
                
                // 检查是否为无穷大（接近90°的奇数倍）
                if (fabs(cos(radians)) < 1e-10) {
                    cout << "tan(" << num1 << "°) = 无穷大";
                } else {
                    cout << "tan(" << num1 << "°) = " << tan_val;
                }
            }
            break;
            
        case 12: // 幂运算（重点）
            cout << num1 << " ^ " << num2 << " = " << pow(num1, num2);
            break;
            
        case 13: // 取余（针对整数）
            if (static_cast<int>(num2) == 0) {
                cout << "❌ 错误：取余运算的除数不能为零！";
            } else {
                cout << static_cast<int>(num1) << " % " 
                     << static_cast<int>(num2) << " = " 
                     << static_cast<int>(num1) % static_cast<int>(num2);
            }
            break;
            
        case 14: // 最大值
            cout << "max(" << num1 << ", " << num2 << ") = " 
                 << (num1 > num2 ? num1 : num2);
            break;
            
        case 15: // 最小值
            cout << "min(" << num1 << ", " << num2 << ") = " 
                 << (num1 < num2 ? num1 : num2);
            break;
            
        default:
            cout << "❌ 错误：无效的操作！";
            break;
    }
    
    cout << endl;
    
    // 恢复默认输出格式
    cout.unsetf(ios_base::floatfield);
    cout.precision(6);
}