#include <cstdio>
#include <iostream>
#include <math.h>
#include <assert.h>
#include "AVL.h"

namespace lbn {
class Node{
public:
    Node* left, *right;
    int val, h;
    
    Node(int v) :  
        val(v), left(nullptr), right(nullptr), h(1) {}
    Node(int v, Node* l, Node* r) :  
        val(v), left(l), right(r), h(1) {}
};

/* get */
Node* getNewNode(int key) {
    Node* nw_node = new Node(key);
    return nw_node;
}

/* clear */
void clear(Node* root){
    if(!root) return;
    clear(root->left) ;
    clear(root->right);
    delete root;
}

/* update height*/
void updateHeight(Node* root){
    if(!root) return;
    int left_height  = root->left  ? root->left->h  : 0;
    int right_height = root->right ? root->right->h : 0;
    root->h = ((left_height > right_height) ? left_height : right_height ) + 1;
}

/* left rotate */
Node* left_rotate(Node* root) {
    assert(root != nullptr);
    Node* tmp = root->right;
    assert(tmp != nullptr);
    root->right = tmp->left;
    tmp->left = root;
    // NOTE: 重要的两个调整，因为你改变了位置，也就是改变了树高信息
    updateHeight(root);
    updateHeight(tmp);
    return tmp;
}

/* right rotate */
Node* right_rotate(Node* root) {
    assert(root != nullptr);
    Node* tmp = root->left;
    assert(tmp != nullptr);
    root->left = tmp->right;
    tmp->right = root;
    // NOTE: 重要的两个调整，因为你改变了位置，也就是改变了树高信息
    updateHeight(root);
    updateHeight(tmp);
    return tmp;
}

/* pre  node*/
Node* pre(Node* root){
    Node* tmp = root->left;
    while(tmp->right != NULL) tmp = tmp->right;
    return tmp;
}

/* 调整策略 */
Node* adjust(Node* root) {
    if(!root) return nullptr;
    int left_h  = root->left  ? root->left->h  : 0;
    int right_h = root->right ? root->right->h : 0;
    if( abs(left_h - right_h) <= 1) return root;
    if(left_h > right_h) { // L
        int ll_h = root->left->left ? root->left->left->h : 0;
        int lr_h = root->left->right ? root->right->left->h : 0;
        if( lr_h > ll_h ) { // LR
            root->left = left_rotate(root->left);
        }
        root = right_rotate(root);
    } else { // R
        int rl_h = root->right->left ? root->right->left->h : 0;
        int rr_h = root->right->right ? root->right->right->h : 0;
        if( rl_h > rr_h ) { // RL
            root->right = right_rotate(root->right);
        }
        root = left_rotate(root);
    }
    return root;
}

/* insert */ 
Node* insert(Node* root, int key){
    if(!root) return getNewNode(key);
    if(root->val == key) return root;
    if(root->val > key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    // NOTE: 注意调整树高防止信息不对的调整失败
    updateHeight(root);
    return adjust(root);
}


/* erase */
Node* erase(Node* root, int key){
    if(!root) return nullptr;
    if(root->val > key) {
        root->left = erase(root->left, key);
    } else if(root->val < key) {
        root->right = erase(root->right, key);
    } else {
        if(nullptr == root->left || nullptr == root->right) {
            Node* tmp = root->left ? root->left : root->right;
            delete root;
            return tmp;
        } else {
            Node* tmp = pre(root);
            root->val = tmp->val;
            // NOTE: erase之后会改变根节点的信息，需要注意
            root->left = erase(root->left, tmp->val);
        }
    }
    updateHeight(root);
    return adjust(root);
}

void show(Node* root){
    if(!root) return;
    show(root->left);
    printf("%d : [%d, %d], height = %d\n", root->val, (root->left ? root->left->val : 0), (root->right? root->right->val : 0), root ? root->h : 0);
    show(root->right);
}

} // namespace

/* self test */
//
using namespace lbn;

int main (int argc, char *argv[])
{
    Node* root = nullptr;
    // int opt, num;
    // while(true) {
    //     std::cin >> opt >> num;
    //     if(opt == -1) break;
    //     if(opt == 0)  {
    //         root = erase(root, num);
    //     } else if(opt == 1){
    //         root = insert(root, num);
    //     }
    //     show(root);
    // }
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 5);
    show(root);
    std::cout << std::endl;
    root = erase(root, 2);
    show(root);
    clear(root);

    return 0;
}
