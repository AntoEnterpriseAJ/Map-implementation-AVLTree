#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "TreeNode.h"

template <typename T>
class AVLTree
{
	static TreeNode<T>* m_sentinelNode;

	TreeNode<T>* m_root;

	void insertRepair(TreeNode<T>* node);
	void deleteRepair(TreeNode<T>* node);
	void rotateLeft(TreeNode<T>* node);
	void rotateRight(TreeNode<T>* node);
	void transplant(TreeNode<T>* z, TreeNode<T>* y);
	void print2DUtil(TreeNode<T>* root, int space) const;
public:
	AVLTree();
	~AVLTree();

	void insert(T key);
	TreeNode<T>* max(TreeNode<T>* root);
	TreeNode<T>* min(TreeNode<T>* root);
	TreeNode<T>* successor(TreeNode<T>* node);
	TreeNode<T>* predecessor(TreeNode<T>* node);
	TreeNode<T>* find(T key);
	void deleteNode(T Key);
	void erase(TreeNode<T>* node);
	void construct(const std::vector<T>& keys);
	void clear();

	TreeNode<T>* getRoot() const;
	bool empty() const;
	void printTree(int option) const;
	void print2D(TreeNode<T>* root) const;
	void printPreorder(TreeNode<T>* node) const;
	void printInorder(TreeNode<T>* node) const;
	void printPostorder(TreeNode<T>* node) const;
	void printBreadth() const;
};

template<typename T>
TreeNode<T>* AVLTree<T>::m_sentinelNode = new TreeNode<T>{};

template <typename T>
AVLTree<T>::AVLTree() : m_root{ m_sentinelNode }
{}

template <typename T>
AVLTree<T>::~AVLTree()
{
	clear();
	delete m_sentinelNode;
}

template<typename T>
TreeNode<T>* AVLTree<T>::getRoot() const { return m_root; }

template <typename T>
bool AVLTree<T>::empty() const
{
	return m_root == m_sentinelNode;
}

