#include <cstdio>

#include "tree.h"

namespace avl_tree {

	bool AVLTree::insert(key_t key) {
		
		printf("In insert\n");
		if (top_ == nullptr) {
			top_ = new Node{ key };
			return true;
		}
		printf("top is %p - %d\n", top_, top_->key_);
		printf("Insert not in top\n");
		Node* iter = top_;

		while (true) {
			if (iter->key_ > key) {
				if (iter->left_ == nullptr) { // or >=?
					iter->left_ = new Node{ key, nullptr, nullptr, iter};
					iter = iter->left_;
					printf("I am - %p , parent - %p\n", iter->parent_->left_, iter->parent_);
					break;
				}

				iter = iter->left_;

			}
			else if (iter->key_ == key) {
				printf("That key - %d is in tree!\n", key);
				return false;
			}
			else {
				if (iter->right_ == nullptr) {
					iter->right_ = new Node{ key, nullptr, nullptr, iter };
					iter = iter->right_;
					break;
				}

				iter = iter->right_;
			}
		}

		int flag;

		while (iter->parent_ != nullptr) {
			printf("First: i am - %p, left - %p, rigth - %p, parent - %p\n", iter, iter->left_, iter->right_, iter->parent_);
			flag = depth_calc(iter, iter->parent_, 1);
			iter = iter->parent_;
		}

		return true;
	}

	int depth_calc(Node* child, Node* parent, int add) {
		printf("child - %p, parent - %p\n", child, parent);
		if (child == parent->left_) {
			parent->left_depth_ += add;
			++(parent->left_size_);
			if (parent->left_depth_ <= parent->right_depth_) {
				printf("i am - %p, left - %p, rigth - %p, parent - %p\n", parent, parent->left_, parent->right_, parent->parent_);
				return 0;// if (parent->parent_ != nullptr) depth_calc(parent, parent->parent_, 0);
			}
			else {
				printf("i am - %p, left - %p, rigth - %p, parent - %p\n", parent, parent->left_, parent->right_, parent->parent_);
				return 1;// if (parent->parent_ != nullptr) depth_calc(parent, parent->parent_, 1);
			}
		}

		if (child == parent->right_) {
			parent->right_depth_ += add;
			++(parent->right_size_);
			if (parent->right_depth_ <= parent->left_depth_) {
				return 0;// depth_calc(parent, parent->parent_, 0);
			}
			else {
				return 1;// depth_calc(parent, parent->parent_, 1);
			}
		}
	}


}