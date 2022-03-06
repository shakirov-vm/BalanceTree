#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>
#include "../tree/tree.h"

// For use this you need write -DU_TEST with g++

BOOST_AUTO_TEST_SUITE(BigFive)

BOOST_AUTO_TEST_CASE(CopyCtor) {

	avl_tree::AVLTree<int> test_tree;
	test_tree.insert(2);
	test_tree.insert(1);
	test_tree.insert(3);
	test_tree.insert(4);

	avl_tree::AVLTree<int> copy_test_tree(test_tree);

	BOOST_REQUIRE_EQUAL(copy_test_tree.get_top()->key_, 2);
	BOOST_REQUIRE_EQUAL(copy_test_tree.get_top()->left_->key_, 1);
	BOOST_REQUIRE_EQUAL(copy_test_tree.get_top()->right_->key_, 3);
	BOOST_REQUIRE_EQUAL(copy_test_tree.get_top()->right_->right_->key_, 4);
}

BOOST_AUTO_TEST_CASE(MoveCtor) {

	avl_tree::AVLTree<int> test_tree;
	test_tree.insert(2);
	test_tree.insert(1);
	test_tree.insert(3);
	test_tree.insert(4);

	avl_tree::AVLTree<int> move_test_tree(std::move(test_tree));

	BOOST_REQUIRE_EQUAL(move_test_tree.get_top()->key_, 2);
	BOOST_REQUIRE_EQUAL(move_test_tree.get_top()->left_->key_, 1);
	BOOST_REQUIRE_EQUAL(move_test_tree.get_top()->right_->key_, 3);
	BOOST_REQUIRE_EQUAL(move_test_tree.get_top()->right_->right_->key_, 4);
}

BOOST_AUTO_TEST_CASE(MoveOp) {

	avl_tree::AVLTree<int> test_tree;
	test_tree.insert(2);
	test_tree.insert(1);
	test_tree.insert(3);
	test_tree.insert(4);

	avl_tree::AVLTree<int> move_test_tree;
	move_test_tree = std::move(test_tree);

	BOOST_REQUIRE_EQUAL(move_test_tree.get_top()->key_, 2);
	BOOST_REQUIRE_EQUAL(move_test_tree.get_top()->left_->key_, 1);
	BOOST_REQUIRE_EQUAL(move_test_tree.get_top()->right_->key_, 3);
	BOOST_REQUIRE_EQUAL(move_test_tree.get_top()->right_->right_->key_, 4);
}

BOOST_AUTO_TEST_CASE(CopyOp) {

	avl_tree::AVLTree<int> test_tree;
	test_tree.insert(2);
	test_tree.insert(1);
	test_tree.insert(3);
	test_tree.insert(4);

	avl_tree::AVLTree<int> copy_test_tree;
	copy_test_tree = test_tree;

	BOOST_REQUIRE_EQUAL(copy_test_tree.get_top()->key_, 2);
	BOOST_REQUIRE_EQUAL(copy_test_tree.get_top()->left_->key_, 1);
	BOOST_REQUIRE_EQUAL(copy_test_tree.get_top()->right_->key_, 3);
	BOOST_REQUIRE_EQUAL(copy_test_tree.get_top()->right_->right_->key_, 4);
}

BOOST_AUTO_TEST_SUITE_END()