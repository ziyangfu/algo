#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

class Calculator {
private:
    stack<double> numbers;     // 存储操作数
    stack<char> operators;     // 存储运算符
    
    // 判断运算符优先级
    int precedence(char op) {
        if(op == '+' || op == '-') return 1;
        if(op == '*' || op == '/') return 2;
        return 0;
    }
    
    // 执行一次计算
    double applyOp(double a, double b, char op) {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if(b == 0) throw runtime_error("Division by zero");
                return a / b;
        }
        return 0;
    }
    
    // 处理栈顶运算
    void processTop() {
        char op = operators.top(); operators.pop();
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        numbers.push(applyOp(a, b, op));
    }
    
public:
    double evaluate(string expression) {
        for(int i = 0; i < expression.length(); i++) {
            // 跳过空格
            if(expression[i] == ' ') continue;
            
            // 处理数字（包括小数）
            if(isdigit(expression[i]) || expression[i] == '.') {
                string numStr = "";
                while(i < expression.length() && 
                      (isdigit(expression[i]) || expression[i] == '.')) {
                    numStr += expression[i++];
                }
                i--; // 回退一位
                numbers.push(stod(numStr));
            }
            // 处理左括号
            else if(expression[i] == '(') {
                operators.push(expression[i]);
            }
            // 处理右括号
            else if(expression[i] == ')') {
                while(!operators.empty() && operators.top() != '(') {
                    processTop();
                }
                if(!operators.empty()) operators.pop(); // 移除左括号
            }
            // 处理运算符
            else {
                while(!operators.empty() && operators.top() != '(' &&
                      precedence(operators.top()) >= precedence(expression[i])) {
                    processTop();
                }
                operators.push(expression[i]);
            }
        }
        
        // 处理剩余运算符
        while(!operators.empty()) {
            processTop();
        }
        
        return numbers.top();
    }
};

// 使用示例
int main() {
    Calculator calc;
    string expr = "(3 + 5) * 2 - 8";
    cout << "Result: " << calc.evaluate(expr) << endl; // 输出: -27
    return 0;
}
