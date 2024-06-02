#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "TreeNode.h"

template <typename Key, typename Value>
class Map
{
public:
    void insert(const std::pair<Key, Value>& pair);
    void erase(const Key& key);
    void construct(const std::vector<std::pair<Key, Value>>& keys);
    void clear();
    void deleteNode(TreeNode<std::pair<Key, Value>>* node);

    bool contains(const Key& key) const;
    bool empty() const;
    void printTree(int option) const;
    void print2D(TreeNode<std::pair<Key, Value>>* root) const;
    void printPreorder(TreeNode<std::pair<Key, Value>>* node) const;
    void printInorder(TreeNode<std::pair<Key, Value>>* node) const;
    void printPostorder(TreeNode<std::pair<Key, Value>>* node) const;
    void printBreadth() const;

    class Iterator 
    {
    public:
        using value_type = std::pair<Key, Value>;
        using pointer = value_type*;
        using reference = value_type&;


        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        reference operator*() const { return m_node->data; }
        pointer operator->() const { return &(m_node->data); }
        
        bool operator==(const Iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

        Iterator(TreeNode<std::pair<Key, Value>>* node) : m_node(node) {}
        friend class Map;
    private:
        TreeNode<std::pair<Key, Value>>* m_node;
        Map* map;

        Iterator(TreeNode<std::pair<Key, Value>>* node, Map* map) : m_node(node), map(map) {}
    };

    Iterator begin() {
        return Iterator(min(m_root), this);
    }

    Iterator end() {
        return Iterator(s_sentinelNode, this);
    }

    Map();
    ~Map();

private:
    static TreeNode<std::pair<Key, Value>>* s_sentinelNode;

    TreeNode<std::pair<Key, Value>>* m_root;

    void insertRepair(TreeNode<std::pair<Key, Value>>* node);
    void deleteRepair(TreeNode<std::pair<Key, Value>>* node);
    void rotateLeft(TreeNode<std::pair<Key, Value>>* node);
    void rotateRight(TreeNode<std::pair<Key, Value>>* node);
    void transplant(TreeNode<std::pair<Key, Value>>* z, TreeNode<std::pair<Key, Value>>* y);
    void print2DUtil(TreeNode<std::pair<Key, Value>>* root, int space) const;

