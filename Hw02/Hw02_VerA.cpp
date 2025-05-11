#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

struct Ans{//存取資料型態與兩位數以上數字統整 
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
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());//將空白去除
	for(int i=0;i<=s.size();i++){
		if(s[i]==' ')
			continue;
		else if(s[i]=='1'||s[i]=='2'||s[i]=='3'||s[i]=='4'||s[i]=='5'||s[i]=='6'||s[i]=='7'||s[i]=='8'||s[i]=='9'||s[i]=='0'||s[i]=='.'){//將數字放進a裡，以便處理兩位數以上字元 
	   		if(!c)
	   			p--;
  			if(s[i]=='.'){ //遇到小數開始p會變-1、-2 
    			c=false;
    			continue;
   			} 
   			a.push_back(s[i]);
  		}
		else{
			if(s[i]=='-'&&precedence(s[i-1])>0){//判斷是否為負號 
				inn=true;
				continue;
			} 
	   		while(!a.empty()){//遇到運算元將a取出放入user內 
	    	j+=(a[a.size()-1]-48)*(float)pow(10,p);//乘上p以求結果 
	    	p++;
	    	a.pop_back();
	   		}
	   		if(inn){
	   			j=j*(-1);
	   			inn=false;
			}
	   		if(j!=0)
	    		user.push_back({1,j,'0'});//把結果推入內部 
	   		j=0;
	   		p=0;
	   		c=true;
	   		user.push_back({0,0,s[i]});//將運算元放入user內 
	  	}
 	}	
}
//Lab6的內容(堆疊) 
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


// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix() {
    Stack s;     
    for (int i = 0; i<user.size();i++) {
        if(user[i].isnumber)
    		user2.push_back({1, user[i].number, '0'});
        else if (user[i].symbol== '(') 
            s.push(user[i].symbol);//是左括號壓進堆疊 
        else if (user[i].symbol == ')') {
            while (s.peek() != '(') 
                user2.push_back({0, 0, s.pop()});
            s.pop();//左括號刪掉 
        }
        else{
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(user[i].symbol))
                user2.push_back({0, 0, s.pop()});
            s.push(user[i].symbol);//把原本符號推進去 
        }
    }
    while (!s.isEmpty())
         user2.push_back({0, 0, s.pop()});
}//Lab6的東西結束 
float judge(float a, float b, char sy) {//用來計算的程式 
    switch (sy) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
    	case '/': return a/b; 
  		case '%': return fmod(a, b);//用來取float的餘數程式 
  		case '^': return pow(a,b);
    }
}

float Ans_calculate(){//將答案計算 
	vector<float> s;//將數字的東西疊進去 
	for(int i=0;i<user2.size();i++){
		if(user2[i].isnumber)
			s.push_back(user2[i].number);
		else{//如果遇到符號就會pop出來計算完再堆回去 
			float j=s.back();
			s.pop_back();
			float t=s.back();
			s.pop_back();
			s.push_back(judge(t,j,user2[i].symbol));//呼叫計算程式 
		}
	}
	return s[0];
}
int main(int argc, char** argv) {
	string s={0};
	cout<<"請輸入運算式：";
	getline(cin, s);
	change_type(s);//將輸入值存入 Ans
	InfixToPostfix(); //轉成後序 
	float j=Ans_calculate();//將結果計算出來 
	if(fmod(j, 1)==0)
		cout<<fixed << setprecision(1) << j;//當整數時用來顯示.0的 
	else
		cout<<j;
	return 0;
}
