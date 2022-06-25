#pragma once
#include "trie.h"
#include <queue>

template<class T>
inline Trie<T>::~Trie(){
	deleteNode(root_);
}

template<class T>
inline Trie<T>::Trie(const Trie& other){
	cloneRoot(other);
}

template<class T>
inline Trie<T>& Trie<T>::operator=(const Trie& other){
	Trie tempTrie;
	tempTrie.cloneRoot(other);
	deleteNode(root_);
	root_ = tempTrie.root_;
	tempTrie.root_ = nullptr;
}

template<class T>
inline void Trie<T>::insert(const std::string key, const T& new_value){
	Node* iterator = findNode(key);
	if (iterator) { //if the whole key is contained
		iterator->value = new_value;
		return;
	}
	iterator = root_;
	size_t i = 0;
	for (; i < key.length(); i++) { //check if a part of the key is contained
		bool char_found = false;
		for (size_t j = 0; j < iterator->children.size(); j++) {
			if (iterator->children[j]->c == key[i]) {
				char_found = true;
				iterator = iterator->children[j];
				break;
			}
		}
		if (!char_found) break;
	}
	for (; i < key.length(); i++) { //for every character of the key that is NOT contained in the trie
		Node* new_node = new Node(key[i]);
		addNode(iterator, new_node);
		iterator = new_node;
	}
	iterator->value = new_value;
	iterator->end_node = true;
	keys_.push_back(key);
}

template<class T>
inline bool Trie<T>::find(const std::string key, T& value) const {
	Node* iterator = findNode(key);
	if (!iterator || !iterator->end_node) {
		return false;
	}
	value = iterator->value;
	return true; 
}

template<class T>
inline void Trie<T>::remove(const std::string key){
	Node* iterator = findNode(key);
	if (!iterator || !iterator->end_node) return; //not a key
	if (iterator->children.size()) { //part of different key
		iterator->end_node = false;
		return;
	}
	while (iterator->parent->children.size() == 1 && !iterator->parent->end_node && iterator->parent != root_) iterator = iterator->parent;
	Node* common_prefix_node = iterator->parent; //first node that is part of other keys
	for (size_t i = 0; i < common_prefix_node->children.size(); i++) {
		if (common_prefix_node->children[i]->c ==  iterator->c) {
			common_prefix_node->children.erase(common_prefix_node->children.begin() + i);
		}
	}
	deleteNode(iterator);

	for (size_t i = 0; i < keys_.size(); i++) {
		if (keys_[i] == key) {
			keys_.erase(keys_.begin() + i);
			break;
		}
	}
}

template<class T>
inline typename Trie<T>::Node* Trie<T>::findNode(const std::string key) const {
	Node* iterator = root_;
	for (size_t i = 0; i < key.length(); i++) {
		bool char_found = false;
		for (size_t j = 0; j < iterator->children.size(); j++) {
			if (iterator->children[j]->c == key[i]) {
				char_found = true;
				iterator = iterator->children[j];
				break;
			}
		}
		if (!char_found) return nullptr;
	}
	return iterator;
}

template<class T>
inline void Trie<T>::deleteNode(Node* node){
	if (!node) return;
	for (size_t i = 0; i < node->children.size(); i++) {
		deleteNode(node->children[i]);
	}
	delete node;
}

//Used in the copy constructor and operator =
template<class T>
inline void Trie<T>::cloneRoot(const Trie& other){
	if (other.root_) {
		root_ = new Node(other.root_->value);
		std::queue<Node*> other_bfs_queue, copy_bfs_queue;
		other_bfs_queue.push(other.root_);
		copy_bfs_queue.push(root_);
		while (!other_bfs_queue.empty()) {
			Node* node_other = other_bfs_queue.front(), * node_copy = copy_bfs_queue.front();
			other_bfs_queue.pop();
			copy_bfs_queue.pop();
			for (size_t i = 0; i < node_other->children.size(); i++) {
				Node* new_node = new Node(node_other->children[i]->c);
				new_node->value = node_other->children[i]->value;
				new_node->end_node = node_other->children[i]->end_node;
				addNode(node_copy, new_node);
				other_bfs_queue.push(node_other->children[i]);
				copy_bfs_queue.push(new_node);
			}
		}

	}
	else root_ = nullptr;
}

template<class T>
inline void Trie<T>::addNode(Node* parent_node, Node* child){
	child->parent = parent_node;
	parent_node->children.push_back(child);
}