#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

struct Ans{//�s����ƫ��A�P���ƥH�W�Ʀr�ξ� 
    bool isnumber;  
    float number;     
    char symbol;    
};
vector<Ans> user2;
vector<Ans> user;
int precedence(char op) {
    switch(op) {
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
  		case '%': return 3;
  		case '^': return 4;
  		case '(':return 1;
  		case ')':return 1;
        default: return 0;
    }
}
void change_type(string s){
	vector<char> a;
	char t;
	float j=0;
	int p=0;
	bool c=true,inn=false;
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());//�N�ťեh��
	for(int i=0;i<=s.size();i++){
		if(s[i]==' ')
			continue;
		else if(s[i]=='1'||s[i]=='2'||s[i]=='3'||s[i]=='4'||s[i]=='5'||s[i]=='6'||s[i]=='7'||s[i]=='8'||s[i]=='9'||s[i]=='0'||s[i]=='.'){//�N�Ʀr��ia�̡A�H�K�B�z���ƥH�W�r�� 
	   		if(!c)
	   			p--;
  			if(s[i]=='.'){ //�J��p�ƶ}�lp�|��-1�B-2 
    			c=false;
    			continue;
   			} 
   			a.push_back(s[i]);
  		}
		else{
			if(s[i]=='-'&&precedence(s[i-1])>0){//�P�_�O�_���t�� 
				inn=true;
				continue;
			} 
	   		while(!a.empty()){//�J��B�⤸�Na���X��Juser�� 
	    	j+=(a[a.size()-1]-48)*(float)pow(10,p);//���Wp�H�D���G 
	    	p++;
	    	a.pop_back();
	   		}
	   		if(inn){
	   			j=j*(-1);
	   			inn=false;
			}
	   		if(j!=0)
	    		user.push_back({1,j,'0'});//�⵲�G���J���� 
	   		j=0;
	   		p=0;
	   		c=true;
	   		user.push_back({0,0,s[i]});//�N�B�⤸��Juser�� 
	  	}
 	}	
}
//Lab6�����e(���|) 
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


// �N���Ǫ�F�� (infix) �ഫ����Ǫ�F�� (postfix)
void InfixToPostfix() {
    Stack s;     
    for (int i = 0; i<user.size();i++) {
        if(user[i].isnumber)
    		user2.push_back({1, user[i].number, '0'});
        else if (user[i].symbol== '(') 
            s.push(user[i].symbol);//�O���A�����i���| 
        else if (user[i].symbol == ')') {
            while (s.peek() != '(') 
                user2.push_back({0, 0, s.pop()});
            s.pop();//���A���R�� 
        }
        else{
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(user[i].symbol))
                user2.push_back({0, 0, s.pop()});
            s.push(user[i].symbol);//��쥻�Ÿ����i�h 
        }
    }
    while (!s.isEmpty())
         user2.push_back({0, 0, s.pop()});
}//Lab6���F�赲�� 
float judge(float a, float b, char sy) {//�Ψӭp�⪺�{�� 
    switch (sy) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
    	case '/': return a/b; 
  		case '%': return fmod(a, b);//�ΨӨ�float���l�Ƶ{�� 
  		case '^': return pow(a,b);
    }
}

float Ans_calculate(){//�N���׭p�� 
	vector<float> s;//�N�Ʀr���F���|�i�h 
	for(int i=0;i<user2.size();i++){
		if(user2[i].isnumber)
			s.push_back(user2[i].number);
		else{//�p�G�J��Ÿ��N�|pop�X�ӭp�⧹�A��^�h 
			float j=s.back();
			s.pop_back();
			float t=s.back();
			s.pop_back();
			s.push_back(judge(t,j,user2[i].symbol));//�I�s�p��{�� 
		}
	}
	return s[0];
}
int main(int argc, char** argv) {
	string s={0};
	cout<<"�п�J�B�⦡�G";
	getline(cin, s);
	change_type(s);//�N��J�Ȧs�J Ans
	InfixToPostfix(); //�ন��� 
	float j=Ans_calculate();//�N���G�p��X�� 
	if(fmod(j, 1)==0)
		cout<<fixed << setprecision(1) << j;//���ƮɥΨ����.0�� 
	else
		cout<<j;
	return 0;
}
