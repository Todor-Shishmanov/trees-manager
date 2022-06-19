#pragma once
#include <vector>
#include <string>
#include <fstream>

//TODO: cin can be done with tokens, each string of tokens = 1 line
//TODO: Fix ValueTree so that it is a proper class by it's own. Big 5 and so on
//TODO: VNode can be nested class
//TODO: Fix naming of stuff, code is simple enough to be read by itself
//TODO: containsByValue and other functions must get by reference not pointers

struct VNode {
	VNode(int value) :
		value(value),
		parent(nullptr)
	{}
	VNode(int value, VNode* parent) :
		value(value),
		parent(nullptr)
	{
		if(parent) parent->addChild(this);
	}

	inline bool operator==(const VNode& other) const { return this->value == other.value; }
	inline bool operator!=(const VNode& other) const { return !((*this) == other); }
	inline bool operator< (const VNode& other) const { return this->value < other.value; }
	inline bool operator> (const VNode& other) const { return this->value > other.value; }
	inline bool operator<=(const VNode& other) const { return !((*this) > other); }
	inline bool operator>=(const VNode& other) const { return !((*this) < other); }

	void addChild(VNode* child);
	void removeChild(VNode* child);
	void replaceChild(VNode* old_child, VNode* new_child);

	int value;
	VNode* parent;
	std::vector<VNode*> children;
};
inline std::ostream& operator<<(std::ostream& os, const VNode& node) { return os << node.value; }

class ValueTree{
public:
	ValueTree() : root_(nullptr) {}
	~ValueTree() { deleteNode(root_); }
	ValueTree(const ValueTree& other);
	ValueTree& operator=(const ValueTree& other);


	friend std::ostream& operator<<(std::ostream& os, const ValueTree& tree);

	bool containsByValue(const ValueTree* t) const;
	void removeByValue(const ValueTree* t);
	void loadFromFile(std::string file_name);
	void saveAsFile(std::string file_name) const;

private:
	void cloneRoot(const ValueTree& other);
	bool containsNode(const VNode* node) const;
	void deleteNode(VNode* node);

	VNode* root_;
};

int sumParentlessNodes(std::vector<VNode const*>& parentless_nodes);
bool matchTree(const VNode* t1_root, const VNode* t2_root, std::vector<const VNode*>& remaining_nodes);
bool matchTree(const VNode* t1_root, const VNode* t2_root);