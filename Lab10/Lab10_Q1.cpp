#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
const int EMPTY = NULL; // �� NULL �N��S���`�I
class TreeNode {
public:
    int value;// �`�I��
    TreeNode* left;// ���l�`�I
    TreeNode* right;// �k�l�`�I

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//��l�Ƹ`�I
};

class BinaryTree {
public:
    TreeNode* root;// ��ڸ`�I

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) {// �إ߾�
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q;//�إ�queue�x�s�ݳB�z���`�I����
        root = new TreeNode(arr[0]);// �إ߮ڸ`�I (�}�C�Ĥ@�Ӥ���)
        q.push(&root);// �N�ڸ`�I�����Х[�Jqueue

        size_t i = 1;// �}�C����
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();// ���Xqueue���Ĥ@�Ӹ`�I����
            q.pop();// �N�Ӹ`�I�qqueue���R��

            // ���l�`�I
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]);// �K�[���l�`�I
                    q.push(&((*nodePtr)->left));// �N���l�`�I�����Х[�Jqueue
                }
                i++;
            }
            // �k�l�`�I
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]);// �K�[�k�l�`�I
                    q.push(&((*nodePtr)->right));// �N�k�l�`�I�����Х[�Jqueue
                }
                i++;
            }
        }
        return root;
    }

   
    void Breadth_first_search(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//�إ�queue�x�s�ݳB�z���`�I����
        q.push(root); // �N�ڸ`�I�����Х[�Jqueue

        while (!q.empty()) {
            TreeNode* current = q.front();// ���Xqueue���Ĥ@�Ӹ`�I����
            q.pop();// �N�Ӹ`�I�qqueue���R��
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // �N���l�`�I�����Х[�Jqueue
            if (current->right) q.push(current->right);// �N���l�`�I�����Х[�Jqueue
        }
    }
    int Breadth_first_SumLevel(TreeNode* root,int i) {
        if (root == nullptr) return 0;
        queue<TreeNode*> q;//�إ�queue�x�s�ݳB�z���`�I����
        q.push(root); // �N�ڸ`�I�����Х[�Jqueue
		int j=0,sum=0;
        while (!q.empty()) {
            TreeNode* current = q.front();// ���Xqueue���Ĥ@�Ӹ`�I����
            if(j >= pow(2, i) - 1 && j < pow(2, i + 1) - 1)//�N�U�h�[�b�@�_�A�p�G�ó]�w�W���P�U�� 
        		sum+=current->value;//sum���[�`�� 
            q.pop();// �N�Ӹ`�I�qqueue���R��
            if (current->left) q.push(current->left);  // �N���l�`�I�����Х[�Jqueue
            if (current->right) q.push(current->right);// �N���l�`�I�����Х[�Jqueue
            j++;
        }
        return sum;
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);
	int i=4;
    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;
	cout<<"�п�J�n�d�ߪ��h��(�q0�}�l)�G";
	cin>>i;
	int a=i;
	i=tree.Breadth_first_SumLevel(tree.root,i);//��Ӽh�Ƭۥ[ 
	if(a>3)
		cout<<"�W�L��"<<endl;
	else
		cout<<"��"<<a<<"�h���`�M���G"<<i<<endl;
    system("pause");
    return 0;
}
