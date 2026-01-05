#ifndef _ST_HPP_
#define _ST_HPP_

#include <utility>
#include <vector>
#include <iostream>
#include <functional>

#include "RBT.hpp"
#include "RBTPrint.hpp"

/*
 Name: Chad Bynum
 Email: ccbynum@crimson.ua.edu
 Course Section: Fall 2025 CS 201
 Homework #: 2
 Serial Number: 49
*/

template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
	typedef RBTNode<Key, Type>* iterator;

	// Constructors
	// constant
	ST() { 
		nodeCount = 0;
	}; 

	// Destructor
	// linear in the size of the ST
	~ST(){
	};

	// access or insert specifies element
	// inserts if the key is not present and returns a reference to
	// the value corresponding to that key
	// O(LogN), N size of ST
	Type& operator[](const Key& key) {
		RBTNode<Key, Type>* node = this->Search(key);
		if (node) {
			return node->value;
		}
		// insert default-constructed value
		RBTNode<Key, Type>* newNode = this->Insert(key, Type());
		nodeCount++;
		return newNode->value;
	}; 

	// insert a (key, value) pair, if the key already exists
	// set the new value to the existing key
	// O(LogN), N size of ST
	void insert(const Key& key, const Type& value) {
		RBTNode<Key, Type>* node = this->Search(key);
		if (node) {
			node->value = value;
		}
		else {
			this->Insert(key, value);
			nodeCount++;
		}
	};

	// remove element at the given position
	// amortized constant
	void remove(iterator position) {
		if (position == nullptr) return;
		this->RemoveNode(position);
		if (nodeCount > 0) nodeCount--;
	};

        // remove element with keyvalue key and 
	// return number of elements removed (either 0 or 1)
	// O(logN), N size of ST
	std::size_t remove(const Key& key) {
		bool removed = this->Remove(key);
		if (removed) {
			if (nodeCount > 0) nodeCount--;
			return 1;
		}
		return 0;
	};  

	// removes all elements from the ST, after this size() returns 0
	// linear in the size of the ST
	void clear() {
		this->DeleteTree(this->root);
		this->root = nullptr;
		nodeCount = 0;
	}; 

	// checks if ST has no elements; true is empty, false otherwise
	// constant
	bool empty() const {
		return nodeCount == 0;
	}; 

	// returns number of elements in ST
	// constant
	std::size_t size() const {	
		return nodeCount;
	}; 

	// returns number of elements that match keyvalue key
	// value returned is 0 or 1 since keys are unique
	// O(LogN), N size of ST
	std::size_t count(const Key& key) {
		return this->Search(key) ? 1 : 0;
	}; 

	// find an element with keyvalue key and return 
	// the iterator to the element found, nullptr if not found
	// O(LogN), N size of ST
	iterator find(const Key& key) {
		return this->Search(key);
	};

	// check if key exists in ST
	// O(LogN), N size of ST
	bool contains(const Key& key) {
		return this->Search(key) != nullptr;
	};

        // return contents of ST as a vector of (key,value) pairs
        // O(N), N size of ST
        std::vector<std::pair<Key, Type> > toVector() {
            std::vector<std::pair<Key, Type> > out;
            // inorder traversal
            std::function<void(RBTNode<Key,Type>*)> inorder = [&](RBTNode<Key,Type>* node) {
                if (!node) return;
                inorder(node->left);
                out.emplace_back(node->key, node->value);
                inorder(node->right);
            };
            inorder(this->root);
            return out;
        };

	// print the symbol table as Red-Black Tree
	// O(N), N size of ST
	void displayTree() {
		std::cout << RBTPrint<Key,Type>::TreeToString(RedBlackTree<Key,Type>::root) << std::endl;
	};

	// print the symbol table in sorted order
	// O(N), N size of ST
	void display() {
		// print inorder (sorted by key)
		std::function<void(RBTNode<Key,Type>*)> inorder = [&](RBTNode<Key,Type>* node) {
			if (!node) return;
			inorder(node->left);
			std::cout << node->key << ": " << node->value << std::endl;
			inorder(node->right);
		};
		inorder(this->root);
	};

private:
	std::size_t nodeCount;

};

#endif

