#pragma once
#include "../ValueTree/vtree.h"
#include "../Trie/trie.h"

class UI
{
public:
	UI() : stop_running_(false) {}
	~UI();
	void run();
private:
	bool stop_running_;
	Trie<ValueTree*> trees_;

	//Ease of use
	void quit();
	void show();
	void help();
	void print(std::string tree_name);

	//Task
	void save(std::string tree_name, std::string file_name);
	void load(std::string tree_name, std::string file_name);
	void contains(std::string first_tree, std::string second_tree);
	void remove(std::string first_tree, std::string second_tree);

	ValueTree* find(std::string tree_name); //Time complexity: O(k), k = lenght of the longest tree_name
	void add_tree(std::string tree_name, ValueTree* tree);

	//Healper for run()
	void getInput();
};

