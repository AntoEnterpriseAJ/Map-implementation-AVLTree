#pragma once
template <typename T>
struct TreeNode
{
	T val;
	int height;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	TreeNode(T init = T{}, int h = 1, TreeNode* l = nullptr, TreeNode* r = nullptr, TreeNode* p = nullptr)
		: val{ init }, height{ h }, left{ l }, right{ r }, parent{ p }
	{}
};