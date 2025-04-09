#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;  // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top; // 指向堆疊頂端
public:
    Stack() {top = nullptr; } // 初始化堆疊

    // Push 操作：將元素放入堆疊
    void push(char ch) {
        Node* newNode = new Node(); // 建立新節點
        newNode->data = ch;         // 儲存資料
        newNode->next = top;        // 新節點指向原本的頂端
        top = newNode;              // 更新頂端為新節點
    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
        if (top == nullptr) {  // 如果堆疊是空的
            cout << "堆疊為空，無法取出元素。\n";
            return 0;  // 結束這次 pop()
        }
        char poppedValue = top->data;  // 取得頂端元素的值
        Node* temp = top;              // 用 temp 暫存目前頂端節點
        top = top->next;               // 更新頂端為下一個節點
        delete temp;                   // 釋放記憶體，刪除原頂端節點
        return poppedValue;
    }

    // Peek 操作：取得頂端元素但不移除
    char peek() {
        return top->data;//回傳頂端資料    
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
    	if(top==nullptr)
        	return true;  
        return false;
    }
};

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
    switch(op) {
        case '+':
        	return 1;
        case '-': 
        	return 1;
        case '*':
        	return 2;
        case '/': 
			return 2;
        default: 
			return 0;
    }
}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
    Stack s;            
    int j = 0;          

    for (int i = 0; infix[i] != '\0'; i++) {
        char t = infix[i];//把讀到的存下來 
        if (t != '+' && t != '-' && t != '*' && t != '/'&& t!='('&&t!=')') {
            postfix[j++] = t;//是數字就輸出 
        }
       if (t == '(') {
            s.push(t);//是左括號壓進堆疊 
        }
        if (t == ')') {
            while (s.peek() != '(') {
                postfix[j++] = s.pop();//括號找左括號，遇到的值輸出 
            }
            s.pop();//左括號刪掉 
        }
        if (t == '+' || t == '-' || t == '*' || t == '/') {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(t)) {
                postfix[j++] = s.pop();//看符號優先級大小，遇到大的小的會先出去 
            }
            s.push(t);//把原本符號推進去 
        }
    }
    while (!s.isEmpty()) {
        postfix[j++] = s.pop();//最後堆疊裡的符號一併輸出 
    }
}

int main() {
    char infix[100]={0}, postfix[100]={0};
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式

    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式

    return 0;
}

