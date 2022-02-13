#include <cstdio>
#include <stack>
#include <iostream>

#include "tree.h"

namespace avl_tree {

	AVLTree::~AVLTree() {
		if (top_ == nullptr) return;

		Node* side; //How do poison?
		Node* iter = top_;

		while (side != top_) {

			if (side == iter->right_) {
				std::cout << side->key_ << " have " << side->left_size_ << std::endl;
				delete side;
				side = iter; 
				iter = iter->parent_;
				continue;
			}
			if (iter->left_ != nullptr && iter->left_ != side) { 

				iter = iter->left_;
				continue;
			}
			if (iter->left_ == nullptr) {
			
				if (iter->right_ != nullptr) {
					iter = iter->right_;
					continue;
				}
				side = iter;
				iter = iter->parent_;
				continue;
			}
			if (side == iter->left_) {
				
				if (iter->right_ != nullptr) {
				std::cout << side->key_ << " have " << side->left_size_ << std::endl;
					delete side;
					iter = iter->right_;
					continue;
				}
				else {
				std::cout << side->key_ << " have " << side->left_size_ << std::endl;
					delete side;
					side = iter;
					iter = iter->parent_;
					continue;
				}
			}
		}
				std::cout << side->key_ << " have " << side->left_size_ << std::endl;
		delete side;
	}

