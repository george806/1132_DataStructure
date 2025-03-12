#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
	vector<int> exp;//存取係數與常數 
	vector<int> nums;//存取次方項 
	int k=0,count=0;
	string o="",s="";
	getline(cin,s);//取得使用者輸入值 
	for(int i=0;i<s.size();i++){
		if(s[i]!=' ')
			o+=s[i];
	}//將空白值去除掉 
	s=o;//把字串還回去 
	o="";
	for(int i=0;i<s.size();i++){
		if(s[i]=='x'){//以x為目標 
			for(int j=i+1;j<s.size();j++){//將次方項數字提取出來 
				if(s[j]=='^')//定位他下一位是否為次方項 
					j++;
				if(s[j]=='+')//如果不是代表一次方 
					break;
				else
					o+=s[j];//將字元儲存 
			}
			reverse(o.begin(),o.end());//整個字串反轉 
			for(int t=0;t<o.size();t++){
				k+=(o[t]-48)*pow(10,t);//將字串改成數字 
			}
			if(s[i+1]=='+')//若遇到x的下一位是+號時 
				exp.push_back(1);//則代表一次方 
			exp.push_back(k);//將結果推進動態陣列 
			k=0;
			o="";
			for(int j=i;j>0;j--){//將係數項提取出來 
				if(s[j-1]=='+'||j==0)//確認是否為第一位數或前一位為+號，以方便離開 
					break;
				else
					o+=s[j-1];//將字元儲存
			}
			for(int t=0;t<o.size();t++){//將字串改成數字
				k+=(o[t]-48)*pow(10,t); 
			}
			nums.push_back(k);//將結果推進動態陣列 
			k=0;
			o="";
			count++;//確認總共有幾個項數 
		}
		if(i==s.size()-1){//確認末項 
			while(s[i]!='+'){
				o+=s[i];//將字元儲存 直到+號 
				i--;
			}
			for(int t=0;t<o.size();t++){//將字串改成數字
				k+=(o[t]-48)*pow(10,t);
			}
			nums.push_back(k);//代表末項的係數值 
			exp.push_back(0);//代表X的0次方 
			break;
		}
	}
	if(s[s.size()-1]=='x')
		count--;//若末項非為常數項就-1(預設為常數項) 
	for(int i=0;i<count+1;i++)
		cout<<nums[i]<<'^'<<exp[i]<<' ';//輸出結果 
	return 0;
}
