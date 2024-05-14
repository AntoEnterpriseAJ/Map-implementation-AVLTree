#pragma once
#include "AVLTree.h"
#include "TreeNode.h"
#include <vector>

template <typename keyType, typename valType>
class Map
{
	using pair = std::pair<keyType, valType>;
	AVLTree<pair> m_tree;

	struct Comparator
	{
		bool operator ()(const pair& pair1, const pair& pair2) const
		{
			return pair1.first < pair2.first;
		}
	};
public:
	Map() = default;
	Map(const std::vector<pair>& initValues);
	Map(const Map& map2);
	~Map() = default;
	
	valType& operator [](const keyType& key);
	void clear();
	Map& operator =(const Map& map2);
};

template <typename keyType, typename valType>
valType& Map<keyType, valType>::operator [](const keyType& key)
{
	TreeNode<pair>* node = m_tree.find({ key, valType{} }, Comparator());
	if (node == nullptr)
	{
		m_tree.insert({ key, valType{} });
		node = m_tree.find({ key, valType{} }, Comparator());
	}
	
	return node->val.second;
}

template <typename keyType, typename valType>
Map<keyType, valType>& Map<keyType, valType>::operator =(const Map<keyType, valType>& map2)
{

}

template <typename keyType, typename valType>
void Map<keyType, valType>::clear()
{
	m_tree.clear();
}

template<typename keyType, typename valType>
Map<keyType, valType>::Map(const std::vector<pair>& initValues)
{
	for (const auto& pair : initValues)
	{
		m_tree.insert(pair);
	}
}