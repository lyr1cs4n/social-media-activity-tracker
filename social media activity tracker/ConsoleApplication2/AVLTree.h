#ifndef AVLTREE_H
#define AVLTREE_H


#include <iostream>
#include <unordered_map>
template <typename T>
class AVLTreeNode {
public:
    AVLTreeNode<T>* leftChild;
    AVLTreeNode<T>* rightChild;
    T data;
    int nodeHeight;

    AVLTreeNode() : leftChild(nullptr), rightChild(nullptr), nodeHeight(0) {}

    AVLTreeNode(T value) : leftChild(nullptr), rightChild(nullptr), nodeHeight(0), data(value) {}
};

template <typename T>
class AVLTree {
private:
    AVLTreeNode<T>* root;
    std::unordered_map<std::string, AVLTreeNode<T>*> nodeMap;

public:
    AVLTree();

    AVLTreeNode<T>* createNode(T data, std::string mapKey);

    int getNodeHeight(AVLTreeNode<T>* node);

    int calculateBalanceFactor(AVLTreeNode<T>* node);

    void updateNodeHeight(AVLTreeNode<T>* node);

    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* node);

    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* node);

    AVLTreeNode<T>* insertNode(AVLTreeNode<T>* node, T data, std::string mapKey);

    void insert(T data, std::string mapKey);

    AVLTreeNode<T>* findMinNode(AVLTreeNode<T>* node);

    AVLTreeNode<T>* deleteNode(AVLTreeNode<T>* node, T data, std::string mapKey);

    void deleteNode(T data, std::string mapKey);

    AVLTreeNode<T>* searchNode(std::string mapKey);

    void inOrderTraversal(AVLTreeNode<T>* currentNode);

    void inOrderTraversal();

    bool isEmpty();
};

using namespace std;
template<typename T>
AVLTree<T>::AVLTree() : root(nullptr)
{

}
template<typename T>
bool AVLTree<T>::isEmpty()
{
    return root == NULL;
}
template<typename T>
AVLTreeNode<T>* AVLTree<T>::createNode(T data, std::string mapKey)
{
    AVLTreeNode<T>* newNode = new AVLTreeNode<T>(data);
    nodeMap[mapKey] = newNode;
    return newNode;
}

template<typename T>
int AVLTree<T>::getNodeHeight(AVLTreeNode<T>* node)
{
    if (node == nullptr) {
        return 0;
    }
    return node->nodeHeight;
}

template<typename T>
int AVLTree<T>::calculateBalanceFactor(AVLTreeNode<T>* node)
{
    if (node == nullptr) {
        return 0;
    }
    return getNodeHeight(node->leftChild) - getNodeHeight(node->rightChild);
}

template<typename T>
void AVLTree<T>::updateNodeHeight(AVLTreeNode<T>* node)
{
    if (node != nullptr) {
        node->nodeHeight = 1 + max(getNodeHeight(node->leftChild), getNodeHeight(node->rightChild));
    }
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* node)
{
    AVLTreeNode<T>* x = node->leftChild;
    AVLTreeNode<T>* T2 = x->rightChild;

    x->rightChild = node;
    node->leftChild = T2;

    updateNodeHeight(node);
    updateNodeHeight(x);

    return x;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* node)
{
    AVLTreeNode<T>* y = node->rightChild;
    AVLTreeNode<T>* T2 = y->leftChild;

    y->leftChild = node;
    node->rightChild = T2;

    updateNodeHeight(node);
    updateNodeHeight(y);

    return y;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::insertNode(AVLTreeNode<T>* node, T data, std::string mapKey)
{
    if (node == nullptr) {
        return createNode(data, mapKey);
    }

    if (data < node->data) {
        node->leftChild = insertNode(node->leftChild, data, mapKey);
    }
    else if (data > node->data) {
        node->rightChild = insertNode(node->rightChild, data, mapKey);
    }
    else {
        return node;
    }

    updateNodeHeight(node);
    int balance = calculateBalanceFactor(node);

    if (balance > 1 && data < node->leftChild->data) {
        return rotateRight(node);
    }
    if (balance < -1 && data > node->rightChild->data) {
        return rotateLeft(node);
    }
    if (balance > 1 && data > node->leftChild->data) {
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }
    if (balance < -1 && data < node->rightChild->data) {
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    return node;
}

template<typename T>
void AVLTree<T>::insert(T data, std::string mapKey)
{
    root = insertNode(root, data, mapKey);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::findMinNode(AVLTreeNode<T>* node)
{
    while (node->rightChild) {
        node = node->rightChild;
    }
    return node;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::deleteNode(AVLTreeNode<T>* node, T data, std::string mapKey)
{
    if (node == nullptr) {
        return node;
    }

    if (data < node->data) {
        node->leftChild = deleteNode(node->leftChild, data, mapKey);
    }
    else if (node->data < data) {
        node->rightChild = deleteNode(node->rightChild, data, mapKey);
    }
    else {
        nodeMap.erase(mapKey);
        cout << "[*] "
            << "\033[33mDeleted Successfully. \033[0m" << endl;

        if (node->leftChild == nullptr && node->rightChild == nullptr) {
            delete node;
            return nullptr;
        }
        else if (node->leftChild == nullptr) {
            AVLTreeNode<T>* temp = node->rightChild;
            delete node;
            return temp;
        }
        else if (node->rightChild == nullptr) {
            AVLTreeNode<T>* temp = node->leftChild;
            delete node;
            return temp;
        }
        else {
            AVLTreeNode<T>* temp = findMinNode(node->rightChild);
            node->data = temp->data;
            node->rightChild = deleteNode(node->rightChild, temp->data, mapKey);
        }
    }

    if (node == nullptr) {
        return node;
    }

    updateNodeHeight(node);

    int balance = calculateBalanceFactor(node);

    if (balance > 1 && calculateBalanceFactor(node->leftChild) >= 0) {
        return rotateRight(node);
    }
    if (balance > 1 && calculateBalanceFactor(node->leftChild) < 0) {
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }
    if (balance < -1 && calculateBalanceFactor(node->rightChild) <= 0) {
        return rotateLeft(node);
    }
    if (balance < -1 && calculateBalanceFactor(node->rightChild) > 0) {
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    return node;
}

template<typename T>
void AVLTree<T>::deleteNode(T data, std::string mapKey)
{
    root = deleteNode(root, data, mapKey);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::searchNode(std::string mapKey)
{
    auto it = nodeMap.find(mapKey);
    return (it != nodeMap.end() ? it->second : nullptr);
}

template<typename T>
void AVLTree<T>::inOrderTraversal(AVLTreeNode<T>* currentNode)
{
    if (currentNode) {
        inOrderTraversal(currentNode->leftChild);
        currentNode->data.displayAll();
        inOrderTraversal(currentNode->rightChild);
    }
}

template<typename T>
void AVLTree<T>::inOrderTraversal()
{
    if (root == nullptr) {
        cout << endl;
        cout << "    Database is empty. " << endl;
    }
    inOrderTraversal(root);
}
#endif 