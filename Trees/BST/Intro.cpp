
#include<iostream>
#include<queue>
using namespace std;
class Node{
public:
    int data;
    Node* left,*right;
    Node(int d){
        data = d;
        left = right = NULL;
    }
};
Node* createBST(Node* root,int data){
   if(root == NULL){
        return new Node(data);
   } 

   if(data >  root -> data){
        root -> right = createBST(root -> right,data);
   }
   else{
    root -> left = createBST(root -> left,data);
   }
   return root;
}

void takeInput(Node* &root){
    int data;
    cin >> data;
    while(data != -1){
        root = createBST(root,data);
        cin >> data;
    }
}


void levelOrderTraversal(Node* root){
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
       if(temp != NULL){
            cout << temp->data << " ";  
            if(temp -> left) q.push(temp -> left);
            if(temp -> right) q.push(temp -> right);
       }else{
            cout << endl;
            if(!q.empty())q.push(NULL);
       }
    }

}

int main(){
    Node* root = NULL;
    cout << "Taking Input" << endl;
    takeInput(root);
    cout << "Printing ---->" << endl;
    levelOrderTraversal(root);
    return 0;
}
// Find Min/max at both ends simple left end and right end.
// Searching Use BST property and Deletion of a Node in BST
/*
  Handeling the 2 child case is important where finding predecessor and replace it with predecessor or succesor and recursively solve the copied node :)
*/

// Leetcode 450. Delete Node in a BST
class Solution {
private:
TreeNode* findPred(TreeNode* root){
    if(root == NULL) return NULL;
    root = root -> left;
    while(root && root -> right != NULL){
        root = root -> right;
    }
    return root;
}
TreeNode* deleteNodeInBST(TreeNode* root,int key){
    if(root == NULL) return NULL;
    if(root -> val == key){
        // handle 4 cases 
        if(root -> left == NULL && root -> right == NULL) {
            delete root;
            return NULL;
        }
        else if(root -> left == NULL && root -> right != NULL) {
            TreeNode* temp = root -> right;
            root -> right = NULL;
            delete root;
            return temp;
        }
        else if(root -> left != NULL && root -> right == NULL) {
            TreeNode* temp = root -> left;
            root -> left = NULL;
            delete root;
            return temp;
        }else{
            TreeNode* pred = findPred(root);
            root -> val = pred -> val;
            root -> left = deleteNodeInBST(root -> left,root -> val);
            return root;
        }
    }

    if(root -> val > key){
        root -> left = deleteNodeInBST(root -> left,key);
    }else{
        root -> right = deleteNodeInBST(root -> right,key);
    }
    return root;
}
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
       return deleteNodeInBST(root,key);
    }
};


