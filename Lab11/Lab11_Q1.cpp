#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <cctype>
using namespace std;

// �w�q�@�� MaxHeap ���O
class store{
	public:
		string name;//�W�r 
		int date;//���Ĥ�� 
		int pbc;//�H��(public) 
	
};
bool isNumber(const string& s) {
    if (s.empty()) return false; //�Ŧr�ꤣ�O�Ʀr
    for (char c : s) {//�d�ݾ�Ӧr�� 
        if (!isdigit(c))//�P�_�O�_���Ʀr 
			return false;
    }
    return true;
}
void bubbleSort(vector<store>& shop,int a) {
    for(int i=0;i<a-1;i++) {
        for(int j=0;j<a-1;j++){
        	if(shop[j].date>=shop[j+1].date){//�ݤ���O�_�۵��Χ�� 
        		if(shop[j].date==shop[j+1].date&&shop[j].pbc>shop[j+1].pbc)//����۵�����H�� 
        			continue;//�Y�H��󰪫h���L�����洫 
        		swap(shop[j],shop[j+1]);//�i��洫 
			}
		}
    }
}
int main() {
    int a[3];
    ifstream infile("input3.txt");//�ޤJ�ɮ� 
    string s,name;
    getline(infile,s);
    a[0]=stoi(s);//�N��J�X����Ʀs�U�� 
    vector<store> shop(a[0]);//�s���ڪ���X 
   	for(int i=0;i<a[0];i++){//�N���G�ɤJ��shop�� 
   		getline(infile,name,' ');
   		getline(infile,s,' ');
   		if(!isNumber(s)){
   			name+=" "+s;
			getline(infile,s,' ');//�Ω���o����W�r�t�@�Ӫťժ��W�r 
		}
   		a[1]=stoi(s);//�s�J���Ĥ�� 
   		getline(infile,s); 
   		a[2]=stoi(s);//�s�J�H��� 
   		shop[i].name=name;
   		shop[i].date=a[1];
   		shop[i].pbc=a[2];
	}
	bubbleSort(shop,a[0]);//�i��Ƨ� 
	cout<<"�ӫ~�ƧǡG"<<endl; 
	for(int i=0;i<a[0];i++){
		cout<<shop[i].name<<endl;//��X���G 
	}
	infile.close();//�����ɮ� 
    return 0;
}
