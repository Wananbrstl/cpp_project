#ifndef AVL_H_
#define AVL_H_


namespace lbn{

class Node;

/* get */
Node* getNewNode(int key);

/* clear */
void clear(Node* root);

/* update height*/
void updateHeight(Node* root);

/* left rotate */
Node* left_rotate(Node* root);

/* right rotate */
Node* right_rotate(Node* root);

/* pre  node*/
Node* pre(Node* root);

/* 调整策略 */
Node* adjust(Node* root);

/* insert */ 
Node* insert(Node* root, int key);

/* erase */
Node* erase(Node* root, int key);

/* show */
void show(Node* root);

} // namespace
#endif // AVL_H_
