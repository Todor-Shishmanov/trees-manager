#include "../ui.h"
#include "../vtree.h"
#include "../trie.h"
#include "../custom_unit_tests/test.h"

#include <iostream>
#include <filesystem> // fs::remove
namespace fs = std::filesystem;

using std::cout;
using std::cin;
using std::endl;
using std::string;
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free

void VTree_test_case_remove(string t1_file, string t2_file) {
	ValueTree big_tree, small_tree;

	cout << "=================================================" << endl;
	cout << "Test case remove " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big_tree.loadFromFile(t1_file);

	cout << t1_file << " tree:" << endl << big_tree << endl;
	cout << t2_file << " tree:" << endl << small_tree << endl;

	big_tree.removeByValue(small_tree);

	cout << "Result tree: " << endl << big_tree << endl;
}

void VTree_test_case_contains(string t1_file, string t2_file, string expected) {
	ValueTree big_tree, small_tree, test_save_tree;

	cout << "=================================================" << endl;
	cout << "Test case contains " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big_tree.loadFromFile(t1_file);

	cout << "Small :" << endl << small_tree << endl;
	cout << "Big :" << endl << big_tree << endl;
	cout << "Small contains big: " << small_tree.containsByValue(big_tree) << endl;
	cout << "Big contains small: " << big_tree.containsByValue(small_tree) << endl;

	cout << "Expected results: " << expected << endl;

}

void VTree_test_case_save(string tree_file) {
	cout << "=================================================" << endl;
	cout << "Test case VTree save" << endl;

	ValueTree tree, test_save_tree;
	string save_file = "dummy_test_file.txt";

	tree.loadFromFile(tree_file);
	tree.saveAsFile(save_file);
	cout << "Tree:" << endl << tree << endl;

	test_save_tree.loadFromFile(save_file);
	cout << "Tree from save file:" << endl << test_save_tree << endl;

	cout << "In file:" << endl;
	std::ifstream stream(save_file.c_str());
	if (!stream.is_open()) throw std::invalid_argument("Cannot open file.");
	string line;
	while (std::getline(stream, line)) {
		cout << line << endl;
	}
	stream.close();
	cout << endl;
	fs::remove(save_file);
}

//Helper for VTest_tree_case_copy()
void foo(ValueTree t, string tree_file) {
	t.loadFromFile(tree_file);
}

void VTest_tree_case_copy(string t1_file, string t2_file) {
	cout << "=================================================" << endl;
	cout << "Test case VTree copy" << endl;

	ValueTree tree, copy_tree;

	tree.loadFromFile(t1_file);
	copy_tree.loadFromFile(t2_file);
	cout << "Trees before any copy: " << endl << "t1: "<<endl << tree << endl << "t2: " << endl<< copy_tree << endl;

	copy_tree = tree;
	cout << "t2 = t1" << endl;
	cout << "Tree after copy assignment : " << endl << tree << endl << copy_tree << endl;

	foo(tree, t2_file);
	cout << "foo(tree)" << endl;
	cout << "Tree after copy constructor (should be unchanged): " << endl << tree << endl;
}

//Helper for Trie_test_case
void foo(Trie<int> t) {
	t.insert("random", 10);
}

void Trie_test_case1() {
	cout << "=================================================" << endl;
	cout << "Test case Trie<int>" << endl;

	int one_value = 1;
	string one_key = "o";
	int two_value = 2;
	string two_key = "b";
	int three_value = 3;
	string three_key = "ome";

	Trie<int> test_trie;
	test_trie.insert(one_key, one_value);
	cout << "Inserting: " << one_value << " with key " << one_key << endl;
	test_trie.insert(two_key, two_value);
	cout << "Inserting: " << two_value << " with key " << two_key << endl;
	test_trie.insert(three_key, three_value);
	cout << "Inserting: " << three_value << " with key " << three_key << endl;

	int container;
	if (test_trie.find(one_key, container)) {
		cout << "OK: " << container << endl;
	}
	else cout << "ERROR!" << endl;

	if (test_trie.find(two_key, container)) {
		cout << "OK: " << container << endl;
	}
	else cout << "ERROR!" << endl;

	if (test_trie.find(three_key, container)) {
		cout << "OK: " << container << endl;
	}
	else cout << "ERROR!" << endl;

	foo(test_trie);
	cout << "Testing the copy constructor by using foo(), which inserts random key with value 10" << endl;

	if (test_trie.find("random", container)) {
		cout << "ERROR! found: " << container << endl;
	}
	else cout << "Random not found! (OK)" << endl;

	test_trie.remove(three_key);
	cout << "Removing third key: " << three_key << endl;

	if (test_trie.find(three_key, container)) {
		cout << "ERROR! Found: " << container << endl;
	}
	else cout << "Third not found! (OK)" << endl;

	cout << "Trying to find the second key." << endl;
	if (test_trie.find(two_key, container)) {
		cout << "OK: " << container << endl;
	}
	else cout << "ERROR!" << endl;
}

