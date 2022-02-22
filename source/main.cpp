#include <cstdio>
#include <iostream>
#include "tree/tree.h"

#define DEBUG 0

bool YourTest(std::string& input);
bool E2ETest(std::string& input, std::string& answer);

int main(int argc, char** argv) {

/*
	avl_tree::AVLTree<int> our_tree(4);
	
	our_tree.insert(2);
	our_tree.insert(1);
	our_tree.insert(15);
	our_tree.insert(8);
	our_tree.insert(12);
	our_tree.insert(3);
	our_tree.insert(6);
	our_tree.insert(14);
	our_tree.insert(5);
	our_tree.insert(7);
std::cout << "Before copy" << std::endl;
	avl_tree::AVLTree<int> copy_tree(our_tree);

std::cout << "Before operator" << std::endl;
	avl_tree::AVLTree<int> operator_tree(5);
	operator_tree = copy_tree;

std::cout << "After operator" << std::endl;

*/

	if (argc == 2) {
		std::string input = std::string(argv[1]);

		if (YourTest(input)) return 0;
		return 1;
	}

	if (argc == 3) {
		std::string input = std::string(argv[1]);
		std::string answer = std::string(argv[2]);

		if (E2ETest(input, answer)) {
			if (DEBUG) printf("OK Test\n");
			return 0;
		}
		if (DEBUG) printf("Failed Test\n");
		return 1;
	}
}

bool YourTest(std::string& input) { 
        
    std::ifstream input_potok(input);

  	avl_tree::AVLTree<int> test_tree;

    if (input_potok.is_open()) {

    	std::string action;
    	size_t num;
    	size_t result;

    	while (!input_potok.eof()) {

    		input_potok >> action >> num;

    		if (action == "k") test_tree.insert(num);
    		if (action == "m") {
    			result = test_tree.find_k_ordinal_stat(num);
    			if (result == 0xDEADBEEF) std::cout << "we haven't " << num << " elements in thee" << std::endl;
    			else std::cout << num << " ordinal statistics is " << result << std::endl;
    		}
    		if (action == "n") { 
    			result = test_tree.find_num_less_that_k(num);
    			std::cout << "less than " << num << " element is " << result << std::endl;
    		}
    	}
    	test_tree.dump();

    	input_potok.close();
        return true;
    }

    std::cout << "File [" << input << "] can't be open. Test failed\n";
    return false;
}

bool E2ETest(std::string& input, std::string& answer) { 
        
    std::ifstream input_potok(input);
    std::ifstream answer_potok(answer);

	avl_tree::AVLTree<int> test_tree;

    if (input_potok.is_open() && answer_potok.is_open()) {

    	std::string action;
    	size_t num;
    	size_t result;
    	size_t answer;
    	size_t err = 0;

    	while (!input_potok.eof()) {

    		input_potok >> action >> num;

    		if (action == "k") test_tree.insert(num);
    		if (action == "m") {
    			answer_potok >> answer;
    			result = test_tree.find_k_ordinal_stat(num);
    			if (result != answer) {
    				std::cout << "Ord_stat: answer is " << answer << " result is " << result << std::endl;
    				err++;
    			}
			}
    		if (action == "n") { 
    			answer_potok >> answer;
    			result = test_tree.find_num_less_that_k(num);
    			if (result != answer) {
    				std::cout << "Less_tht: answer is " << answer << " result is " << result << std::endl;
    				err++;
    			}
    		}
    	}

    	if (err > 0) {
    		std::cout << "Test failed" << std::endl;
    		return false;
    	}
    	else std::cout << "Test success" << std::endl;

    	input_potok.close();
        answer_potok.close();
        return true;
    }

    std::cout << "File [" << input << "] or [" << answer << "] can't be open. Test failed\n";
    return false;
}
