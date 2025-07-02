
//530. Minimum Absolute Difference in a BST
//return the minimum absolute difference between the values of any two different nodes in the tree.
//Brute Force -> take a vector and store inorder in it and then later cal minimum diff 
// Anoter Apporach without space-> while inorder traversal for every node subtract from predecessor and succesor and maintain a min elem
class Solution {
private:
    TreeNode* getPred(TreeNode* root){
        if(root && root -> right){
            return getPred(root -> right);
        }
        return root;
    }
    TreeNode* getSucc(TreeNode* root){
        if(root && root -> left){
            return getSucc(root -> left);
        }
        return root;
    }
    void getDiff(TreeNode* root,int& mini){
        if(root == NULL) return;
        // if predecessor exist then update else ignore Vice versa for Succesor
        if(root -> left){ // prevents from passing null to getPred() and getSucc()
            TreeNode* left = getPred(root -> left);
            mini = min(mini,abs((root -> val) - (left -> val)));
        }
        if(root -> right){
            TreeNode* right = getSucc(root -> right);
            mini = min(mini,abs((root -> val) -( right -> val)));
        }

        getDiff(root -> left,mini);
        getDiff(root -> right,mini);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        int min = INT_MAX;
        getDiff(root,min);
        return min;
    }
};

//98. Validate BST
//Q.is Given Tree a BST ? nodes[1,1e4];
//for the first node in inorder just store it in prev !,rest of nodes compare with prev.Easy Exit when Not a BST!
// My Approach i.e 1st

class Solution {
private:
void validate(TreeNode* root,int& prev,bool& prevLoaded,bool& isBST){
    if(root == NULL) return;
    if(isBST == false) return;

    validate(root -> left,prev,prevLoaded,isBST);
    // for the first node in inorder just store it !
    if(!prevLoaded){
        prevLoaded = true;
        prev = root -> val;
    }
    else{
        // rest of nodes compare with prev.
        int curr = root -> val;
        if(prev < curr){
            prev = curr;
        }else{
            // Easy Exit when Not a BST
            isBST = false;
        }
    }
    validate(root -> right,prev,prevLoaded,isBST);
}
public:
    bool isValidBST(TreeNode* root) {
        if(root -> left == NULL && root -> right == NULL) return true;
        int prev = INT_MIN;
        bool prevLoaded = false;
        bool isBST = true;
        validate(root,prev,prevLoaded,isBST);
        return isBST;
    }
};
//Another Beautiful Approach 
// preOrder Traversal Variation where we can assume the range of any elem say root (-inf,inf) then upon left (-inf,root->val)
// for right (root -> val , inf); if element lies then valid and check further if out of range invalid :)
// for without duplicates (root -> val > min && root -> val < max) duplicates root -> val >= min && root -> val <= max
class Solution {
private:
    bool checkValid(TreeNode* root,int min,int max){
        // why ? succesful Termination and no violation till now 
        // next call is only placed when curr is valid so upon returning true is returned ! 
        if(root == NULL) return true;

        if(root -> val >= min && root -> val <= max){
            bool left = checkValid(root -> left,min,root -> val);
            bool right = checkValid(root -> right,root -> val,max);
            return left && right;
        } return false;
    }
public:
    bool isValidBST(TreeNode* root) {
        return checkValid(root,INT_MIN,INT_MAX);
    }
};

// Predecessor And Succesor of BST.
// decrementing k in Inorder Traversal when 0 return root !
// swap right and left for kth largest element !
class Solution {
private:
    int smallest(TreeNode* root, int& k,int& left,int& right){
        if(root == NULL) return 0;
       
       
        left = smallest(root -> left,k,left,right);
        if(left != 0) return left;

        k--;
        if(k == 0) return root -> val;

        right = smallest(root -> right,k,left,right);
        if(right != 0) return right;
        
        
        return 0;
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        int left = 0, right = 0;
        return smallest(root, k,left,right);
    }
};

// pred and succesor Question 
// track down possible pred and succ in case the node has no child if has then return child (subtrees) else tracked oned :)
 pair<int, int> predecessorSuccessor(TreeNode *root, int key) { 
    if(root == NULL) return {-1,-1};
     int possiblePred = -1,possibleSucc = -1; 
     TreeNode* node = root;
     while(node && node -> data != key){
         if(node -> data < key){
             possiblePred = node -> data;
             node = node -> right;
         }else{
             possibleSucc = node -> data;
             node = node -> left;
         }
     } 
     // check if it has children if yes return them else possible pred or succ 
     if(node != NULL){ 
         TreeNode* left = node -> left; 
         while(left != NULL){ 
             possiblePred = left -> data; 
             left = left -> right; 
         } 
         TreeNode* right = node -> right; 
         while(right != NULL){ 
             possibleSucc = right -> data; 
             right = right -> left; 
         } 
     } 
     return {possiblePred,possibleSucc}; 
 } 

 //235 . LCA in BST
 // MY approach maintaing 2 pointers 
 class Solution {
private:
   TreeNode* solve(TreeNode* root,TreeNode* p, TreeNode* q,TreeNode* left,TreeNode* right,TreeNode* prev){
        if(left != right) return prev;
        
        if(left != NULL){
            if(p -> val < left -> val){
                left = left -> left;
            }else if(p -> val > left -> val){
                left = left -> right;
            }
        }

        if(right != NULL){
            prev = right;
            if(q -> val < right -> val ){
                right = right -> left;
            }else if(q -> val > right -> val){
                right = right -> right;
            }
        }

        TreeNode* temp = solve(root,p,q,left,right,prev);
        return temp;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* prev = root;
       return solve(root,p,q,root,root,prev);
    }
};
// Simple Approach of moving them both twice else return root !
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* comparator = root;
        // can i assume both p and q lies in left
        if(comparator -> val > p -> val && comparator -> val > q -> val){
            return lowestCommonAncestor(root -> left,p,q);
        }// Both the values at right
        else if(comparator -> val < p -> val && comparator -> val < q -> val){
            return lowestCommonAncestor(root -> right,p,q);
        }// the values are splited so lca is curr root
        else{
            return root;
        }
    }
};