	AVLTree::AVLTree(const AVLTree& other) {
		if (other.top_ == nullptr) { // bad option
			top_ = nullptr;
			return;
		} 

		Node* side; //How do poison?
		Node* iter = other.top_;

		Node* iter_new = new Node { iter->key_, nullptr, nullptr, nullptr, iter->left_size_ };
		top_ = iter_new;

		while (side != other.top_) {

			if (side == iter->right_) {
				side = iter;
				iter = iter->parent_;
				iter_new = iter_new->parent_;
				continue;
			}
			if (iter->left_ != nullptr && iter->left_ != side) {
				iter = iter->left_;
				iter_new->left_ = new Node {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
				iter_new = iter_new->left_;
				continue;
			}
			if (iter->left_ == nullptr) {
			
				if (iter->right_ != nullptr) {
					iter = iter->right_;
					iter_new->right_ = new Node {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
					iter_new = iter_new->right_;
					continue;
				}
				side = iter;
				iter = iter->parent_;
				iter_new = iter_new->parent_;
				continue;
			}
			if (side == iter->left_) {
				
				if (iter->right_ != nullptr) {
					iter = iter->right_;
					iter_new->right_ = new Node {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
					iter_new = iter_new->right_;
					continue;
				}
				else {
					side = iter;
					iter = iter->parent_;
					iter_new = iter_new->parent_;
					continue;
				}
			}
		}
	}

	AVLTree& AVLTree::operator= (const AVLTree& other) {

	    if (this == &other) {
	        return *this;
	    }

	    if (other.top_ != nullptr) {

		    Node* side; //How do poison?
			Node* iter = other.top_;

			Node* iter_new = new Node { iter->key_, nullptr, nullptr, nullptr, iter->left_size_ };
			top_ = iter_new;

			while (side != other.top_) {

				if (side == iter->right_) {
					side = iter;
					iter = iter->parent_;
					iter_new = iter_new->parent_;
					continue;
				}
				if (iter->left_ != nullptr && iter->left_ != side) {
					iter = iter->left_;
					iter_new->left_ = new Node {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
					iter_new = iter_new->left_;
					continue;
				}
				if (iter->left_ == nullptr) {
				
					if (iter->right_ != nullptr) {
						iter = iter->right_;
						iter_new->right_ = new Node {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
						iter_new = iter_new->right_;
						continue;
					}
					side = iter;
					iter = iter->parent_;
					iter_new = iter_new->parent_;
					continue;
				}
				if (side == iter->left_) {
					
					if (iter->right_ != nullptr) {
						iter = iter->right_;
						iter_new->right_ = new Node {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
						iter_new = iter_new->right_;
						continue;
					}
					else {
						side = iter;
						iter = iter->parent_;
						iter_new = iter_new->parent_;
						continue;
					}
				}
			}
	    }

	    return *this;
	}
	
	bool AVLTree::insert(key_t key) {

		if (top_ == nullptr) {
			top_ = new Node{ key };
			return true;
		}

		Node* iter = top_;
		Node* parent = top_->parent_;

		while (true) {

			if (iter == nullptr) {
				iter = new Node{ key, nullptr, nullptr, parent };
				if (parent->key_ > iter->key_) parent->left_ = iter;
				if (parent->key_ < iter->key_) parent->right_ = iter;
				iter->dump();
				break;
			}
			if (iter->key_ > key) {
				parent = iter;
				++(iter->left_size_);
				iter = iter->left_;
			}
			else if (iter->key_ == key) {
				printf("That key - %d is in tree!\n", key);
				return false;
			}
			else {
				parent = iter;
				// There ++ to right size				
				iter = iter->right_;
			}
		}

		while (iter->parent_ != nullptr) { 
			printf("iter is %ld\n", iter->key_);
			iter = iter->balance(); 
			iter = iter->parent_;
		}

		top_ = top_->balance();

		while (top_->parent_ != nullptr) {
			top_ = top_->parent_;
		}

		return true;
	}

	AVLTree::AVLTree(AVLTree&& tmp) {
	    std::swap(top_, tmp.top_);
	}

	AVLTree& AVLTree::operator= (AVLTree&& tmp) {
	    
	    if (this == &tmp) {
	        return *this;
	    }
	    std::swap(top_, tmp.top_);
	    return *this;
	}

	size_t AVLTree::find_k_ordinal_stat(size_t k) {
	
		if (top_ == nullptr) {
			std::cout << "Tree is empty" << std::endl;
			return 0xDEADBEEF; // maybe -1?
		}

		Node* iter = top_;
		size_t on_the_left = iter->left_size_;
		std::cout << "left_size_ on top_ is " << on_the_left << std::endl;
// what's     if?
		while (1) {
printf("key - %ld, on_the_left - %ld\n", iter->key_, on_the_left);
			if (on_the_left > k - 1) {
				on_the_left -= iter->left_size_;
				iter = iter->left_;
				on_the_left += iter->left_size_;
				continue;
			}
			if (on_the_left == k - 1) {
				return iter->key_;
			}
			if (on_the_left < k - 1) {
				if (iter->right_ == nullptr) break;
				iter = iter->right_;
				on_the_left += iter->left_size_ + 1;
			}
		}
		std::cout << "There's no " << k << " elements" << std::endl;
		return 0xDEADBEEF; // What there?		
	}


	size_t AVLTree::find_num_less_that_k(size_t k) {

		if (top_ == nullptr) {
			std::cout << "Tree is empty" << std::endl;
			return 0xDEADBEEF; // maybe -1?
		}

		Node* iter = top_;
		size_t on_the_left = iter->left_size_;
		std::cout << "left_size_ on top_ is " << on_the_left << std::endl;

		while (1) {

			if (iter->key_ > k) {
				printf("%ld less that %ld\n", k, iter->key_);
				if (iter->left_ == nullptr) {

					return on_the_left;
				}
				on_the_left -= iter->left_size_;
				iter = iter->left_;
				on_the_left += iter->left_size_;
				continue;
			}
			if (iter->key_ == k) {
				printf("%ld equal %ld\n", k, iter->key_);
				// ?
				return on_the_left;
			}
			if (iter->key_ < k) {
				printf("%ld more that %ld\n", k, iter->key_);
				if (iter->right_ == nullptr) {
					++on_the_left;
					return on_the_left;
				}
				iter = iter->right_;
				on_the_left += iter->left_size_ + 1;
			}
		}
		return 0xDEADBEEF; // What there?
	}

	int Node::height() {
		if (this != nullptr) return height_; //that can't be
		else return 0;
	}

	int Node::balance_factor() {
		return right_->height() - left_->height();
	}

	void Node::fix_height() {
		int left_height = left_->height();
		int right_height = right_->height();
		if (left_height > right_height) height_ = left_height + 1;
		else height_ = right_height + 1;
	}

	Node* Node::right_rotate() {

		Node* lifted = left_;
		//std::cout << "right rotate " << right_ << std::endl; 
		//if (right_ != nullptr) --(right_->left_size_);
		std::cout << "key is " << key_ << " and " << left_size_ << std::endl;
		left_size_ -= left_->left_size_ + 1;
		if ((parent_ != nullptr) && (parent_->left_ == this)) parent_->left_ = lifted;
		else if ((parent_ != nullptr) && (parent_->right_ == this)) parent_->right_ = lifted;

		lifted->parent_ = parent_;
		if (lifted->right_ != nullptr) lifted->right_->parent_ = this;
		parent_ = lifted;

		left_ = lifted->right_;
		lifted->right_ = this;

		fix_height();
		lifted->fix_height();
		return lifted;
	}

	Node* Node::left_rotate() {

		Node* lifted = right_;
		//std::cout << "left rotate " << right_ << std::endl;
		//++(right_->left_size_);
		right_->left_size_ += left_size_ + 1;
		if ((parent_ != nullptr) && (parent_->left_ == this)) parent_->left_ = lifted;
		else if ((parent_ != nullptr) && (parent_->right_ == this)) parent_->right_ = lifted;

		lifted->parent_ = parent_;
		if (lifted->left_ != nullptr) lifted->left_->parent_ = this;
		parent_ = lifted;

		right_ = lifted->left_;
		lifted->left_ = this;

		fix_height();
		lifted->fix_height();
		return lifted;
	}

	Node* Node::balance() {

		fix_height();
		if (balance_factor() == 2) {
			if (right_->balance_factor() < 0) right_ = right_->right_rotate();
			return left_rotate();
		}

		if (balance_factor() == -2) {
			if (left_->balance_factor() > 0) left_ = left_->left_rotate();
			return right_rotate();
		}
		return this;
	}

}