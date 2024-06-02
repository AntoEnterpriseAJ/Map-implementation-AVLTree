#pragma once
template <typename T>
struct TreeNode
{
	T data;
	int height;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	TreeNode(T init = T{}, int h = 1, TreeNode* l = nullptr, TreeNode* r = nullptr, TreeNode* p = nullptr)
		: data{ init }, height{ h }, left{ l }, right{ r }, parent{ p }
	{}
};