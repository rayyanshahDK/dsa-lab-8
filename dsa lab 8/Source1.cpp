#include <iostream>
using namespace std;
#define MAXNODES 500
template <typename ItemType>
class BinaryTree {
private:
    struct Node {
        ItemType data;
        int leftChild, rightChild, parent;
    };
    Node tree[MAXNODES];
    int nodeCount;
    int root;
public:
    BinaryTree() {
        nodeCount = 0;
        root = -1;
    }
    BinaryTree(ItemType data) {
        nodeCount = 1;
        root = 0;
        tree[0].data = data;
        tree[0].leftChild = -1;
        tree[0].rightChild = -1;
        tree[0].parent = -1;
    }
    BinaryTree(BinaryTree& leftBT, ItemType data, BinaryTree& rightBT) {
        nodeCount = 1 + leftBT.nodeCount + rightBT.nodeCount;
        root = 0;
        tree[0].data = data;
        tree[0].leftChild = 1;
        tree[0].rightChild = 1 + leftBT.nodeCount;
        tree[0].parent = -1;
        for (int idx = 0; idx < leftBT.nodeCount; idx++) {
            tree[idx + 1] = leftBT.tree[idx];
            tree[idx + 1].parent = 0;
        }
        for (int idx = 0; idx < rightBT.nodeCount; idx++) {
            tree[idx + 1 + leftBT.nodeCount] = rightBT.tree[idx];
            tree[idx + 1 + leftBT.nodeCount].parent = 0;
        }
    }
    bool Empty() {
        return nodeCount == 0;
    }
    BinaryTree GetLeftChild() {
        BinaryTree leftSubtree;
        if (Empty() || tree[root].leftChild == -1) {
            cout << "Left child not found!" << endl;
        }
        else {
            leftSubtree.tree[0] = tree[tree[root].leftChild];
            leftSubtree.root = 0;
            leftSubtree.nodeCount = 1;
        }
        return leftSubtree;
    }
    BinaryTree GetRightChild() {
        BinaryTree rightSubtree;
        if (Empty() || tree[root].rightChild == -1) {
            cout << "Right child not found!" << endl;
        }
        else {
            rightSubtree.tree[0] = tree[tree[root].rightChild];
            rightSubtree.root = 0;
            rightSubtree.nodeCount = 1;
        }
        return rightSubtree;
    }
    ItemType GetValue() {
        if (Empty()) {
            cout << "Empty tree error!" << endl;
            return ItemType();
        }
        return tree[root].data;
    }
};
//dynamically


#include <iostream>
using namespace std;

template <typename ItemType>
class BinaryTree {
private:
    struct Node {
        ItemType data;
        Node* leftChild;
        Node* rightChild;
        Node* parent;
        
        Node(ItemType value) : data(value), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
    };
    
    Node* root;
    int nodeCount;
   
    Node* copyTree(Node* sourceNode, Node* parentNode = nullptr) {
        if (sourceNode == nullptr) return nullptr;
        
        Node* newNode = new Node(sourceNode->data);
        newNode->parent = parentNode;
        newNode->leftChild = copyTree(sourceNode->leftChild, newNode);
        newNode->rightChild = copyTree(sourceNode->rightChild, newNode);
        
        return newNode;
    }
    
    int countNodes(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->leftChild) + countNodes(node->rightChild);
    }
    

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->leftChild);
            deleteTree(node->rightChild);
            delete node;
        }
    }

