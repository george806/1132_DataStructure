#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int maxR=0,maxL=0;
bool swi=true;
// �𪺸`�I
class TreeNode {
public:
    int value;             // �`�I����
    TreeNode* left;        // ���l�`�I
    TreeNode* right;       // �k�l�`�I

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // ��l�Ƹ`�I
};

// �𵲺c
class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {} // ��l�ƾ�

    // �ΰ}�C�c�ؤG����
    TreeNode* buildTree(vector<int>& arr) {
        if (arr.empty()) return nullptr;

        queue<TreeNode*> q; // �إ�queue�x�s�ݳB�z���`�I
        root = new TreeNode(arr[0]); // �إ߮ڸ`�I (�}�C�Ĥ@�Ӥ���)
        q.push(root); // �N�ڸ`�I�[�Jqueue

        size_t i = 1; // �}�C����
        while (!q.empty() ) {//&& i < arr.size()
            TreeNode* current = q.front(); // ���Xqueue�����`�I
            q.pop();

            // �K�[���l�`�I
            if (i < arr.size()) {
                current->left = new TreeNode(arr[i]);
                q.push(current->left); // �N���l�`�I�[�Jqueue
                i++;
            }

            // �K�[�k�l�`�I
            if (i < arr.size()) {
                current->right = new TreeNode(arr[i]);
                q.push(current->right); // �N�k�l�`�I�[�Jqueue
                i++;
            }
            
        }

        return root;
    }

    // ���ǹM��
    void inorderTraversal(TreeNode* node) {
    	
        if (node == nullptr){
        	
			return ; // �p�G�`�I���šA����
		}
		
		if(swi)
			maxL=node->value;//���w����̤j�� 
		else
			maxR=node->value;//���w�k��̤j�� 
        inorderTraversal(node->left);  // �M�����l��
        cout << node->value << " ";    // �X�ݷ�e�`�I
        if(node->value==root->value) swi=false;//�T�{root��m�A����Ĥ@�O�]���@�i�h�N�|�J�� 
        inorderTraversal(node->right); // �M���k�l��
    }

};


int main() {
    BinaryTree tree; // �ŧi�G����

    // ��J�}�C�Ω�c�ؾ�ANULL ��ܪŤl�`�I
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };

    tree.buildTree(arr); // �إ߾�

    // ���ǹM����X
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(tree.root);
    cout<< endl;
    cout<<"�̤j���l�ƭ�: "<<maxL;//��X�̤j���ƭ� 
	cout<< endl; 
    cout<<"�̤j�k�l�ƭ�: "<<maxR; //��X�̤j�k�ƭ� 
    

    return 0;
}
