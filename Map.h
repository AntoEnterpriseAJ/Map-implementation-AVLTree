#pragma once
#include "AVLTree.h"
#include <vector>

template <typename keyType, typename valType>
class Map
{
	using pair = std::pair<keyType, valType>;
	AVLTree<pair> m_tree;
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
	for (int i = 0; i < initValues.size(); ++i)
	{
		TreeNode<pair> node = new TreeNode<pair>{ initValues[i] };
		m_tree.insert();
	}
}