#include "vtree.h"
#include "utility.h"
#include <queue>
#include <stack>
#include <fstream>

typedef std::pair<VNode const* const, VNode const* const> NodePair;

using std::vector;
using std::string;
using std::queue;
using std::stack;

void VNode::addChild(VNode* child) {
    if (!child || child->parent == this) return;
    for (size_t i = 0; i < children.size(); i++) {
        if (*(children[i]) == *child) return;
    }
    if (child->parent) child->parent->removeChild(child);
    child->parent = this;
    children.push_back(child);
}

void VNode::removeChild(VNode* child) {
    if (!child || child->parent != this) return;
    for (size_t i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            child->parent = nullptr;
            children.erase(children.begin() + i);
            return;
        }
    }
}

void VNode::replaceChild(VNode* old_child, VNode* new_child){
    if (!new_child) {
        removeChild(old_child);
        return;
    }
    if (!old_child || old_child->parent != this || new_child->parent == this) return;
    for (size_t i = 0; i < children.size(); i++) {
        if (children[i] == old_child) { //find old child place
            old_child->parent = nullptr;
            for (size_t j = 0; j < children.size(); j++) {
                if (*children[j] == *new_child) {
                    children.erase(children.begin() + i); // don't add child
                    return;
                }
            }
            //add child
            children[i] = new_child;
            new_child->parent = this;
            return;
        }
    }
}

ValueTree::ValueTree(const ValueTree& other){
    cloneRoot(other);
}

ValueTree& ValueTree::operator=(const ValueTree& other){
    ValueTree temp_tree;
    temp_tree.cloneRoot(other);
    deleteNode(root_);
    root_ = temp_tree.root_;
    temp_tree.root_ = nullptr;
    return *this;
}

bool ValueTree::containsByValue(const ValueTree* const t) const {
    VNode* t1_root = root_, * t2_root = t->root_;
    if (!t1_root) return true; //empty tree is contained in every tree.
    if (!t2_root) return false; //empty tree contains only itself.
    queue<VNode*> bfs_queue;
    bfs_queue.push(t1_root);
    while (!bfs_queue.empty()) {
        VNode* t1_node= bfs_queue.front();
        bfs_queue.pop();
        if (*t1_node == *t2_root && matchTree(t1_node, t2_root)) return true;
        for (unsigned i = 0; i < t1_node->children.size(); i++)
            bfs_queue.push(t1_node->children[i]);
    }
    return false;
}

void ValueTree::removeByValue(const ValueTree* const t) {
    VNode* t1_root = root_, * t2_root = t->root_;
    if (!t1_root || !t2_root) return;
    queue<VNode*> bfs_t1_queue;
    stack<VNode*> potential_subtrees_stack;
    bfs_t1_queue.push(t1_root);
    while (!bfs_t1_queue.empty()) {
        VNode* t1_node = bfs_t1_queue.front();
        bfs_t1_queue.pop();
        for (unsigned i = 0; i < t1_node->children.size(); i++) 
            bfs_t1_queue.push(t1_node->children[i]);
        if (*t1_node == *t2_root) {
            potential_subtrees_stack.push(t1_node);
        }
    }

    while (!potential_subtrees_stack.empty()) {
        VNode* potential_root = potential_subtrees_stack.top();
        potential_subtrees_stack.pop();
        vector<VNode const*> parentless_nodes;
        if (!matchTree(potential_root, t2_root, parentless_nodes)) continue;
        
        //Potential node confirmed
        VNode* confirmed_root = potential_root;
        
        if (parentless_nodes.empty()) {
            if (confirmed_root == root_) root_ = nullptr;
            else confirmed_root->parent->removeChild(confirmed_root);
            deleteNode(confirmed_root);
            continue;
        }
        int value = sumParentlessNodes(parentless_nodes);
        VNode* new_node = new VNode(value);

        if (confirmed_root == root_) root_ = new_node;
        else confirmed_root->parent->replaceChild(confirmed_root, new_node);
        deleteNode(confirmed_root);
        if (new_node->parent || new_node == root_) {
            if (new_node == t2_root) {
                potential_subtrees_stack.push(new_node);
            }
        }
        else delete new_node;
    }   
}