    TreeNode<std::pair<Key, Value>>* find(const Key& key) const;
    TreeNode<std::pair<Key, Value>>* max(TreeNode<std::pair<Key, Value>>* root) const;
    TreeNode<std::pair<Key, Value>>* min(TreeNode<std::pair<Key, Value>>* root) const;
    TreeNode<std::pair<Key, Value>>* successor(TreeNode<std::pair<Key, Value>>* node) const;
    TreeNode<std::pair<Key, Value>>* predecessor(TreeNode<std::pair<Key, Value>>* node) const;
};

template<typename Key, typename Value>
TreeNode<std::pair<Key, Value>>* Map<Key, Value>::s_sentinelNode = new TreeNode<std::pair<Key, Value>>{ {Key{}, Value{}}, 0 };

template <typename Key, typename Value>
Map<Key, Value>::Map() : m_root{ s_sentinelNode }
{}

template <typename Key, typename Value>
Map<Key, Value>::~Map()
{
    clear();
    delete s_sentinelNode;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator& Map<Key, Value>::Iterator::operator++()
{
	m_node = map->successor(m_node);
	return *this;
}

template<typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename Key, typename Value>
typename Map<Key,Value>::Iterator& Map<Key, Value>::Iterator::operator--()
{
    m_node = map->predecessor(m_node);
    return *this;
}

template<typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::Iterator::operator--(int)
{
    Iterator tmp = *this;
    --(*this);
    return tmp;
}


template<typename Key, typename Value>
bool Map<Key, Value>::contains(const Key& key) const
{
    return find(key) != s_sentinelNode;
}

template <typename Key, typename Value>
bool Map<Key, Value>::empty() const
{
    return m_root == s_sentinelNode;
}

template <typename Key, typename Value>
void Map<Key, Value>::insertRepair(TreeNode<std::pair<Key, Value>>* nodeParent)
{
    if (nodeParent == s_sentinelNode) return;

    int balanceFactor = nodeParent->right->height - nodeParent->left->height;

    if (balanceFactor == 0) return;

    nodeParent->height++;
    if (balanceFactor == -2)
    {
        int leftBalanceFactor = nodeParent->left->right->height - nodeParent->left->left->height;

        if (leftBalanceFactor == -1)
        {
            rotateRight(nodeParent);
        }
        else if (leftBalanceFactor == 1)
        {
            rotateLeft(nodeParent->left);
            rotateRight(nodeParent);
        }
    }

    if (balanceFactor == 2)
    {
        int rightBalanceFactor = nodeParent->right->right->height - nodeParent->right->left->height;

        if (rightBalanceFactor == -1)
        {
            rotateRight(nodeParent->right);
            rotateLeft(nodeParent);
        }
        else if (rightBalanceFactor == 1)
        {
            rotateLeft(nodeParent);
        }
    }

    insertRepair(nodeParent->parent);
}

template <typename Key, typename Value>
void Map<Key, Value>::deleteRepair(TreeNode<std::pair<Key, Value>>* node)
{
    if (node == s_sentinelNode) return;

    int balanceFactor = node->right->height - node->left->height;

    if (balanceFactor == -1 || balanceFactor == 1) return;

    node->height = 1 + std::max(node->left->height, node->right->height);
    if (balanceFactor == 0)
    {
        deleteRepair(node->parent);
    }

    if (balanceFactor == -2)
    {
        int leftBalanceFactor = node->left->right->height - node->left->left->height;

        if (leftBalanceFactor == 0)
        {
            rotateRight(node);
            return;
        }

        if (leftBalanceFactor == -1)
        {
            rotateRight(node);
            deleteRepair(node->parent);
        }

        if (leftBalanceFactor == 1)
        {
            rotateLeft(node->left);
            rotateRight(node);
            deleteRepair(node->parent);
        }
    }

    if (balanceFactor == 2)
    {
        int rightBalanceFactor = node->right->right->height - node->right->left->height;

        if (rightBalanceFactor == 0)
        {
            rotateLeft(node);
            return;
        }

        if (rightBalanceFactor == 1)
        {
            rotateLeft(node);
            deleteRepair(node->parent);
        }

        if (rightBalanceFactor == -1)
        {
            rotateRight(node->right);
            rotateLeft(node);
            deleteRepair(node->parent);
        }
    }

    return;
}

template <typename Key, typename Value>
void Map<Key, Value>::transplant(TreeNode<std::pair<Key, Value>>* z, TreeNode<std::pair<Key, Value>>* y)
{
    if (z->parent == s_sentinelNode)
    {
        m_root = y;
    }
    else if (z == z->parent->left)
    {
        z->parent->left = y;
    }
    else z->parent->right = y;

    if (y != s_sentinelNode)
    {
        y->parent = z->parent;
    }
}

template <typename Key, typename Value>
void Map<Key, Value>::erase(const Key& key)
{
    TreeNode<std::pair<Key, Value>>* node = find(key);
    if (node == nullptr) return;

    // node has no children
    if (node->left == s_sentinelNode)
    {
        transplant(node, node->right);
        deleteRepair(node->parent);
    }
    else
    {
        if (node->right == s_sentinelNode)
        {
            transplant(node, node->left);
            deleteRepair(node->parent);
        }
        else // node has two children
        {
            TreeNode<std::pair<Key, Value>>* y = predecessor(node);
            TreeNode<std::pair<Key, Value>>* lastParentY = y->parent; // transplant will change y's parent
            if (y->parent != node)
            {
                transplant(y, y->left);
                y->left = node->left;
                y->left->parent = y;
            }
            transplant(node, y);
            y->right = node->right;
            y->right->parent = y;
            y->height = 1 + std::max(y->left->height, y->right->height);
            deleteRepair(lastParentY);
        }
    }
    delete node;
}

template <typename Key, typename Value>
void Map<Key, Value>::deleteNode(TreeNode<std::pair<Key, Value>>* node)
{
    if (node == nullptr) return;

    // node has no children
    if (node->left == s_sentinelNode)
    {
        transplant(node, node->right);
        deleteRepair(node->parent);
    }
    else
    {
        if (node->right == s_sentinelNode)
        {
            transplant(node, node->left);
            deleteRepair(node->parent);
        }
        else // node has two children
        {
            TreeNode<std::pair<Key, Value>>* y = predecessor(node);
            TreeNode<std::pair<Key, Value>>* lastParentY = y->parent; // transplant will change y's parent
            if (y->parent != node)
            {
                transplant(y, y->left);
                y->left = node->left;
                y->left->parent = y;
            }
            transplant(node, y);
            y->right = node->right;
            y->right->parent = y;
            y->height = 1 + std::max(y->left->height, y->right->height);
            deleteRepair(lastParentY);
        }
    }
    delete node;
}

template <typename Key, typename Value>
void Map<Key, Value>::insert(const std::pair<Key, Value>& pair)
{
    const Key& key = pair.first;
    const Value& value = pair.second;

    if (m_root == s_sentinelNode)
    {
        m_root = new TreeNode<std::pair<Key, Value>>{ {key, value}, 1, s_sentinelNode, s_sentinelNode, s_sentinelNode };
        return;
    }

    TreeNode<std::pair<Key, Value>>* node = m_root;
    TreeNode<std::pair<Key, Value>>* nodeParent = nullptr;

    while (node != s_sentinelNode)
    {
        nodeParent = node;
        if (key == node->data.first) return; // key already present
        node = (key < node->data.first) ? node->left : node->right;
    }

    TreeNode<std::pair<Key, Value>>* newNode = new TreeNode<std::pair<Key, Value>>{ {key, value}, 1, s_sentinelNode, s_sentinelNode, nodeParent };

    if (key < nodeParent->data.first)
    {
        nodeParent->left = newNode;
    }
    else
    {
        nodeParent->right = newNode;
    }

    insertRepair(nodeParent);
}

template <typename Key, typename Value>
TreeNode<std::pair<Key, Value>>* Map<Key, Value>::max(TreeNode<std::pair<Key, Value>>* root) const
{
    if (root == s_sentinelNode) return nullptr;

    TreeNode<std::pair<Key, Value>>* node = root;

    while (node->right != s_sentinelNode)
    {
        node = node->right;
    }
    return node;
}

template <typename Key, typename Value>
TreeNode<std::pair<Key, Value>>* Map<Key, Value>::min(TreeNode<std::pair<Key, Value>>* root) const
{
    if (root == s_sentinelNode) return nullptr;

    TreeNode<std::pair<Key, Value>>* node = root;

    while (node->left != s_sentinelNode)
    {
        node = node->left;
    }
    return node;
}

template <typename Key, typename Value>
TreeNode<std::pair<Key, Value>>* Map<Key, Value>::successor(TreeNode<std::pair<Key, Value>>* node) const
{
    if (node->right != s_sentinelNode)
    {
        return min(node->right);
    }
    TreeNode<std::pair<Key, Value>>* nodeParent = node->parent;
    while (nodeParent != s_sentinelNode && node == nodeParent->right)
    {
        node = nodeParent;
        nodeParent = nodeParent->parent;
    }
    return nodeParent;
}

template <typename Key, typename Value>
TreeNode<std::pair<Key, Value>>* Map<Key, Value>::predecessor(TreeNode<std::pair<Key, Value>>* node) const
{
    if (node->left != s_sentinelNode)
    {
        return max(node->left);
    }
    TreeNode<std::pair<Key, Value>>* nodeParent = node->parent;
    while (nodeParent != s_sentinelNode && node == nodeParent->left)
    {
        node = nodeParent;
        nodeParent = nodeParent->parent;
    }
    return nodeParent;
}

template <typename Key, typename Value>
TreeNode<std::pair<Key, Value>>* Map<Key, Value>::find(const Key& key) const
{
    TreeNode<std::pair<Key, Value>>* node = m_root;
    while (node != s_sentinelNode && node->data.first != key)
    {
        node = (key < node->data.first) ? node->left : node->right;
    }
    return (node != s_sentinelNode) ? node : s_sentinelNode;
}

template <typename Key, typename Value>
void Map<Key, Value>::construct(const std::vector<std::pair<Key, Value>>& keys)
{
    clear();
    for (const auto& key_value : keys)
    {
        insert(key_value.first, key_value.second);
    }
}

template <typename Key, typename Value>
void Map<Key, Value>::clear()
{
    if (m_root == s_sentinelNode) return;

    std::queue<TreeNode<std::pair<Key, Value>>*> nodeQueue;
    nodeQueue.push(m_root);
    while (!nodeQueue.empty())
    {
        TreeNode<std::pair<Key, Value>>* node = nodeQueue.front();
        nodeQueue.pop();
        if (node->left != s_sentinelNode)
        {
            nodeQueue.push(node->left);
        }
        if (node->right != s_sentinelNode)
        {
            nodeQueue.push(node->right);
        }
        delete node;
    }
    m_root = s_sentinelNode;
}

template <typename Key, typename Value>
void Map<Key, Value>::rotateLeft(TreeNode<std::pair<Key, Value>>* node)
{
    TreeNode<std::pair<Key, Value>>* y = node->right;
    node->right = y->left;
    if (y->left != s_sentinelNode)
    {
        y->left->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == s_sentinelNode)
    {
        m_root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
    node->height = 1 + std::max(node->left->height, node->right->height);
    y->height = 1 + std::max(y->left->height, y->right->height);
}

template <typename Key, typename Value>
void Map<Key, Value>::rotateRight(TreeNode<std::pair<Key, Value>>* node)
{
    TreeNode<std::pair<Key, Value>>* y = node->left;
    node->left = y->right;
    if (y->right != s_sentinelNode)
    {
        y->right->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == s_sentinelNode)
    {
        m_root = y;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = y;
    }
    else
    {
        node->parent->left = y;
    }
    y->right = node;
    node->parent = y;
    node->height = 1 + std::max(node->left->height, node->right->height);
    y->height = 1 + std::max(y->left->height, y->right->height);
}

template <typename Key, typename Value>
void Map<Key, Value>::printTree(int option) const
{
    switch (option)
    {
    case 1:
        std::cout << "Preorder: ";
        printPreorder(m_root);
        break;
    case 2:
        std::cout << "Inorder: ";
        printInorder(m_root);
        break;
    case 3:
        std::cout << "Postorder: ";
        printPostorder(m_root);
        break;
    case 4:
        std::cout << "Breadth: ";
        printBreadth();
        break;
    case 5:
        std::cout << "Print2D: ";
        print2D(m_root);
        break;
    default:
        std::cout << "Please select a valid option: \n"
            << "1 - Preorder\n"
            << "2 - Inorder\n"
            << "3 - Postorder\n"
            << "4 - Breadth\n"
            << "5 - Print2D\n";
    }
    std::cout << "\n";
}

template <typename Key, typename Value>
void Map<Key, Value>::print2DUtil(TreeNode<std::pair<Key, Value>>* root, int space) const
{
    if (root == s_sentinelNode)
        return;

    space += 10;

    print2DUtil(root->right, space);

    std::cout << std::endl;
    for (int i = 10; i < space; i++)
        std::cout << " ";
    std::cout << root->data.first << "\n";

    print2DUtil(root->left, space);
}

template <typename Key, typename Value>
void Map<Key, Value>::print2D(TreeNode<std::pair<Key, Value>>* root) const
{
    print2DUtil(root, 0);
}

template <typename Key, typename Value>
void Map<Key, Value>::printPreorder(TreeNode<std::pair<Key, Value>>* node) const
{
    if (node == s_sentinelNode) return;

    std::cout << node->data.first << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

template <typename Key, typename Value>
void Map<Key, Value>::printInorder(TreeNode<std::pair<Key, Value>>* node) const
{
    if (node == s_sentinelNode) return;

    printInorder(node->left);
    std::cout << node->data.first << " ";
    printInorder(node->right);
}

template <typename Key, typename Value>
void Map<Key, Value>::printPostorder(TreeNode<std::pair<Key, Value>>* node) const
{
    if (node == s_sentinelNode) return;

    printPostorder(node->left);
    printPostorder(node->right);
    std::cout << node->data.first << " ";
}

template <typename Key, typename Value>
void Map<Key, Value>::printBreadth() const
{
    if (m_root == s_sentinelNode) return;

    std::queue<TreeNode<std::pair<Key, Value>>*> nodeQueue;
    nodeQueue.push(m_root);
    while (!nodeQueue.empty())
    {
        TreeNode<std::pair<Key, Value>>* node = nodeQueue.front();
        nodeQueue.pop();
        std::cout << node->data.first << " ";
        if (node->left != s_sentinelNode)
        {
            nodeQueue.push(node->left);
        }
        if (node->right != s_sentinelNode)
        {
            nodeQueue.push(node->right);
        }
    }
}