public:
    BinaryTree() {
        nodeCount = 0;
        root = nullptr;
    }
    
    BinaryTree(ItemType data) {
        nodeCount = 1;
        root = new Node(data);
    }
    
    BinaryTree(BinaryTree& leftBT, ItemType data, BinaryTree& rightBT) {
        root = new Node(data);
        
        if (!leftBT.Empty()) {
            root->leftChild = copyTree(leftBT.root, root);
        }
        
        if (!rightBT.Empty()) {
            root->rightChild = copyTree(rightBT.root, root);
        }
        
        nodeCount = 1 + leftBT.nodeCount + rightBT.nodeCount;
    }
    

    BinaryTree(const BinaryTree& other) {
        if (other.Empty()) {
            root = nullptr;
            nodeCount = 0;
        } else {
            root = copyTree(other.root);
            nodeCount = other.nodeCount;
        }
    }
       
    ~BinaryTree() {
        deleteTree(root);
    }
    
    bool Empty() {
        return nodeCount == 0;
    }
    
    BinaryTree GetLeftChild() {
        BinaryTree leftSubtree;
        if (Empty() || root->leftChild == nullptr) {
            cout << "Left child not found!" << endl;
        }
        else {
            leftSubtree.root = copyTree(root->leftChild);
            leftSubtree.nodeCount = countNodes(leftSubtree.root);
        }
        return leftSubtree;
    }
    
    BinaryTree GetRightChild() {
        BinaryTree rightSubtree;
        if (Empty() || root->rightChild == nullptr) {
            cout << "Right child not found!" << endl;
        }
        else {
            rightSubtree.root = copyTree(root->rightChild);
            rightSubtree.nodeCount = countNodes(rightSubtree.root);
        }
        return rightSubtree;
    }
    
    ItemType GetValue() {
        if (Empty()) {
            cout << "Empty tree error!" << endl;
            return ItemType();
        }
        return root->data;
    }
};


/* ex 8.2
    #include <iostream>
#define MAXSIZE 100
using namespace std;
class BT {
private:
    int nodes[MAXSIZE];
    bool exists[MAXSIZE];  // to check if a node exists at that position
public:
    BT() {
        for (int idx = 0; idx < MAXSIZE; idx++) {
            exists[idx] = false;
        }
    }
    void add(int val, int pos = 0) {
        if (pos >= MAXSIZE) {
            cout << "Array overflow!" << endl;
            return;
        }
        if (!exists[pos]) {
            nodes[pos] = val;
            exists[pos] = true;
        }
        else {
            cout << "Position already occupied at index " << pos << endl;
        }
    }
    void addLeft(int parentPos, int val) {
        add(val, 2 * parentPos + 1);
    }
    void addRight(int parentPos, int val) {
        add(val, 2 * parentPos + 2);
    }
    void inorderTraversal(int pos = 0) {
        if (pos >= MAXSIZE || !exists[pos]) return;
        inorderTraversal(2 * pos + 1);
        cout << nodes[pos] << " ";
        inorderTraversal(2 * pos + 2);
    }
};
int main() {
    BT tree;
    tree.add(10); // root
    tree.addLeft(0, 5);
    tree.addRight(0, 15);
    tree.addLeft(1, 2);
    tree.addRight(1, 7);
    cout << "Inorder Result: ";
    tree.inorderTraversal();
    cout << endl;
    return 0;
}
ex8.1
/*
#include <iostream>
using namespace std;
class TreeNode {
public:
    int value;
    TreeNode* leftPtr;
    TreeNode* rightPtr;
    TreeNode(int num) {
        value = num;
        leftPtr = rightPtr = nullptr;
    }
};
class BinaryTree {
private:
    TreeNode* rootPtr;
    void inorderHelper(TreeNode* currentNode) {
        if (!currentNode) return;
        inorderHelper(currentNode->leftPtr);
        cout << currentNode->value << " ";
        inorderHelper(currentNode->rightPtr);
    }
public:
    BinaryTree() {
        rootPtr = nullptr;
    }
    TreeNode* getRootNode() {
        return rootPtr;
    }
    void addRoot(int num) {
        if (!rootPtr)
            rootPtr = new TreeNode(num);
        else
            cout << "Root node already present!" << endl;
    }
    void addLeftChild(TreeNode* parentNode, int num) {
        if (!parentNode->leftPtr)
            parentNode->leftPtr = new TreeNode(num);
        else
            cout << "Left child node already present!" << endl;
    }
    void addRightChild(TreeNode* parentNode, int num) {
        if (!parentNode->rightPtr)
            parentNode->rightPtr = new TreeNode(num);
        else
            cout << "Right child node already present!" << endl;
    }
    void displayInorder() {
        inorderHelper(rootPtr);
    }
};
int main() {
    BinaryTree myTree;
    myTree.addRoot(10);
    TreeNode* rootNode = myTree.getRootNode();
    myTree.addLeftChild(rootNode, 5);
    myTree.addRightChild(rootNode, 15);
    myTree.addLeftChild(rootNode->leftPtr, 2);
    myTree.addRightChild(rootNode->leftPtr, 7);
    cout << "Inorder Display: ";
    myTree.displayInorder();
    cout << endl;
    return 0;
}
*/
