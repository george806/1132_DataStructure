#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <cctype>
using namespace std;

// 定義一個 MaxHeap 類別
class store{
	public:
		string name;//名字 
		int date;//有效日期 
		int pbc;//人氣(public) 
	
};
bool isNumber(const string& s) {
    if (s.empty()) return false; //空字串不是數字
    for (char c : s) {//查看整個字串 
        if (!isdigit(c))//判斷是否為數字 
			return false;
    }
    return true;
}
void bubbleSort(vector<store>& shop,int a) {
    for(int i=0;i<a-1;i++) {
        for(int j=0;j<a-1;j++){
        	if(shop[j].date>=shop[j+1].date){//看日期是否相等或更近 
        		if(shop[j].date==shop[j+1].date&&shop[j].pbc>shop[j+1].pbc)//日期相等比較人氣 
        			continue;//若人氣更高則跳過此次交換 
        		swap(shop[j],shop[j+1]);//進行交換 
			}
		}
    }
}
int main() {
    int a[3];
    ifstream infile("input3.txt");//引入檔案 
    string s,name;
    getline(infile,s);
    a[0]=stoi(s);//將輸入幾筆資料存下來 
    vector<store> shop(a[0]);//存取我的輸出 
   	for(int i=0;i<a[0];i++){//將結果導入至shop內 
   		getline(infile,name,' ');
   		getline(infile,s,' ');
   		if(!isNumber(s)){
   			name+=" "+s;
			getline(infile,s,' ');//用於取得完整名字含一個空白的名字 
		}
   		a[1]=stoi(s);//存入有效日期 
   		getline(infile,s); 
   		a[2]=stoi(s);//存入人氣度 
   		shop[i].name=name;
   		shop[i].date=a[1];
   		shop[i].pbc=a[2];
	}
	bubbleSort(shop,a[0]);//進行排序 
	cout<<"商品排序："<<endl; 
	for(int i=0;i<a[0];i++){
		cout<<shop[i].name<<endl;//輸出結果 
	}
	infile.close();//關閉檔案 
    return 0;
}
