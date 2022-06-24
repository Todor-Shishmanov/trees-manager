#include "ui.h"
#include "vtree.h"
#include "trie.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free

/*
void VTree_test_case_removen() {
	ValueTree big, small_tree, test_save_tree;
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	string t1_file = "112.txt";
	string t2_file = "1.txt";
	//do stuff
}
*/

void VTree_test_case_remove1() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "112.txt";
	string t2_file = "1.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;
}
void VTree_test_case_remove2() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "null.txt";
	string t2_file = "null.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;
}

void VTree_test_case_remove3() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "123.txt";
	string t2_file = "null.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;
}

void VTree_test_case_remove4() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "123.txt";
	string t2_file = "123.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;
}

void VTree_test_case_remove5() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "nasty.txt";
	string t2_file = "123.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;
}

void VTree_test_case_remove6() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "minus21.txt";
	string t2_file = "two.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;

}

void VTree_test_case_remove7() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "tripleCon.txt";
	string t2_file = "oneCon.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;

}

void VTree_test_case_remove8() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "tripleCon.txt";
	string t2_file = "two.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;

}

void VTree_test_case_remove9() {
	ValueTree big, small_tree, test_save_tree;

	string t1_file = "uslovie.txt";
	string t2_file = "uslovieSub.txt";
	cout << endl << endl << endl << "Test case " << t1_file << " - " << t2_file << endl << endl << endl;

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);

	cout << big << endl;

}

void VTree_test_case_contains() {
	ValueTree big, small_tree;

	string t1_file = "123.txt";
	string t2_file = "1.txt";

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	cout << small_tree;
	cout << big;
	cout << "Small contains big: " << small_tree.containsByValue(&big) << endl;
	cout << "Big contains small: " << big.containsByValue(&small_tree) << endl;
}

void VTree_test_case_save() {

	ValueTree big, small_tree, test_save_tree;

	string t1_file = "null.txt";
	string t2_file = "null.txt";
	string save_file = "test_save.txt";

	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);

	big.removeByValue(&small_tree);
	big.saveAsFile("test_save.txt");
	cout << "Tree:" << endl << big << endl;

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
	cout << "End of file (on a new line)";
}

void test_for_case_copy(ValueTree t) {
	t.loadFromFile("null.txt");
}

void VTest_tree_case_copy() {
	ValueTree big, small_tree, copy_assignment;
	string t1_file = "SmallOne.txt";
	string t2_file = "BigOne.txt";


	small_tree.loadFromFile(t2_file);
	big.loadFromFile(t1_file);
	cout << "Trees before any copy: " << endl << small_tree << endl << big << endl;
	copy_assignment = small_tree;
	cout << "Tree after = : " << endl << small_tree << endl << copy_assignment << endl;
	test_for_case_copy(big);
	cout << "Tree after copy : " << endl << big;
}
void UI_test_case_1() {
	UI test;
	test.run();
}


void Test_trie_copy(Trie<int> t) {
	t.insert("random", 10);
}
void Trie_test_case1() {
	int one_value = 1;
	string one_key = "o";
	int two_value = 2;
	string two_key = "b";
	int three_value = 3;
	string three_key = "ome";;
	Trie<int> test_trie;
	test_trie.insert(one_key, one_value);
	test_trie.insert(two_key, two_value);
	test_trie.insert(three_key, three_value);

	int get_one;
	if (test_trie.find(one_key, get_one)) {
		cout << "One: " << get_one << endl;
	}
	else cout << "One not found" << endl;

	int get_two;
	if (test_trie.find(two_key, get_two)) {
		cout << "Two: " << get_two << endl;
	}
	else cout << "Two not found" << endl;
	int get_three;
	if (test_trie.find(three_key, get_three)) {
		cout << "Three: " << get_three << endl;
	}
	else cout << "Three not found" << endl;
	test_trie.remove(three_key);
	if (test_trie.find(three_key, get_three)) {
		cout << "Three: " << get_three << endl;
	}
	else cout << "Three not found" << endl;

	Test_trie_copy(test_trie);

	int get_ten;
	if (test_trie.find("random", get_ten)) {
		cout << "Ten: " << get_ten << endl;
	}
	else cout << "Ten not found" << endl;
	if (test_trie.find(two_key, get_two)) {
		cout << "Two: " << get_two << endl;
	}
	else cout << "Two not found" << endl;
}

void Trie_test_case2() {
	ValueTree test_tree_1;
	test_tree_1.loadFromFile("SmallOne.txt");
	string one_key = "OneSmall";

	ValueTree test_tree_2;
	test_tree_2.loadFromFile("BigOne.txt");
	string two_key = "BigSmall";

	ValueTree test_tree_3;
	test_tree_3.loadFromFile("oneCon.txt");
	string three_key = "OneCon";

	Trie<ValueTree> test_trie;
	test_trie.insert(one_key, test_tree_1);
	test_trie.insert(two_key, test_tree_2);
	test_trie.insert(three_key, test_tree_3);
	ValueTree containter;
	if (test_trie.find(one_key, containter)) {
		cout << "One: " << endl << containter << endl;
	}
	else cout << "One not found" << endl;

	if (test_trie.find(two_key, containter)) {
		cout << "Two: " << endl << containter << endl;
	}
	else cout << "Two not found" << endl;

	if (test_trie.find(three_key, containter)) {
		cout << "Three: " << endl << containter << endl;
	}
	else cout << "Three not found" << endl;

	test_trie.remove(three_key);
	if (test_trie.find(three_key, containter)) {
		cout << "Three: " << endl << containter << endl;
	}
	else cout << "Three not found" << endl;
}

int run_test() {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);

	bool test_value_tree = true;
	bool test_prefix_tree = true;
	bool test_ui = true;

	try {
		if (test_value_tree) {
			VTree_test_case_remove1();
			VTree_test_case_remove2();
			VTree_test_case_remove3();
			VTree_test_case_remove4();
			VTree_test_case_remove5();
			VTree_test_case_remove6();
			VTree_test_case_remove7();
			VTree_test_case_remove8();
			VTree_test_case_remove9();
			VTree_test_case_contains();
			VTree_test_case_save();
			VTest_tree_case_copy();
		}
		if (test_prefix_tree) {
			Trie_test_case1();
			Trie_test_case2();
		}
		if (test_ui) {
			UI_test_case_1();
		}

	}
	catch (std::invalid_argument& e) {
		cout << endl << e.what() << endl;
	}
	cout << "Memory report: " << endl;
	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2)) {
		cout << "Memory leak!";
	}
	else cout << "OK";
	return 0;
}
/*
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	//stuff
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) {
		cout << "Hey, memory leak!";
	}
*/