template <typename T>
void AVLTree<T>::insertRepair(TreeNode<T>* nodeParent)
{
	if (nodeParent == m_sentinelNode) return;

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

template <typename T>
void AVLTree<T>::deleteRepair(TreeNode<T>* node)
{
	if (node == m_sentinelNode) return;

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

template <typename T>
void AVLTree<T>::transplant(TreeNode<T>* z, TreeNode<T>* y)
{
	if (z->parent == m_sentinelNode)
	{
		m_root = y;
	}
	else if (z == z->parent->left)
	{
		z->parent->left = y;
	}
	else z->parent->right = y;

	if (y != m_sentinelNode)
	{
		y->parent = z->parent;
	}
}

template <typename T>
void AVLTree<T>::deleteNode(T key)
{
	TreeNode<T>* node = find(key);
	if (node == nullptr) return;

	// node has no children
	if (node->left == m_sentinelNode)
	{
		transplant(node, node->right);
		deleteRepair(node->parent);
	}
	else
	{
		if (node->right == m_sentinelNode)
		{
			transplant(node, node->left);
			deleteRepair(node->parent);
		}
		else // node has two children
		{
			TreeNode<T>* y = predecessor(node);
			TreeNode<T>* lastParentY = y->parent; // transplant will change y's parent
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

			//we can use this for successor:
			//TreeNode<T>* y = successor(node);
			//if (y->parent != node)
			//{
			//	transplant(y, y->right);
			//	y->right = node->right;
			//	y->right->parent = y;
			//}
			//transplant(node, y);
			//y->left = node->left;
			//y->left->parent = y;
			//y->height = 1 + std::max(y->left->height, y->right->height); // ? maybe
			//deleteRepair(y->parent);
		}
	}
	delete node;
}

template <typename T>
void AVLTree<T>::erase(TreeNode<T>* node)
{
	if (node == nullptr) return;

	// node has no children
	if (node->left == m_sentinelNode)
	{
		transplant(node, node->right);
		deleteRepair(node->parent);
	}
	else
	{
		if (node->right == m_sentinelNode)
		{
			transplant(node, node->left);
			deleteRepair(node->parent);
		}
		else // node has two children
		{
			TreeNode<T>* y = predecessor(node);
			TreeNode<T>* lastParentY = y->parent; // transplant will change y's parent
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

			//we can use this for successor:
			//TreeNode<T>* y = successor(node);
			//if (y->parent != node)
			//{
			//	transplant(y, y->right);
			//	y->right = node->right;
			//	y->right->parent = y;
			//}
			//transplant(node, y);
			//y->left = node->left;
			//y->left->parent = y;
			//y->height = 1 + std::max(y->left->height, y->right->height); // ? maybe
			//deleteRepair(y->parent);
		}
	}
	delete node;
}

template <typename T>
void AVLTree<T>::construct(const std::vector<T>& keys)
{
	for (int i = 0; i < keys.size(); ++i)
	{
		insert(keys[i]);
	}
}

template <typename T>
void AVLTree<T>::clear()
{
	if (m_root == m_sentinelNode) return;

	std::queue<TreeNode<T>*> q;
	q.push(m_root);

	while (!q.empty())
	{
		TreeNode<T>* current = q.front();
		q.pop();

		if (current->left != m_sentinelNode) q.push(current->left);
		if (current->right != m_sentinelNode) q.push(current->right);

		delete current;
	}

	m_root = m_sentinelNode;
}

template <typename T>
void AVLTree<T>::printPreorder(TreeNode<T>* node) const
{
	if (node != m_sentinelNode)
	{
		std::cout << node->val << " ";
		printPreorder(node->left);
		printPreorder(node->right);
	}
}

template <typename T>
void AVLTree<T>::printInorder(TreeNode<T>* node) const
{
	if (node != m_sentinelNode)
	{
		printInorder(node->left);
		std::cout << node->val << " ";
		printInorder(node->right);
	}
}

template <typename T>
void AVLTree<T>::printPostorder(TreeNode<T>* node) const
{
	if (node != m_sentinelNode)
	{
		printPostorder(node->left);
		printPostorder(node->right);
		std::cout << node->val << " ";
	}
}

template <typename T>
void AVLTree<T>::printBreadth() const
{
	if (m_root == m_sentinelNode) return;

	std::queue<TreeNode<T>*> q;
	q.push(m_root);

	while (!q.empty())
	{
		int size = q.size();
		for (int i = 0; i < size; ++i)
		{
			TreeNode<T>* current = q.front();
			q.pop();

			std::cout << current->val << " ";

			if (current->left != m_sentinelNode) q.push(current->left);
			if (current->right != m_sentinelNode) q.push(current->right);
		}
		std::cout << '\n';
	}
}

template <typename T>
void AVLTree<T>::printTree(int option) const
{
	switch (option)
	{
	case 1:
		printPreorder(m_root);
		break;
	case 2:
		printInorder(m_root);
		break;
	case 3:
		printPostorder(m_root);
		break;
	case 4:
		printBreadth();
		break;
	default:
		std::cout << "Invalid option\n(1)Preorder (2)Inorder (3)Postorder (4)Breadth\n";
		break;
	}
}


template <typename T>
TreeNode<T>* AVLTree<T>::find(T key)
{
	if (m_root == m_sentinelNode) return nullptr;

	TreeNode<T>* current = m_root;
	while (current != m_sentinelNode)
	{
		if (current->val == key) return current;

		if (key > current->val)
		{
			current = current->right;
		}
		else current = current->left;
	}

	return nullptr;
}

template <typename T>
TreeNode<T>* AVLTree<T>::max(TreeNode<T>* root)
{
	if (root == m_sentinelNode) return nullptr;

	while (root->right != m_sentinelNode)
	{
		root = root->right;
	}

	return root;
}

template<typename T>
TreeNode<T>* AVLTree<T>::min(TreeNode<T>* root)
{
	if (root == m_sentinelNode) return nullptr;

	while (root->left != m_sentinelNode)
	{
		root = root->left;
	}

	return root;
}

template <typename T>
TreeNode<T>* AVLTree<T>::successor(TreeNode<T>* node)
{
	if (node == m_sentinelNode) throw std::string{ "no successor" };

	if (node->right != m_sentinelNode)
	{
		TreeNode<T>* current = node->right;
		while (current->left != m_sentinelNode)
		{
			current = current->left;
		}

		return current;
	}

	TreeNode<T>* p = node->parent;
	while (p != m_sentinelNode && p->right == node)
	{
		node = p;
		p = node->parent;
	}

	if (p == m_sentinelNode) throw std::string{ "no successor" };

	return p;
}

template <typename T>
TreeNode<T>* AVLTree<T>::predecessor(TreeNode<T>* node)
{
	if (node == m_sentinelNode) throw std::string{ "no predecessor" };

	if (node->left != m_sentinelNode)
	{
		TreeNode<T>* current = node->left;
		while (current->right != m_sentinelNode)
		{
			current = current->right;
		}

		return current;
	}

	TreeNode<T>* p = node->parent;
	while (p != m_sentinelNode && p->left == node)
	{
		node = p;
		p = node->parent;
	}

	if (p == m_sentinelNode) throw std::string{ "no predecessor" };

	return p;
}

template <typename T>
void AVLTree<T>::rotateRight(TreeNode<T>* node)
{
	if (node->left == m_sentinelNode) return;
	TreeNode<T>* newRoot = node->left;

	node->left = newRoot->right;
	if (newRoot->right != m_sentinelNode)
	{
		newRoot->right->parent = node;
	}

	newRoot->right = node;
	newRoot->parent = node->parent;

	if (node->parent == m_sentinelNode)
	{
		m_root = newRoot;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = newRoot;
	}
	else
	{
		node->parent->right = newRoot;
	}

	node->parent = newRoot;

	node->height = 1 + std::max(node->left->height, node->right->height);
	newRoot->height = 1 + std::max(newRoot->left->height, newRoot->right->height);
}

template <typename T>
void AVLTree<T>::rotateLeft(TreeNode<T>* node)
{
	if (node->right == m_sentinelNode) return;
	TreeNode<T>* newRoot = node->right;

	node->right = newRoot->left;
	if (newRoot->left != m_sentinelNode)
	{
		newRoot->left->parent = node;
	}

	newRoot->left = node;
	newRoot->parent = node->parent;

	if (node->parent == m_sentinelNode)
	{
		m_root = newRoot;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = newRoot;
	}
	else
	{
		node->parent->right = newRoot;
	}

	node->parent = newRoot;

	node->height = 1 + std::max(node->left->height, node->right->height);
	newRoot->height = 1 + std::max(newRoot->left->height, newRoot->right->height);
}


template <typename T>
void AVLTree<T>::insert(T key)
{
	if (m_root == m_sentinelNode)
	{
		m_root = new TreeNode<T>{ key, 1, m_sentinelNode, m_sentinelNode, m_sentinelNode };
		return;
	}

	TreeNode<T>* current = m_root;
	TreeNode<T>* prev = nullptr;
	while (current != m_sentinelNode)
	{
		if (current->val == key) return;

		prev = current;
		if (key > current->val)
		{
			current = current->right;
		}
		else current = current->left;
	}

	if (key > prev->val)
	{
		prev->right = new TreeNode<T>{ key, 1, m_sentinelNode, m_sentinelNode, prev };
	}
	else
	{
		prev->left = new TreeNode<T>{ key, 1, m_sentinelNode, m_sentinelNode, prev };
	}

	insertRepair(prev);
}

template <typename T>
void AVLTree<T>::print2DUtil(TreeNode<T>* root, int space) const
{
	if (root == m_sentinelNode)
		return;

	space += 10;

	print2DUtil(root->right, space);

	std::cout << "\n";
	for (int i = 10; i < space; i++)
		std::cout << " ";
	std::cout << root->val << "\n";

	print2DUtil(root->left, space);
}

template <typename T>
void AVLTree<T>::print2D(TreeNode<T>* root) const
{
	print2DUtil(root, 0);
}