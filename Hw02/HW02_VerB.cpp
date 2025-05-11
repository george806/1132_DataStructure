#include <cctype>
#include <cmath>
#include <cstring>
#include <iomanip>    // 讓我們可以使用setprecision來設定小數點位數的設定
#include <iostream>
using namespace std;

// char type的node 給infixtopostfix function 用
// 定義 Stack 的節點結構
template <typename T>
struct Node {
    T data;        // 存儲字符 (運算子或括號)
    Node* next;    // 指向下一個節點
};

// 使用 linked list 實作 Stack
template <typename T>
class Stack {
private:
    Node<T>* top;    // 指向堆疊頂端
public:
    Stack() : top(nullptr)
    {
    }

    // Push 操作：將元素放入堆疊
    void push(T val)
    {
        Node<T>* newNode = new Node<T>();    // 建立新節點
        newNode->data = val;                 // 儲存資料
        newNode->next = top;                 // 新節點指向原本的頂端
        top = newNode;                       // 更新頂端為新節點
        // cout << ch << " 已推入堆疊\n";
    }

    // Pop 操作：移除並回傳頂端元素
    T pop()
    {
        if (top == nullptr) {    // 如果堆疊是空的
            // cout << "堆疊為空，無法取出元素。\n";
            return T();    // 結束這次 pop()
        }

        T val = top->data;      // 取得頂端元素的值
        Node<T>* temp = top;    // 用 temp 暫存目前頂端節點
        top = top->next;        // 更新頂端為下一個節點
        delete temp;            // 釋放記憶體，刪除原頂端節點
        // cout << "已取出元素: " << poppedchar << endl;
        // cout << poppedchar;
        return val;
    }

    // Peek 操作：取得頂端元素但不移除
    T peek()
    {
        if (top == nullptr) {
            // cout << "堆疊為空，無法取出元素。\n";
            return -1;
        }

        return top->data;
    }

    // 判斷堆疊是否為空
    bool isEmpty()
    {
        if (top == nullptr) {    // 回傳空的狀況
            // cout << "堆疊為空，無法取出元素。\n";
            return true;
        }
        else {
            return false;
        }
    }
};

// 原本lab6是用isoperator來區分，但是HW02用是不是digitordot來判斷會更好，因為要判斷的operator更多了
bool isoperator(char op)    // 判斷是不是operator i.e. + - * / ( )
{
    if (op != '+' && op != '-' && op != '*' && op != '/' && op != '^' && op != '%' && op != '(') {
        return false;
    }
    return true;
}

bool isdigitordot(char op)
{
    return (isdigit(op) || (op == '.'));
}
// 判斷運算子(加減乘除) 的優先順序
// 在stack裡的優先順序，因為'('在stack內跟在括號外的優先順序不一樣，所以有instack的跟outstack的。
int instackprecedence(char op)    // 越小越優先
{
    switch (op) {
    case '(':
        return 8;
    case '+':
        return 3;
    case '-':
        return 3;
    case '*':
        return 2;
    case '/':
        return 2;
    case '^':
        return 1;
    default:
        return -1;
    }
}

// 在stack外的優先順序
int outstackprecedence(char op)    // 越小越優先
{
    switch (op) {
    case '(':
        return 0;
    case '+':
        return 3;
    case '-':
        return 3;
    case '*':
        return 2;
    case '/':
        return 2;
    case '^':
        return 1;
    default:
        return -1;
    }
}

bool isspace(char op)    // 用來略過空格的輸入
{
    return (op == ' ');
}

bool isnegative(char op)
{
    return (op == '-');
}
// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix)
{
    Stack<char> s;    // 因為處理的是字串，因此使用的Stack的type是char
    int i = 0;
    int count = 0;                  // 用來記錄postfix字串目前儲存到哪
    while (infix[i] != '\0') {      // 到字串尾才會結束
        if (isspace(infix[i])) {    // 忽略空格，直接跳過，直接用continue找下一個來判斷
            i++;
            continue;
        }

        // HW02版本的註解，假如是數字或是'.'的話，把此字元從infix字串複製到postfix字串
        // lab6的註解判斷吃到的char是哪類，總共有3類，第一種是不是operator的，第二種是')'，第三種是非')'的operator。
        // 負號的處理
        int j = i - 1;                           // 處理當下字元負號的判斷
        while (j >= 0 && isspace(infix[j])) {    // j會一直定位到index i前面一個非空白字元，這樣下面的負號判斷才不會有問題
            j--;                                 // 跳過前面的空格
        }
        // 因為一開始用的是[i - 1]，所以只有在10 /-8這樣的情況才會判斷成-8，
        // 假如是10 / -8這樣的輸入的話，這樣isoperator(infix[i - 1]) 會是false，所以會被判斷成10 / - 8這樣的輸入，負號跟8分開了。
        if (isdigitordot(infix[i]) || ((infix[i] == '-') && ((i == 0) || isoperator(infix[j])) && isdigitordot(infix[i + 1]))) {    // 第一種，不是operator的話，就直接存在postfix字串。
            if (infix[i] == '-') {
                postfix[count] = infix[i];    // 把'-'儲存進輸出
                i++;
                count++;
            }
            while (isdigitordot(infix[i])) {    // 會一直複製到不是數字或小數點
                postfix[count] = infix[i];
                i++;
                count++;
            }
            postfix[count] = ' ';    // 為了輸出能清楚分辨operand或operator，加入空格
            count++;
            continue;
        }
        else if (infix[i] == ')') {                      // 第二種，假如是右括號，要一直pop直到左括號。
            while (!s.isEmpty() && s.peek() != '(') {    // stack不是空的話，已經stack最上方的不是'('的話，會一直pop直到這兩個其中一個發生。
                postfix[count] = s.pop();
                count++;
                postfix[count] = ' ';
                count++;
            }
            s.pop();    // ************把'(' 丟掉 *****************
            // 因為')' 會把stack內，碰到'('之前的東西都pop到postfix裡，因此會剩'('在stack中的最上方，而這個'('是要和')'成對消失的。
        }
        // 第三種，剩下的operator只要判斷stack最上方的優先順序是不是小於等於準備要進stack的符號，假如是的話就要一直pop到stack空或是直到stack內的優先順序大於要進stack的符號。
        else {
            // while (!s.isEmpty() && instackprecedence(s.peek()) <= outstackprecedence(infix[i])) { // lab6版本
            // 下面是HW02版本
            // 這個修改是因為'^'是右結合，因此'^'只有在stack中的符號順位比stack外的符號還要小的時候pop出來，等於的話'^'不能pop出來，其他的符號跟lab6的狀況一樣。
            while ((!s.isEmpty()) && (instackprecedence(s.peek()) < outstackprecedence(infix[i]) || (instackprecedence(s.peek()) == outstackprecedence(infix[i]) && infix[i] != '^'))) {
                postfix[count] = s.pop();
                count++;
                postfix[count] = ' ';
                count++;
            }
            s.push(infix[i]);    // 當stack內的符號的優先順序終於比要進stack的符號低時或是stack空了，才把新的符號push到stack內
        }
        i++;                                                   // while index++
        cout << "目前的postfix輸出為: " << postfix << endl;    // 逐步地確認書出狀況。
    }
    // 把剩下的堆疊都 pop 出來，因為上面三種狀況並沒有一定會pop完stack才停止，第一種根本不會pop，第二種可能只會pop到'('為止，第三種可能只會pop到stack內的優先順序比stack外的還低時，
    while (!s.isEmpty() && infix[i] != '(') {
        postfix[count++] = s.pop();
        postfix[count] = ' ';
        count++;
    }
}