void Trie_test_case2(string t1_file, string t2_file, string t3_file) {
	cout << "=================================================" << endl;
	cout << "Test case Trie<ValueTree>" << endl;

	ValueTree test_tree_1;
	test_tree_1.loadFromFile(t1_file);
	string one_key = "OneSmall";

	ValueTree test_tree_2;
	test_tree_2.loadFromFile(t2_file);
	string two_key = "BigSmall";

	ValueTree test_tree_3;
	test_tree_3.loadFromFile(t3_file);
	string three_key = "OneCon";

	Trie<ValueTree> test_trie;
	test_trie.insert(one_key, test_tree_1);
	test_trie.insert(two_key, test_tree_2);
	test_trie.insert(three_key, test_tree_3);
	cout << "Inserting trees: " << endl << "t1" << endl << test_tree_1 << endl << "t2" << endl << test_tree_2 << endl << "t3" << endl << test_tree_3 << endl << endl;

	ValueTree containter;

	cout << "Trying to find each tree:" << endl;

	if (test_trie.find(one_key, containter)) {
		cout << "t1 OK: " << endl << containter << endl;
	}
	else cout << "ERROR!" << endl;

	if (test_trie.find(two_key, containter)) {
		cout << "t2 OK: " << endl << containter << endl;
	}
	else cout << "ERROR!" << endl;

	if (test_trie.find(three_key, containter)) {
		cout << "t3 OK: " << endl << containter << endl;
	}
	else cout << "ERROR!" << endl;

	test_trie.remove(three_key);
	cout << "Removing t3" << endl;

	if (test_trie.find(three_key, containter)) {
		cout << "ERROR! Found: " << endl << containter << endl;
	}
	else cout << "t3 not found! (OK)" << endl;

	cout << "Check if the trees are still intact: "<< endl << "t1" << endl << test_tree_1 << endl << "t2" << endl << test_tree_2 << endl << "t3" << endl << test_tree_3 << endl;
}

void UI_test() {
	//HELP
	//LOAD big bigOne.txt
	//LOAD small smallOne.txt
	//CONTAINS big small
	//COUNTAINS small big
	//REMOVE big small
	//REMOVE small big
	//PRINT big
	//PRINT small
	//SHOW
	//QUIT

	UI test;
	test.run();
}

int run_test(bool test_value_tree, bool test_prefix_tree, bool test_ui) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	try {
		if (test_value_tree) {
			VTree_test_case_remove("Test_trees/112.txt", "Test_trees/1.txt");
			VTree_test_case_remove("Test_trees/null.txt", "Test_trees/null.txt");
			VTree_test_case_remove("Test_trees/123.txt", "Test_trees/null.txt");
			VTree_test_case_remove("Test_trees/123.txt", "Test_trees/123.txt");
			VTree_test_case_remove("Test_trees/nasty.txt", "Test_trees/123.txt");
			VTree_test_case_remove("Test_trees/minus21.txt", "Test_trees/two.txt");
			VTree_test_case_remove("Test_trees/tripleCon.txt", "Test_trees/oneCon.txt");
			VTree_test_case_remove("Test_trees/tripleCon.txt", "Test_trees/two.txt");
			VTree_test_case_remove("Test_trees/task.txt", "Test_trees/taskSub.txt");
			VTree_test_case_remove("Test_trees/twotwo.txt", "Test_trees/two.txt");

			VTree_test_case_contains("Test_trees/112.txt", "Test_trees/null.txt", "0 - 1");
			VTree_test_case_contains("Test_trees/123.txt", "Test_trees/1.txt", "0 - 1");
			VTree_test_case_contains("Test_trees/123.txt", "Test_trees/minus21.txt", "0 - 0");
			VTree_test_case_contains("Test_trees/null.txt", "Test_trees/null.txt", "1 - 1");
			VTree_test_case_contains("Test_trees/123.txt", "Test_trees/123.txt", "1 - 1");

			VTree_test_case_save("Test_trees/123.txt");
			VTest_tree_case_copy("Test_trees/SmallOne.txt", "Test_trees/null.txt");
		}
		if (test_prefix_tree) {
			Trie_test_case1();
			Trie_test_case2("Test_trees/SmallOne.txt", "Test_trees/BigOne.txt", "Test_trees/oneCon.txt");
		}
		if (test_ui) {
			UI_test();
		}
	}
	catch (std::invalid_argument& e) {
		cout << endl << "ERROR! Exception throw: " << e.what() << endl;
	}
	cout << "Memory report: " << endl;
	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2)) {
		cout << "Memory leak!";
	}
	else cout << "OK";
	return 0;
}