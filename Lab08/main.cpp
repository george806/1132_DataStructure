#include <iostream>
using namespace std;

// ========================
// �𪺸`�I���O
// ========================
class TreeNode {
public:
    int data;           // �`�I�x�s�����
    TreeNode* left;     // ���V���l�`�I
    TreeNode* right;    // ���V�k�l�`�I

    // �`�I�غc�l�G�]�w��ƨê�l�ƥ��k���Ь���
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ========================
// �G���j�M�����O
// ========================
class BinarySearchTree {
private:
    TreeNode* root; // �ڸ`�I����

    // --- �p�������j���J��k ---
    TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val); // ��촡�J��m�A�إ߷s�`�I
        }

        if (val < node->data) {
            node->left = insert(node->left, val); // ���J���l��
        }
        else if (val > node->data) {
            node->right = insert(node->right, val); // ���J�k�l��
        }
        // �p�G val == node->data�A�����J�]�קK���ơ^

        return node; // �^�ǧ�s�᪺�`�I
    }

    // --- �p�������j�j�M��k ---
    bool search(TreeNode* node, int target) {
        if (node == nullptr) return false;

        if (node->data == target) return true;
        else if (target < node->data) return search(node->left, target); // �~��b���l���
        else return search(node->right, target);// �~��b�k�l���
    }

    // --- �p�������ǹM����k�]��-��-�k�^---
    void inOrderTraversal(TreeNode* node) {
        if (node == nullptr) return;

        inOrderTraversal(node->left);   // �����X���l��
        cout << node->data << " ";   // �L�X�ثe�`�I�����
        inOrderTraversal(node->right); // �A���X�k�l��
    }

    // --- �p�����R����k ---
    TreeNode* deleteNode(TreeNode* node, int val) {
    	if (val < node->data) { //�p�G�n�R���Ȥ�ثe�o�Ӹ`�I�p,�����l���
			node->left = deleteNode(node->left, val);
		}
		else if (val > node->data) { //�p�G�n�R���Ȥ�ثe�o�Ӹ`�I�j,���k�l���
			node->right = deleteNode(node->right, val);
		}
		else { //�p�G�n�R���ȵ���ثe�o�Ӹ`�I,�i�J�R�����T�ر��p
		 if (node->left == nullptr && node->right == nullptr) {//�S���l�`�I 
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr) {//�u���k�l�`�I�A��`�I�|���� 
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {//�u�����l�`�I�A��`�I�|���� 
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        else {//���k�����l�`�I
            TreeNode* ss= findMin(node->right); // �q�k�仼�ɪ���k�A��k�l��̤p�� 
            node->data = ss->data;               // �Υ����N�ثe�`�I����
            node->right = deleteNode(node->right, ss->data); // �⥦�R���A�קK�X�{��ӬۦP�� �A�M�ᱵ�^�h 
        }
		}
    }

    // --- �p������̤p�Ȥ�k ---
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:
    // --- �غc�l�G��l�Ƭ��ž� ---
    BinarySearchTree() : root(nullptr) {}

    // --- ���}���J��k ---
    void insert(int val) {
        root = insert(root, val);
    }

    // --- ���}�j�M��k ---
    bool search(int target) {
        return search(root, target);
    }

    // --- ���}���ǹM����k ---
    void displayInOrder() {
        cout << "�𪺤��ǹM���]�Ƨǫ�^���G�G" << endl;
        inOrderTraversal(root);
        cout << endl;
    }

    // --- ���}�R����k ---
    void deleteValue(int val) {
        root = deleteNode(root, val);
    }
};

int main() {
    BinarySearchTree bst; // �إߤ@�ʪŪ���

    // �w�]���J�����
    int values[] = { 7, 1, 4, 2, 8, 13, 12, 11, 15, 9, 5 };
    int n = sizeof(values) / sizeof(values[0]);

    // ���ƴ��J��
    for (int i = 0; i < n; ++i) {
        bst.insert(values[i]);
    }

    // ���ϥΪ̿�J�n���J�����
    int key;
    cout << "�п�J�n�j�M/�s�W����ȡG";
    cin >> key;

    if (bst.search(key)) {
        cout << "�� " << key << " �w�s�b�𤤡A���s�W�C" << endl;
    }
    else {
        cout << "�� " << key << " ���s�b�A�w�s�W�i�𤤡C" << endl;
        bst.insert(key);
    }

    // ��ܥثe�𪺤��ǹM�����G
    bst.displayInOrder();

    // ���ϥΪ̿�J�n�R�������
    int deleteKey;
    cout << "�п�J�n�R������ȡG";
    cin >> deleteKey;

    // �R���`�I
    bst.deleteValue(deleteKey);

    // ��ܧR���᪺��
    cout << "�R���᪺��]���ǹM���^�G" << endl;
    bst.displayInOrder();

    return 0;
}
