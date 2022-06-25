#pragma once
#include <string>
#include <vector>

//TODO: implement proper Trie
//TODO: change name of the class - Search tree?

//Limitation - class T must have a default constructor
template <class T>
class Trie{
public:
	Trie() : root_(new Node(' ')) {}
	~Trie();
	Trie(const Trie& other);
	Trie& operator=(const Trie& other);

	std::vector<std::string> get_keys() const { return keys_; }
	bool find(const std::string key, T& value) const;
	void insert(const std::string key, const T& new_value);
	void remove(const std::string key);

private:

	struct Node {
		Node(char character) : value(T()), c(character), end_node(false), parent(nullptr) {}
		Node(const T& value, char character) : value(value), c(character), end_node(true), parent(nullptr) {}

		T value;
		char c;
		bool end_node;
		Node* parent;
		std::vector<Node*> children;
	};

	Node* findNode(const std::string key) const;
	void addNode(Node* parent_node, Node* child);
	void deleteNode(Node* node);
	void cloneRoot(const Trie& other);

	Node* root_;
	std::vector<std::string> keys_;
};

#include "trie.ipp"