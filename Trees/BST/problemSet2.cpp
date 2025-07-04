// 653 . Two sum in bst
// Excellent approach of applying 2 sum on bst same as 2 pointer approach on sorted array!
// storing route of min elem in min stack and vice versa ! and 2 pointer approach !
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        stack<TreeNode*> min,max;
        // Full Stacks
        TreeNode* temp = root;
        while(temp){
            min.push(temp);
            temp = temp -> left;
        }
        temp = root;
        while(temp){
            max.push(temp);
            temp = temp -> right;
        }
        while(!min.empty() && !max.empty() && min.top() != max.top()){
            int left = min.top() -> val;
            int right = max.top() -> val;
            int data = left + right;
            if(data == k) return true;
            if(data < k){
                TreeNode* top = min.top();
                min.pop();
                TreeNode* temp = top -> right;
                while(temp){
                    min.push(temp);
                    temp = temp -> left;
                }
            }else{
                TreeNode* top = max.top();
                max.pop();
                TreeNode* temp = top -> left;
                while(temp){
                    max.push(temp);
                    temp = temp -> right;
                }
            }
        }
        return false;
    }
};
// LC 897. Increasing Order Search Tree ||  converting a bst into linked list
// Just a Inorder Iterative Traversal then for every node make left NULL and maintain prev and connect with curr pointer 
class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* temp = root;
        s.push(temp);
        bool head = true;
        TreeNode* prev = NULL;
        TreeNode* LL = NULL;
       while(!s.empty()){

            while(temp && temp -> left){
                temp = temp -> left;
                s.push(temp);
            }
          
            TreeNode* top = s.top();
            if(head){
                LL = top;
                prev = top;
                head = false;
                LL -> left = NULL;
            }else{
                top -> left = NULL;
                prev -> right = top;
                prev = top;
            }
            s.pop();
            // end
            temp = top -> right;
            if(temp){
                s.push(temp);
            } 
       }
        return LL;
    }
};

//1008. Construct Binary Search Tree from Preorder Traversal

// stack based majority my solutiom 
// push elem to the left if smaller go on..
// if greater elem there is chance its greater than parent so pop up till
// greater elem found or stack empty
// to its childs right put the elem and put the new elem into stack to continue the process why in right ?
// if it was smaller it should be in left but the chance was gone so its place is in right !
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        stack<TreeNode*> s;
        int n = preorder.size();
        TreeNode* node = new TreeNode(preorder[0]);
        s.push(node);
        for(int i = 1; i < n; i++){
            TreeNode* temp = s.top();
            if(!s.empty() &&  temp -> val > preorder[i]){
                temp -> left = new TreeNode(preorder[i]);
                s.push(temp -> left);   
            }
            else{
                while(!s.empty() && s.top() -> val < preorder[i]){
                    temp = s.top();
                    s.pop();
                }
                temp -> right = new TreeNode(preorder[i]);
                s.push(temp -> right);
            }
        }
        return node;
    }
};

// Range Based Solution will an elem lies in a range !
// simple preorder traversal 
// if dosent lie in range return null and proceed
class Solution {
TreeNode* BST(vector<int>& preorder,int min,int max,int& i){
    if(i >= preorder.size()) return NULL;
    
    if(preorder[i] > min && preorder[i] < max){
        TreeNode* root = new TreeNode(preorder[i]);
        i++;
        root -> left = BST(preorder,min,root -> val,i);
        root -> right = BST(preorder,root -> val,max,i);
        return root;
    }else{
        return NULL;
    }
}
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return BST(preorder,INT_MIN,INT_MAX,i);
    }
};

// 109. Convert Sorted List to Binary Search Tree
// Simple  Divide and Conquer just take out middle divide in 2 halves and pass 1 to left and 1 to right
// The Next Question is Extremely similar 
class Solution {
public:
    ListNode* middle(ListNode* head){
        if(head == NULL) return NULL;
        if(head -> next == NULL || head -> next -> next == NULL) return head;
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = NULL;
        while(fast -> next != NULL && fast -> next -> next != NULL){
            prev = slow;
            slow= slow -> next;
            fast = fast -> next -> next;
        }
        return prev;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        
        ListNode* mid = middle(head);

        if(mid == NULL) return NULL;
        if(mid -> next == NULL) return new TreeNode(head -> val);

        TreeNode* root = new TreeNode(mid -> next -> val);
        ListNode* nxt = mid -> next;
        mid -> next = NULL;

        root -> left = sortedListToBST(head);
        ListNode* next = nxt -> next;
        nxt -> next = NULL;

        root -> right = sortedListToBST(next);
        return root;
    }
};


//1382 Balance a BST
 // Given a non height balanced bst -> take inorder 
 // the inorder of balancd bst is also same ..! 
 // use this hint ! create a vector to store in order then using that array build a bst!
class Solution {
private:
void takeInput(TreeNode* root,vector<TreeNode*>& nodes){
    if(root == NULL) return;

    takeInput(root -> left,nodes);
    nodes.push_back(root);
    takeInput(root -> right,nodes);
}

TreeNode* balance(vector<TreeNode*>& nodes,int start , int end){
    // base case
    if(start > end) return NULL;
    // code
    int mid = start + (end - start) / 2;
    TreeNode* root = nodes[mid];
    root -> left = balance(nodes,start,mid-1);
    root -> right = balance(nodes,mid + 1,end);
    return root;
}
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<TreeNode*> nodes;
        takeInput(root,nodes);
        return balance(nodes,0 ,nodes.size() - 1);
    }
};