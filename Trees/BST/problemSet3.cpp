// Simple Merge 2 bst and return Their Nodes (Array)
class Solution {
public:
    // Helper to do inorder traversal and collect values
    void inorder(TreeNode* root, vector<int>& vec) {
        if (!root) return;
        inorder(root->left, vec);
        vec.push_back(root->val);
        inorder(root->right, vec);
    }

    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> v1, v2;
        inorder(root1, v1);
        inorder(root2, v2);

        // Merge two sorted vectors
        vector<int> result;
        int i = 0, j = 0;
        while (i < v1.size() && j < v2.size()) {
            if (v1[i] < v2[j]) {
                result.push_back(v1[i++]);
            } else {
                result.push_back(v2[j++]);
            }
        }
        // Push remaining elements
        while (i < v1.size()) result.push_back(v1[i++]);
        while (j < v2.size()) result.push_back(v2[j++]);

        return result;
    }
};

// Code Studio IMP
// Convert BSTs into Sorted LL , Merge 2 Sorted LL , Sorted List to BST. 1,2,3 (3 is not req in Quest && 3 already done)
    void increasingBST(TreeNode* root, TreeNode*& prev, TreeNode*& head) {
        if (root == NULL) return;

        increasingBST(root->left, prev, head);
        if (prev == NULL) {
            head = root;
            prev = root;
            prev->left = NULL;
        } else {
            prev->right = root;
            prev = root;
            prev->left = NULL;
        }
        increasingBST(root->right, prev, head);
    }

    TreeNode* merge(TreeNode* root1, TreeNode* root2) {
        if (!root1) return root2;
        if (!root2) return root1;
        TreeNode* head = NULL;
        if (root1->data < root2->data) {
            head = root1;
            head->right = merge(root1->right, root2);
        } else {
            head = root2;
            head->right = merge(root1, root2->right);
        }
        return head;
    }

    TreeNode* middle(TreeNode* head) {
        if (head == NULL || head->right == NULL) return NULL;
        TreeNode* slow = head;
        TreeNode* fast = head;
        TreeNode* prev = NULL;

        while (fast->right && fast->right->right) {
            prev = slow;
            slow = slow->right;
            fast = fast->right->right;
        }
        return prev;
    }



    vector<int> mergeBSTs(TreeNode* root1, TreeNode* root2) {
        TreeNode* prev = NULL;
        TreeNode* head1 = NULL;
        increasingBST(root1, prev, head1);

        prev = NULL;
        TreeNode* head2 = NULL;
        increasingBST(root2, prev, head2);

        TreeNode* mergedList = merge(head1, head2);
        vector<int> res;
        TreeNode* temp = mergedList;
        while(temp){
            res.push_back(temp -> data);
            temp = temp -> right;
        }
        return res;
    }


vector<int> mergeBST(TreeNode *root1, TreeNode *root2)
{
    // I should have returned the Converted BST from LL which was already covered !
    return mergeBSTs(root1,root2);
}


// Leetcode 1373. Maximum Sum BST in Binary Tree
// Core Logic
// How To Find Out isBST for Every Node i.Do Inorder and check weather sorted ii. Compare
// root to be Min than max of LSub Tree and root less than Min in right STree BST Property !
// Need Min , Max , Bool T/F for understanding , Sum (which only updates on valid BST occurence)


// key points 
// -> dont confuse seeing int min and max just to pass any leaf node and then compare with root -> data just used as flag
// maintaing a seperate max is good !

class Validator{
    public:
    int min;
    int max;
    bool isBST;
    int sum;
    Validator(): min(INT_MAX),max(INT_MIN),isBST(true),sum(0) {}
    Validator(int m, int mx, bool val, int t): min(m),max(mx),isBST(val),sum(t) {} 
};

class Solution {
private:
    Validator* getSum(TreeNode* root,int& m){
        if(root == NULL) return new Validator();

        Validator* left = getSum(root -> left,m);
        Validator* right = getSum(root -> right,m);

        // Check if its Valid BST
        if(left -> isBST && right -> isBST && (root -> val > left -> max) && (root -> val < right -> min)){
           int sum =  left -> sum + right -> sum + root -> val;
            m = max(m,sum);
            // if leaf node return root -> val else left -> min ...
            int min = (root -> left)?  left -> min : root -> val;
            int max = (root -> right)? right -> max : root -> val;
            return new Validator(min,max,true,sum);
        }
        else return new Validator(0,0,false,0);
    }
public:
    int maxSumBST(TreeNode* root) {
        int Max = 0;
        Validator* node = getSum(root,Max);
        return Max;
    }
};