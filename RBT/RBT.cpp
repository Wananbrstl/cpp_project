/* File   : RBT/RBT.cpp
 *   Author : Wananbrstl
 *   Date   : 2023.1.13
 */
#include <cstdio>
#include <assert.h>

namespace lbn {
/* color */
enum {
    RED = 0,
    BLACK,
    DOUBLE_BLACK,
};

typedef struct Node Node;

/* node */
struct Node{
    int key, color;
    Node* left, *right;

    Node() :
        key(0), color(BLACK), left(nullptr), right(nullptr){}
    Node(int _key, int _color) : 
        key(_key), color(_color), left(nullptr), right(nullptr){}
    Node(int _key, int _color, Node* _left, Node* _right) : 
        key(_key), color(_color), left(_left), right(_right){}

};

Node _NIL, * const NIL = &_NIL;

/* before main function */
__attribute__((constructor)) 
void Init_NIL() {
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL;
    NIL->key = 0;
}

/* create node */
Node* getNewNode(int key) {
    Node* node = new Node(key, RED); 
    node->left = node->right = NIL;
    return node;
}

/* free node */
void freeNode(Node* root) {
    if(NIL == root) return;
    freeNode(root->left);
    freeNode(root->right);
    delete root;
}

/* big left rotate */
Node *left_rotate(Node* root) {
    if(NIL == root) return root;
    Node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    return tmp;
}

/* big right rotate */
Node *right_rotate(Node* root) {
    if(NIL == root) return root;
    Node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    return tmp;
}

int hasRedChild(Node* root) {
    return (root->left->color == RED) || (root->right->color == RED);
}

Node* insert_maintain(Node* root) {
    if(!hasRedChild(root)) return root; // no 
    if(root->left->color == RED && root->right->color == RED) {
        if(!hasRedChild(root->left) && !hasRedChild(root->right)) return root;
        goto insert_end;
    }
    if(root->left->color == RED) {
        if(!hasRedChild(root->left)) return root;
        if(root->left->right->color == RED) {
            root->left = left_rotate(root->left);
        }
        root = right_rotate(root);
    }
    if(root->right->color == RED) {
        if(!hasRedChild(root->right)) return root;
        if(root->right->left->color == RED) {
            root->right = left_rotate(root->right);
        }
        root = left_rotate(root);
    }
insert_end:
    root->color = RED;
    root->left->color = root->right->color = BLACK;
    return root;
}

Node* __insert(Node* root, int key) {
    if(NIL == root) return getNewNode(key);
    if(key == root->key) return root;
    else if(key > root->key) {
        root->right = __insert(root->right, key);
    } else {
        root->left = __insert(root->left, key);
    }
    return insert_maintain(root);
}

Node* insert(Node* root, int key) {
    root = __insert(root, key);
    root->color = BLACK; // TODO: it's neccesary?
    return root;
}

Node* erase_matain(Node* root) {
    /* 两个子节点都不是双重黑 */
    if(root->left->color != DOUBLE_BLACK && root->right->color != DOUBLE_BLACK) return root;
    if(root->left->color == DOUBLE_BLACK) { /* 左边是双重黑 */
        if(root->right->color == RED) { /* 兄弟节点是红色的特殊情况 */
            root->color = RED;
            root->right->color = BLACK;
            root = left_rotate(root);
            root->left = erase_matain(root->left);
            return root;
        } 
        if(!hasRedChild(root->right))  { /* 兄弟节点的两个子节点都是黑色 */
            root->color += 1;
            root->left->color -= 1;
            root->right->color -= 1;
            return root;
        }
        /*TODO: 重要!!!!!!!!!!!!!!*/
        if(root->right->right->color != RED) { /* RL */
            root->right->color = RED;
            root->right->left->color = BLACK;
            root->right = right_rotate(root->right);
        }
        root->right->color = root->color;
        root->left->color -= 1;
        root = left_rotate(root);
        root->right->color = root->left->color = BLACK;
    } else { /* right tree */
        if(root->left->color == RED) {
            root->color = RED;
            root->left->color = BLACK;
            root = right_rotate(root);
            root->right = erase_matain(root->right);
            return root;
        }
        if(!hasRedChild(root->left))  { /* 兄弟节点的两个子节点都是黑色 */
            root->color += 1;
            root->right->color -= 1;
            root->left->color -= 1;
            return root;
        }
        if(root->left->left->color != RED) { /* LR */
            root->left->color = RED;
            root->left->right->color = BLACK;
            root->left = left_rotate(root->left);
        }
        root->left->color = root->color;
        root->right->color -= 1;
        root = right_rotate(root);
        root->left->color = root->right->color = BLACK;
    }
    return root;
}

Node* pre(Node* root) {
    if(NIL == root) return root;
    Node* tmp = root->left;
    while (NIL != tmp->right) tmp = tmp->right;
    return tmp;
}

Node* __erase(Node* root, int key) {
    if(NIL == root) return root;
    if(root->key > key) {
        root->left = __erase(root->left, key);
    } else if(root->key < key) {
        root->right = __erase(root->right, key);
    } else {
        if(NIL == root->left || NIL == root->right) {
            Node* tmp = (root->left != NIL ? root->left : root->right);
            tmp->color += root->color;
            delete root;
            return tmp;
        } else {
            Node* tmp = pre(root);
            root->key = tmp->key;
            root->left = __erase(root->left, tmp->key);
        }
    }
    return erase_matain(root);
}

Node* erase(Node* root, int key) { 
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}

void output(Node* root) {
    assert(root != nullptr);
    if(NIL == root) return;
    printf("%d : [%d, %d]  %s\n",
        root->key,
        root->left->key,
       root->right->key,
       root->color ? "BLACK" : "RED"
   );
    output(root->left);
    output(root->right);
}

Node* modify(Node* root, int key, int tar) {
    if(NIL == root) return root;
    root = erase(root, key);
    root = insert(root, tar);
    return root;
}

} // namespace 


using namespace lbn;
int main (int argc, char *argv[])
{
    Node* root = NIL;
    // int opt, val;
    // for(;~scanf("%d%d", &opt, &val);) {
    //     switch (opt) {
    //         case 1: root = insert(root, val); break;
    //         case 2: break;
    //         default: break;
    //     }
    //     output(root);
    // }
    root = insert(root, 1);
    output(root);
    printf("\n");
    root = insert(root, 2);
    output(root);
    printf("\n");
    root = insert(root, 3);
    output(root);
    printf("\n");
    root = insert(root, 4);
    output(root);
    printf("\n");
    root = insert(root, 5);
    output(root);
    printf("\n");
    root = insert(root, 6);
    output(root);
    printf("\n");
    root = erase(root, 4);
    output(root);
    printf("\n");

    freeNode(root);
    return 0;
}
