#include <iostream>
#include <vector>

class BinaryTree;

struct Node{
    int val;
    Node *left, *right;

    Node(int key) : 
        val(key), left(nullptr), right(nullptr) {}
    Node(int key, Node* l, Node* r) :
        val(key), left(l), right(r) {}

};

class BinaryTree {
private:
    Node* root; 
    
public:
    BinaryTree() :
        root(nullptr) {}

    ~BinaryTree();

    Node* buildTree(const std::vector<int>& nums, int left, int right);
    
    Node* getNewNode(int val);

    void clear(Node* root);
    
    Node* insert(Node* root, int val);
    
    Node* erase(Node* root, int val);

private:
    Node* pressor(Node* root);

};

BinaryTree::~BinaryTree() 
{
    clear(root);
}

Node*
BinaryTree::buildTree(const std::vector<int>& nums, int left, int right)
{
    // if(left > right) return nullptr;
    // if(left == right) return getNewNode(nums[left]);
    // int mid = (left + right) / 2;
    // Node* node = getNewNode(nums[mid]);
    // node->left = buildTree(nums, left, mid - 1);
    // node->right = buildTree(nums, mid + 1, right);
    // return node;
    Node* root = nullptr;
    for(int i = 0; i < nums.size(); ++i)
        root = insert(root, nums[i]);
    return root;
}

Node*
BinaryTree::getNewNode(int val)
{
    Node *node = new Node(val);
    return node;   
}

void
BinaryTree::clear(Node *r)
{
    // if(root == nullptr) return;
    // clear(root->left);
    // clear(root->right);
    delete r;
    if(!r) std::cout << "current root = " << r << std::endl;
    else std::cout << "root is nullptr" << std::endl;
    r = nullptr;
}

Node* 
BinaryTree::insert(Node* root, int val)
{
    if(!root) return getNewNode(val);
    if(root->val == val) return root;
    else if(root->val > val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

Node* 
BinaryTree::pressor(Node* root)
{
    if(!root) return nullptr;
    Node* res = root;
    while(res->right) res = res->right;
    return res;
}

Node*
BinaryTree::erase(Node* root, int val)
{
    if(!root) return nullptr;
    if(root->val > val) {
        root->left = erase(root->left, val);
        return root;
    } else if(root->val < val ){
        root->right = erase(root->right, val);
        return root;
    } else { // root->val == val
        if(root->left == nullptr || root->right == nullptr) {
            Node* tmp = root->left ? root->left : root->right;
            delete root;
            return tmp;
        } else {
            Node* pre = pressor(root);
            std::cout << root->val << "  's pressor is " << pre->val << std::endl;
            root->val = pre->val;
            erase(root->left, pre->val);
        }
    }
    return root;
}

void show(Node* root) 
{
    if(nullptr == root) return;
    show(root->left);
    std::cout << root->val << " " ;
    show(root->right);
}

/* For Test the delete  */
void d(int* root)
{
    delete root;
    root = nullptr;
}
void test()
{
    int* num = new int(2023);
    std::cout << *num  << std::endl;
    d(num);
    if(nullptr == nullptr)
        std::cout << "nullptr" << std::endl;
    else
        std::cout << *num << std::endl;
}

int main (int argc, char *argv[])
{
    std::vector<int> nums{1, 3, 5, 7, 9, 11, 13};
    std::cout << nums.size() << std::endl;
    BinaryTree tree;
    Node* root = tree.buildTree(nums, 0, nums.size()-1);
    show(root);
    std::cout << std::endl;
    root = tree.insert(root, 2);
    root = tree.insert(root, 4);
    root = tree.insert(root, 6);
    show(root);
    std::cout << std::endl;
    root = tree.insert(root, 2);
    root = tree.insert(root, 2);
    root = tree.insert(root, 6);
    root = tree.insert(root, 6);
    show(root);
    std::cout << std::endl;
    root = tree.erase(root, 1);
    root = tree.erase(root, 2);
    root = tree.erase(root, 3);
    root = tree.erase(root, 4);
    root = tree.erase(root, 5);
    root = tree.erase(root, 6);
    root = tree.erase(root, 7);
    root = tree.erase(root, 9);
    root = tree.erase(root, 11);
    root = tree.erase(root, 13);
    show(root);
    std::cout << std::endl;
    // tree.clear(root);
    // std::cout << "===============================" << std::endl;
    // if(root != nullptr) show(root);
    // if(root == nullptr) std::cout << "root = " <<  root << std::endl;
    // test();
    return 0;
}
