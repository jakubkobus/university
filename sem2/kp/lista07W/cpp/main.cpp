#include <cstdio>
#include <string>
#include "BinaryTree.hpp"

int main() {
    BinaryTree<int> intTree;
    BinaryTree<double> doubleTree;
    BinaryTree<std::string> stringTree;

    intTree.insert(5);
    intTree.insert(3);
    intTree.insert(7);
    intTree.insert(4);
    intTree.insert(6);

    printf("Int tree:\n%s\n", intTree.draw().c_str());
    printf("Search 4: %s\n", intTree.search(4) ? "found" : "not found");
    printf("Delete 3: %s\n", intTree.remove(3) ? "deleted" : "not found");
    printf("Int tree after delete:\n%s\n", intTree.draw().c_str());

    doubleTree.insert(2.5);
    doubleTree.insert(1.1);
    doubleTree.insert(3.3);

    printf("Double tree:\n%s\n", doubleTree.draw().c_str());
    printf("Search 1.1: %s\n", doubleTree.search(1.1) ? "found" : "not found");
    printf("Delete 2.5: %s\n", doubleTree.remove(2.5) ? "deleted" : "not found");
    printf("Double tree after delete:\n%s\n", doubleTree.draw().c_str());

    stringTree.insert("apple");
    stringTree.insert("banana");
    stringTree.insert("pear");
    stringTree.insert("grape");

    printf("String tree:\n%s\n", stringTree.draw().c_str());
    printf("Search 'pear': %s\n", stringTree.search("pear") ? "found" : "not found");
    printf("Delete 'banana': %s\n", stringTree.remove("banana") ? "deleted" : "not found");
    printf("String tree after delete:\n%s\n", stringTree.draw().c_str());

    return 0;
}