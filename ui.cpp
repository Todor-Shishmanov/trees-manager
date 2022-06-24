#include "ui.h"
#include <iostream>
#include "utility.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

UI::~UI(){
	vector<string> names = trees_.get_keys();
	for (size_t i = 0; i < names.size(); i++) {
		ValueTree* temp;
		trees_.find(names[i], temp);
		delete temp;
	}
}

void UI::run() {
	help();
	cout << endl;
	while (!stop_running_) {
		try { getInput(); }
		catch (std::invalid_argument& exception) { cout << exception.what() << endl << endl; }
	}
}

ValueTree* UI::find(string tree_name){
	ValueTree* tree;
	if (!trees_.find(tree_name, tree)) {
		return nullptr;
	}
	return tree;
}

void UI::add_tree(string tree_name, ValueTree* tree){
	trees_.insert(tree_name, tree);
}

void UI::quit(){
	stop_running_ = true;
}

void UI::show(){
	vector<string> names = trees_.get_keys();
	if (!names.size()) {
		cout << "No trees loaded yet." << endl;
		return;
	}
	cout << "Trees:" << endl;
	for (size_t i = 0; i < names.size(); i++){
		cout << names[i] << endl;
	}
}

void UI::help(){
	cout
		<< "Command [PARAMETER 1] ...    = Description" << endl
		<< "- QUIT                        = Stops the program." << endl
		<< "- SHOW                        = Shows all loaded trees." << endl
		<< "- HELP                        = Displays this message." << endl
		<< "- PRINT [TREE]                = Prints the tree the same way it will be saved." << endl
		<< "- SAVE [TREE] [FILE]          = Saves tree in file." << endl
		<< "- LOAD [TREE] [FILE]          = Loads tree from file." << endl
		<< "- CONTAINS [TREE 1] [TREE 2]  = Checks if Tree 2 is contained in Tree 1." << endl
		<< "- REMOVE [TREE 1] [TREE 2]    = Removes any instance of Tree 2 in Tree 1." << endl;
}

void UI::print(std::string tree_name){
	ValueTree* t;
	if (!trees_.find(tree_name, t)) {
		//cout << "There is no tree with this name." << endl;
		throw std::invalid_argument("There is no tree with this name.");
	}
	cout << "Tree " << tree_name << ": " << endl << *t << endl;
}


void UI::save(string tree_name, string file_name){
	ValueTree* tree = find(tree_name);
	if (!tree) throw std::invalid_argument("There is no tree with this name.");
	if (usable_file(file_name)) {
		cout << "Warning: file \"" << file_name << "\" already exists. Do you want to override it? (Answer with \"YES\" or \"NO\")" << endl;
		string user_answer;
		getline(cin, user_answer);
		if (user_answer != "YES") {
			cout << "SAVE is not performed!" << endl;
			return;
		}
	}
	tree->saveAsFile(file_name);
}

void UI::load(string tree_name, string file_name){
	ValueTree* tree = find(tree_name);
	if (tree) {
		cout << "Warning: tree \"" << tree_name << "\" already exists. Do you want to override it? (Answer with \"YES\" or \"NO\")" << endl;
		string user_answer;
		getline(std::cin, user_answer);
		if (user_answer != "YES") {
			cout << "LOAD is not performed!" << endl;
			return;
		}
		tree->loadFromFile(file_name);
		return;
	}
	for (size_t i = 0; i < tree_name.size(); i++)
		if (tree_name[i] == ' ') throw std::invalid_argument("Names cannot include spaces.");
	tree = new ValueTree();
	tree->loadFromFile(file_name);
	add_tree(tree_name, tree);
}

void UI::contains(string first_tree, string second_tree){
	ValueTree* t1 = find(first_tree), * t2 = find(second_tree);
	if(!t1 || !t2) throw std::invalid_argument("Trees not found.");

	if (t1->containsByValue(t2)) cout << first_tree << " contains " << second_tree << '.' << endl;
	else cout << first_tree << " does not contain " << second_tree << '.' << endl;
}

void UI::remove(string first_tree, string second_tree){
	ValueTree* t1 = find(first_tree), * t2 = find(second_tree);
	if (!t1 || !t2) throw std::invalid_argument("Trees not found.");
	t1->removeByValue(t2);
}

void UI::getInput(){
	string line;
	getline(std::cin, line);
	vector<string> input_sep = separate(line, ' ');

	if (input_sep[0] == "QUIT" && input_sep.size() == 1) {
		quit();
	}
	else if (input_sep[0] == "HELP" && input_sep.size() == 1) {
		help();
		cout << endl;
	}
	else if (input_sep[0] == "SHOW" && input_sep.size() == 1) {
		show();
		cout << endl;
	}
	else if (input_sep[0] == "PRINT" && input_sep.size() == 2) {
		print(input_sep[1]);
		cout << endl;
	}
	else if (input_sep[0] == "LOAD" && input_sep.size() == 3) {
		load(input_sep[1], input_sep[2]);
		cout << "Done!" << endl << endl;
	}
	else if (input_sep[0] == "SAVE" && input_sep.size() == 3) {
		save(input_sep[1], input_sep[2]);
		cout << "Done!" << endl << endl;
	}
	else if (input_sep[0] == "CONTAINS" && input_sep.size() == 3) {
		contains(input_sep[1], input_sep[2]);
		cout << endl;
	}
	else if (input_sep[0] == "REMOVE" && input_sep.size() == 3) {
		remove(input_sep[1], input_sep[2]);
		cout << "Done!" << endl << endl;
	}
	else throw std::invalid_argument("Invalid command.");
}
