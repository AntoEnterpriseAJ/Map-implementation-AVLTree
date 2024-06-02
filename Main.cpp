#include <iostream>
#include <string>
#include <vector>
#include "Map.h" 

void displayMenu()
{
    std::cout << "\n===== Menu =====\n"
        << "1. Insert key-value pair\n"
        << "2. Delete key\n"
        << "3. Find key\n"
        << "4. Print tree (Preorder)\n"
        << "5. Print tree (Inorder)\n"
        << "6. Print tree (Postorder)\n"
        << "7. Print tree (Breadth-first)\n"
        << "8. Print tree (2D)\n"
        << "9. Clear tree\n"
        << "10. Exit\n"
        << "================\n";
}

int main()
{
    Map<int, std::string> map;

    int choice;
    do
    {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int key;
            std::string value;
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Enter value: ";
            std::cin.ignore();
            std::getline(std::cin, value);
            map.insert({ key, value });
            break;
        }
        case 2:
        {
            int keyToDelete;
            std::cout << "Enter key to delete: ";
            std::cin >> keyToDelete;
            map.erase(keyToDelete);
            break;
        }
        case 3:
        {
            int keyToFind;
            std::cout << "Enter key to find: ";
            std::cin >> keyToFind;
            TreeNode<std::pair<int, std::string>>* foundNode = map.find(keyToFind);
            if (foundNode != nullptr)
            {
                std::cout << "Key " << keyToFind << " found with value: " << foundNode->data.second << std::endl;
            }
            else
            {
                std::cout << "Key " << keyToFind << " not found in the map." << std::endl;
            }
            break;
        }
        case 4:
            std::cout << "Preorder traversal: ";
            map.printTree(1); // 1 for preorder
            std::cout << std::endl;
            break;
        case 5:
            std::cout << "Inorder traversal: ";
            map.printTree(2); // 2 for inorder
            std::cout << std::endl;
            break;
        case 6:
            std::cout << "Postorder traversal: ";
            map.printTree(3); // 3 for postorder
            std::cout << std::endl;
            break;
        case 7:
            std::cout << "Breadth-first traversal: " << std::endl;
            map.printTree(4); // 4 for breadth-first
            std::cout << std::endl;
            break;
        case 8:
            std::cout << "2D representation of the tree: " << std::endl;
            map.printTree(5); // 5 for 2D
            break;
        case 9:
            map.clear();
            std::cout << "Tree cleared." << std::endl;
            break;
        case 10:
            std::cout << "Exiting program..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice! Please enter a number between 1 and 10." << std::endl;
            break;
        }

    } while (choice != 10);


    std::cout << "\niterators:\n";
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        std::cout << it->first << " " << it->second << "\n";
    }

    return 0;
}
