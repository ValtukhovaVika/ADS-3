// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char pr) {
    switch (pr) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default:return -1;
    }
}
std::string infx2pstfx(std::string inf) {
    char top = 0;
    TStack<char> stack1;
    std::string str;
    for (int i = 0; i < inf.length(); i++) {
        int prior;
        prior = priority(inf[i]);
        if (prior > -1) {
            if ((prior == 0 || prior > priority(top) || 
                 stack1.isEmpty()) && inf[i] != ')') {
            if (stack1.isEmpty())
                top = inf[i];
            stack1.push(inf[i]); }
            else if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    str.push_back(stack1.get());
                    str.push_back(' ');
                    stack1.pop();
                }
                stack1.pop();
                if (stack1.isEmpty())
                    top = 0;
            }
            else {
                while (!stack1.isEmpty() && priority(stack1.get()) >= prior) {
                    str.push_back(stack1.get());
                    str.push_back(' ');
                    stack1.pop();
                }
                if (stack1.isEmpty())
                    top = inf[i];
                stack1.push(inf[i]);
            }
        }
        else {
            str.push_back(inf[i]);
            str.push_back(' ');
        }
    }
    while (!stack1.isEmpty()) {
        str.push_back(stack1.get());
        str.push_back(' ');
        stack1.pop();
    }
    str.erase(str.end() - 1, str.end());
    return str;
}
int calculating(char operate, int num1, int num2) {
    switch (operate) {
    case '+':return num1 + num2;
        break;
    case '-':return num1 - num2;
        break;
    case '*':return num1 * num2;
        break;
    case '/':return num1 / num2;
        break;
    }
}

int eval(std::string pst) {
    TStack<int> stack2;
    int result = 0, i = 0;
    char x = pst[i];
    while (x) {
        if (x >= '0' && x <= '9') {
            int insertInt = 0;
            int dec = 1;
            while (x != ' ') {
                insertInt += (x - 48) * dec;
                dec *= 10;
                x = pst[++i];
            }
            stack2.push(insertInt);
        } else {
            char operate = x;
            i++;
            int num2 = stack2.get();
            stack2.pop();
            int num1 = stack2.get();
            stack2.pop();
            int result = calculating(operate, num1, num2);
            stack2.push(result);
        }
        if (i < pst.size())
            x = pst[++i];
        else 
            x = 0;
    }
    result = stack2.get();
    stack2.pop();
    return result;
}