vector<string> tokenizeString(const string& line) {
    vector<string> formated_string;
    if (line[0] != '|' || line[line.size() - 1] != '|') throw std::invalid_argument("Incorrect file format: Line doesn't start or end with \'| \'");

    //Each iteration check for [space] + number or [space] + '|'
    for (size_t i = 1; i < line.length() - 1; i++) {
        if (line[i++] != ' ') throw std::invalid_argument("Incorrect file format: Number or \'|\' isn't separated by a space.");
        
        //Integer 'i' is incremented

        if (line[i] == '|') { //Next brotherhood
            formated_string.push_back("|");
        }
        else if (is_digit(line[i]) || line[i] == '-' && is_digit(line[i + 1])) { //Get number
            string number;
            if (line[i] == '-') {
                number += line[i++]; //we know ++i < line.size(), because the last symbol is '|'
            }
            do {
                number += line[i++];
            } while (is_digit(line[i]));
            formated_string.push_back(number);
            i--;
        }
        else throw std::invalid_argument("Incorrect file format: Only space, \'|\' and numbers are allowed.");
    }

    return formated_string;
}

void ValueTree::loadFromFile(std::string file_name) {
    std::ifstream stream(file_name);
    if (!stream.is_open()) throw std::invalid_argument("Cannot open file!");

    ValueTree* temp_tree = new ValueTree();
    VNode* temp_root = new VNode(0); //Alternative is to manually add the first element
    temp_tree->root_ = temp_root;

    string line;
    vector<string> tokens;
    queue<VNode*> parent_nodes;
    queue<VNode*> new_nodes;
    parent_nodes.push(temp_root);

    while (std::getline(stream, line)) {
        try {
            tokens = tokenizeString(line);
        }
        catch (std::invalid_argument& exception) {
            delete temp_tree;
            throw exception;
        }
        for (size_t i = 0; i < tokens.size(); i++) {
            if (parent_nodes.empty()) {
                delete temp_tree;
                throw std::invalid_argument("Incorrect file format: More brotherhoods than parents.");
            }
            string t = tokens[i];
            if (t == "|") {
                parent_nodes.pop();
                continue;
            }
            int value = stringToInt(t);
            VNode* new_node = new VNode(value, parent_nodes.front());
            if (!new_node->parent) {
                delete temp_tree;
                delete new_node;
                throw std::invalid_argument("Incorrect file format: Values among nodes in a brotherhood aren't unique.");
            }
            new_nodes.push(new_node);
        }
        if (!parent_nodes.empty()) {
            delete temp_tree;
            throw std::invalid_argument("Incorrect file format: More parents than brotherhoods.");
        }
        parent_nodes = new_nodes;
        while (!new_nodes.empty()) new_nodes.pop();
    }
    if (!parent_nodes.empty()) {
        delete temp_tree;
        throw std::invalid_argument("Incorrect file format: More parents than brotherhoods.");
    }
    stream.close();

    //Success
    VNode* new_real_root;
    if (temp_root->children.empty()) new_real_root = nullptr;
    else new_real_root = temp_root->children[0]; //skip the temp root
    if(root_) deleteNode(root_);
    root_ = new_real_root;
    temp_root->removeChild(new_real_root);
    delete temp_tree;
}

std::ostream& operator<<(std::ostream& os, const ValueTree& tree) {
    if (!tree.root_) return os << "| |";

    os << "| " << *(tree.root_) << " |" << std::endl;

    queue<VNode*> bfs_queue;
    bfs_queue.push(tree.root_);
    unsigned curr_level_brotherhoods = 1;
    unsigned next_level_brotherhoods = 0;
    VNode* node = nullptr;

    while (!bfs_queue.empty()) {
        os << '|';
        while (curr_level_brotherhoods) {
            node = bfs_queue.front();
            bfs_queue.pop();
            next_level_brotherhoods += node->children.size();
            for (size_t i = 0; i < node->children.size(); i++) {
                os << ' ' << node->children[i]->value ;
                bfs_queue.push(node->children[i]);
            }
            os << " |";
            curr_level_brotherhoods--;
        }
        if (bfs_queue.empty()) continue;
        os << std::endl;
        curr_level_brotherhoods = next_level_brotherhoods;
        next_level_brotherhoods = 0;
    }
    return os;
}