double PostfixEvaluation(const char* postfix)
{
    Stack<double> s;    //  因為要計算數值，所以使用的Stack的type是double
    int i = 0;
    int top = -1;                   // 紀錄stack儲存的狀況
    while (postfix[i] != '\0') {    // 重複執行到postfix字串結束
        double temp = 0;            // 用來儲存結果的變數
        if (postfix[i] == ' ') {    // 略過空格
            i++;
            continue;
        }
        if (isdigitordot(postfix[i]) || (postfix[i] == '-' && (i == 0 || postfix[i - 1] == ' ') && isdigitordot(postfix[i + 1]))) {    // 數字的話，直接加入floatstack中
            char number[100] = {0};                                                                                                    // 用來儲存此數字的字串
            int j = 0;                                                                                                                 // index
            if (postfix[i] == '-') {
                number[j] = postfix[i];
                i++;
                j++;
            }
            while (isdigitordot(postfix[i])) {    // 是數字或小數點就儲存number字串，一直儲存到不是為止
                number[j] = postfix[i];
                j++;
                i++;
            }
            number[j] = '\0';        // 設定字串結束
            s.push(stod(number));    // string to double 把數字字串轉成double，加入stack中
            top++;
            continue;    // 這邊做完就不需要最後面的i++了，因此使用continue直接開始下一次的loop
        }
        else {                                // operator的情況
            if (!isoperator(postfix[i])) {    // 判斷是否為valid的6種operator '+' '-' '*' '/' '^' '%'
                return NAN;                   // 回傳not a number(NAN) 最後就會輸出nan，代表輸入有誤
            }
            // int operator0 = whatoperator(postfix[i]);    // 判別是哪個operator
            double operand2 = s.pop();    // 第一個pop出來的operand是擺在opeartor後面的
            top--;
            double operand1 = s.pop();    // 第二個pop出來的是擺在operator前面的
            top--;
            switch (postfix[i]) {    // 各operator的實際運算操作
            case '+':                // + operation
                temp = operand1 + operand2;
                break;
            case '-':    // - operation
                temp = operand1 - operand2;
                break;
            case '*':    // * operation
                temp = operand1 * operand2;
                break;
            case '/':    // / operation
                temp = operand1 / operand2;
                break;
            case '^':    // ^ operation
                temp = pow(operand1, operand2);
                break;
            case '%':    // % operation
                temp = fmod(operand1, operand2);
                break;
            }
            s.push(temp);    // 運算後把結果存進floatstack中
            top++;           // 因為存入了這次的結果，top必須++
        }
        i++;    // 更新index
    }
    return s.pop();    // 把最後的結果回傳
}

int main()
{
    char infix[100], postfix[100] = {0};    // 宣告輸出輸入string，postfix要初始化=0比較好，不然可能會出現一直garbage value
    double ans = 0;
    cout << "Enter an Infix expression: ";
    cin.getline(infix, 100);    // 讀取包含空格，並設定最多100個char
    // cin >> infix;    // 輸入中序表達式

    InfixToPostfix(infix, postfix);                           // 中序轉換為後序表達式
    cout << "最終Postfix expression: " << postfix << endl;    // 輸出後序表達式

    // 設定輸出要到小數點後第6位
    ans = PostfixEvaluation(postfix);    // 利用後序表達式來完成計算，並把結果存進ans中
    if (isnan(ans)) {                    // 用來判斷輸入是否有誤
        cout << "輸入的計算式有誤，請重新輸入！" << endl;
    }
    else {
        cout << "Answer is: " << fixed << setprecision(1) << ans << endl;    // 設定輸出要到小數點後第10位
    }

    return 0;
}