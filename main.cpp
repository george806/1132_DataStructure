#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// �w�q Stack ���`�I���c
struct Node {
    char data;  // �s�x�r�� (�B��l�άA��)
    Node* next; // ���V�U�@�Ӹ`�I
};

// �ϥ� linked list ��@ Stack
class Stack {
private:
    Node* top; // ���V���|����
public:
    Stack() {top = nullptr; } // ��l�ư��|

    // Push �ާ@�G�N������J���|
    void push(char ch) {
        Node* newNode = new Node(); // �إ߷s�`�I
        newNode->data = ch;         // �x�s���
        newNode->next = top;        // �s�`�I���V�쥻������
        top = newNode;              // ��s���ݬ��s�`�I
    }

    // Pop �ާ@�G�����æ^�ǳ��ݤ���
    char pop() {
        if (top == nullptr) {  // �p�G���|�O�Ū�
            cout << "���|���šA�L�k���X�����C\n";
            return 0;  // �����o�� pop()
        }
        char poppedValue = top->data;  // ���o���ݤ�������
        Node* temp = top;              // �� temp �Ȧs�ثe���ݸ`�I
        top = top->next;               // ��s���ݬ��U�@�Ӹ`�I
        delete temp;                   // ����O����A�R���쳻�ݸ`�I
        return poppedValue;
    }

    // Peek �ާ@�G���o���ݤ�����������
    char peek() {
        return top->data;//�^�ǳ��ݸ��    
    }

    // �P�_���|�O�_����
    bool isEmpty() {
    	if(top==nullptr)
        	return true;  
        return false;
    }
};

// �P�_�B��l(�[���) ���u������
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

// �N���Ǫ�F�� (infix) �ഫ����Ǫ�F�� (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
    Stack s;            
    int j = 0;          

    for (int i = 0; infix[i] != '\0'; i++) {
        char t = infix[i];//��Ū�쪺�s�U�� 
        if (t != '+' && t != '-' && t != '*' && t != '/'&& t!='('&&t!=')') {
            postfix[j++] = t;//�O�Ʀr�N��X 
        }
       if (t == '(') {
            s.push(t);//�O���A�����i���| 
        }
        if (t == ')') {
            while (s.peek() != '(') {
                postfix[j++] = s.pop();//�A���䥪�A���A�J�쪺�ȿ�X 
            }
            s.pop();//���A���R�� 
        }
        if (t == '+' || t == '-' || t == '*' || t == '/') {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(t)) {
                postfix[j++] = s.pop();//�ݲŸ��u���Ťj�p�A�J��j���p���|���X�h 
            }
            s.push(t);//��쥻�Ÿ����i�h 
        }
    }
    while (!s.isEmpty()) {
        postfix[j++] = s.pop();//�̫���|�̪��Ÿ��@�ֿ�X 
    }
}

int main() {
    char infix[100]={0}, postfix[100]={0};
    cout << "Enter an Infix expression: ";
    cin >> infix; // ��J���Ǫ�F��

    InfixToPostfix(infix, postfix); // �ഫ����Ǫ�F��
    cout << "Postfix expression: " << postfix << endl; // ��X��Ǫ�F��

    return 0;
}