void ValueTree::saveAsFile(std::string file_name) const {
    std::ofstream stream(file_name.c_str(), std::ios::trunc);
    if (!stream.is_open()) throw std::invalid_argument("Cannot open file.");
    stream << *this;
    stream.close();
}

//Used in the copy constructor and operator =
void ValueTree::cloneRoot(const ValueTree& other){
    if (other.root_) {
        root_ = new VNode(other.root_->value);
        queue<VNode*> other_bfs_queue, copy_bfs_queue;
        other_bfs_queue.push(other.root_);
        copy_bfs_queue.push(root_);
        while (!other_bfs_queue.empty()) {
            VNode* node_other = other_bfs_queue.front(), * node_copy = copy_bfs_queue.front();
            other_bfs_queue.pop();
            copy_bfs_queue.pop();
            for (size_t i = 0; i < node_other->children.size(); i++) {
                VNode* new_node = new VNode(node_other->children[i]->value);
                node_copy->addChild(new_node);
                other_bfs_queue.push(node_other->children[i]);
                copy_bfs_queue.push(new_node);
            }
        }

    }
    else root_ = nullptr;
}

bool ValueTree::containsNode(const VNode* node) const {
    if (!node) return true;
    while (node->parent) {
        node = node->parent;
    } 
    if (node == root_) return true;
    return false;
}

void ValueTree::deleteNode(VNode* node) {
    if (!node) return;
    for (size_t i = 0; i < node->children.size(); i++) {
        deleteNode(node->children[i]);
    }
    delete node;
}

//Returns true if t1 contained t2, else false.
//In remaining_nodes will be added nodes from t1 that are NOT in t2 .
//remaining_VNodes is valid only if the function returns true.
bool matchTree(const VNode* const t1_root, const VNode* const t2_root, vector<VNode const*>& remaining_nodes) {
    bool found = false;
    queue<NodePair> bfs_queue; //paired nodes are equal by value
    bfs_queue.push(NodePair(t1_root, t2_root));
    while (!bfs_queue.empty()) {
        NodePair curr_pair = bfs_queue.front();
        bfs_queue.pop();
        vector<VNode*> t1_children_copy = curr_pair.first->children; //used to remove found elements
        for (size_t i = 0; i < curr_pair.second->children.size(); i++) {
            found = false;
            for (size_t j = 0; j < t1_children_copy.size(); j++) {
                if (*(curr_pair.second->children[i]) == *(t1_children_copy[j])) {
                    found = true;
                    bfs_queue.push(NodePair(t1_children_copy[j], curr_pair.second->children[i]));
                    t1_children_copy.erase(t1_children_copy.begin() + j);
                    break;
                }
            }
            if (!found) return false;
        }
        for (size_t i = 0; i < t1_children_copy.size(); i++) {
            remaining_nodes.push_back(t1_children_copy[i]);
        }
    } // end of bfs
    return true;
}

bool matchTree(const VNode* const t1_root, const VNode* const t2_root) {
    vector<VNode const*> unused_arg;
    return matchTree(t1_root, t2_root, unused_arg);
}

int sumParentlessNodes(vector<VNode const*>& parentless_nodes) {
    int value = 0;
    for (size_t i = 0; i < parentless_nodes.size(); i++) {
        std::queue<VNode const*> bfs_queue;
        bfs_queue.push(parentless_nodes[i]);
        while (not bfs_queue.empty()) {
            VNode const* curr_element = bfs_queue.front();
            value += curr_element->value;
            for (size_t i = 0; i < curr_element->children.size(); i++) {
                bfs_queue.push(curr_element->children[i]);
            }
            bfs_queue.pop();
        }
    }
    return value;
}