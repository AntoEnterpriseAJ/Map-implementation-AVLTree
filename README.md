# Map Implementation using AVL Tree

This project is a custom implementation of a `Map` data structure using an AVL Tree. By default, maps often use a Red-Black Tree due to its efficient balancing properties. However, this implementation opts for an AVL Tree, which provides stricter balancing at the cost of potentially more rotations.

## Overview

### Files
- **Map.h**: Contains the implementation of the `Map` class, which includes methods for inserting, deleting, and searching for key-value pairs, as well as various tree traversal methods.
- **TreeNode.h**: Contains the definition of the `TreeNode` class, which represents each node in the AVL Tree.
- **main.cpp**: Example usage of the `Map` class, with a menu-driven interface to interact with the map.

## Class Details

### Map Class
The `Map` class is a template class that supports any data types for the keys and values. The primary methods and their functionalities are:

- **insert(const std::pair<Key, Value>& pair)**: Inserts a new key-value pair into the map.
- **erase(const Key& key)**: Removes the key-value pair identified by the key.
- **contains(const Key& key) const**: Checks if a key exists in the map.
- **empty() const**: Checks if the map is empty.
- **clear()**: Removes all elements from the map.
- **printTree(int option) const**: Prints the tree using different traversal methods: 1 - preorder, 2 - inorder, 3 - postorder, 4 - breadth, 5 - print2D
- **Print2D is used for a more visual approach

### Print2D
![image](https://github.com/AntoEnterpriseAJ/Map-implementation-AVLTree/assets/152036671/52c334f9-68e4-4706-be1e-aabfba5f850f)

### Iterator Class
The `Map` class includes an `Iterator` class to allow users to traverse the map using iterators, similar to standard C++ containers.
```cpp
for (auto it = map.begin(); it != map.end(); ++it) {
    std::cout << it->first << " " << it->second << "\n";
}
```

### AVL Tree Specific Methods
- **rotateLeft(TreeNode<std::pair<Key, Value>>* node)**: Performs a left rotation on a given node.
- **rotateRight(TreeNode<std::pair<Key, Value>>* node)**: Performs a right rotation on a given node.
- **insertRepair(TreeNode<std::pair<Key, Value>>* node)**: Repairs the tree after an insertion to maintain AVL balance.
- **deleteRepair(TreeNode<std::pair<Key, Value>>* node)**: Repairs the tree after a deletion to maintain AVL balance.

## Contributing
This project was created for study purposes. Contributions are welcome but not actively sought.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
