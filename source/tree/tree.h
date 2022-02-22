#include <fstream>
#include <cstdio>
#include <stack>
#include <iostream>
#include <exception>
#include <array>
#include <cstdio>
#include <cstdlib>

#pragma once

namespace avl_tree {

#define MAX_NAME_SIZE 75

	template <typename key_t = int>
	struct Node {
		key_t key_;
		Node* left_;
		Node* right_;
		Node* parent_;

		size_t left_size_;
		int height_;

		Node(key_t key = 0, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, size_t left_size = 0, int height = 1) :
			key_(key),
			left_(left),
			right_(right),
			parent_(parent),
			left_size_(left_size),
			height_(height) {}

		void dump() {

			std::cout << "node is " << key_ << ", ";
			if (left_ != nullptr) std::cout << "left is " << left_->key_ << ", ";
			if (right_ != nullptr) std::cout << "right is " << right_->key_ << ", ";
			if (parent_ != nullptr) std::cout << "parent is " << parent_->key_ << ", ";
			std::cout << std::endl;
		}

		int balance_factor();
		void fix_height();
		int height();
		Node<key_t>* balance();
		Node<key_t>* left_rotate();
		Node<key_t>* right_rotate();

	};

	template <typename key_t = int>	
	class AVLTree {
		
		Node<key_t>* top_;

	private:

		void delete_subtree(Node<key_t> * upper);
		void find_insert_place(Node<key_t> * &iter, Node<key_t> * &parent, key_t key);

	public:

		AVLTree() : top_(nullptr) {}
		AVLTree(key_t key) {
			top_ = new Node<key_t>(key);
		}
		AVLTree(const AVLTree& other);
		AVLTree(AVLTree&& tmp);
		AVLTree& operator= (const AVLTree& other);
		AVLTree& operator= (AVLTree&& tmp);
		~AVLTree();

		void insert(key_t key);
		key_t find_k_ordinal_stat(size_t k) const;
		size_t find_num_less_that_k(size_t k) const;
		void dump();

	};

	template <typename key_t = int>
	void print_graph(Node<key_t> * node, std::ofstream& potok);

	template <typename key_t>
	void AVLTree<key_t>::delete_subtree(Node<key_t> * upper) {

		std::stack<Node<key_t>*> stk; 

		Node<key_t> * last_node = nullptr;
		Node<key_t> * stk_top = nullptr;
		Node<key_t> * iter = upper;

		while (stk.size() != 0 || iter != nullptr) {

			if (iter != nullptr) {

				stk.push(iter);
				iter = iter->left_;
			}
			else {

				stk_top = stk.top();

				if ((stk_top->right_ != nullptr) && (last_node != stk_top->right_)) {

					iter = stk_top->right_;
				}
				else {

					stk.pop();
					delete last_node;
					last_node = stk_top;
				}
			}
		}

		delete last_node;
	}

	template <typename key_t>
	AVLTree<key_t>::~AVLTree() {

		delete_subtree(top_);
	}

	template <typename key_t>
	AVLTree<key_t>::AVLTree(const AVLTree<key_t>& other) { 
		
		if (other.top_ == nullptr) { // bad option
			top_ = nullptr;
			return;
		}

		try {

		    Node<key_t>* side = nullptr; // How do poison like 0x00000001? 
			Node<key_t>* iter = other.top_;

			Node<key_t>* iter_new = new Node<key_t> { iter->key_, nullptr, nullptr, nullptr, iter->left_size_ };
			top_ = iter_new;

			while (side != other.top_) { // If, for example, we want do there side != nullptr
									 	 // And we want compare side with 100% invalid ptr [so first compare will always true]
				if (side == iter->right_) {
					side = iter;
					iter = iter->parent_;
					iter_new = iter_new->parent_;
					continue;
				}
				if (iter->left_ != nullptr && iter->left_ != side) {
					iter = iter->left_;
					iter_new->left_ = new Node<key_t> {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
					iter_new = iter_new->left_;
					continue;
				}
				if (iter->left_ == nullptr) {
				
					if (iter->right_ != nullptr) {
						iter = iter->right_;
						iter_new->right_ = new Node<key_t> {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
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
						iter_new->right_ = new Node<key_t> {iter->key_, nullptr, nullptr, iter_new, iter->left_size_ };
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
		catch (std::bad_alloc) {

			delete_subtree(top_); // But we have bad_alloc, how we get stack?
			top_ = nullptr; // Or compiler optimize this?

			// Why not? We have tree in a consistent state but when bad_alloc throw out - dtor don't call -
			// - but we want do this. Of course i can do function like "delete a subtree" and call it there
			// but i think it is the same
			// And - we don't want have function like "delete a subtree" because it kill our invariants
			throw;
		}

	}

	template <typename key_t>
	AVLTree<key_t>& AVLTree<key_t>::operator= (const AVLTree<key_t>& other) {
		
	    if (this == &other) return *this;

	    AVLTree<key_t> tmp(other);

	    std::swap(tmp, *this);

	    return *this;
	}

	template <typename key_t>
	AVLTree<key_t>::AVLTree(AVLTree<key_t>&& tmp) {
	    std::swap(top_, tmp.top_);
	}

	template <typename key_t>
	AVLTree<key_t>& AVLTree<key_t>::operator= (AVLTree<key_t>&& tmp) {
	    
	    if (this == &tmp) {
	        return *this;
	    }

	  	std::swap(top_, tmp.top_);
		
	    return *this;
	}

	template <typename key_t>
	void AVLTree<key_t>::find_insert_place(Node<key_t> * &iter, Node<key_t> * &parent, key_t key) {
		
		while (true) {

			if (iter == nullptr) return;
	
			if (iter->key_ > key) {
				parent = iter;
				++(iter->left_size_);
				iter = iter->left_;
			}
			else if (iter->key_ == key) {
				std::cout << "That key - " << key << " is in tree!" << std::endl;
				throw std::domain_error("That key is already in the tree\n");
			}
			else {
				parent = iter;				
				iter = iter->right_;
			}
		}
	}

	template <typename key_t>
	void AVLTree<key_t>::insert(key_t key) { // if bad_alloc - it fly to user

		if (top_ == nullptr) {
			top_ = new Node<key_t>{ key };
			return;
		}

		Node<key_t> * iter = top_;
		Node<key_t> * parent = top_->parent_;

		find_insert_place(iter, parent, key);

		iter = new Node<key_t>{ key, nullptr, nullptr, parent };
	//----------------------------------------------------- Kalb Line
		if (parent->key_ > iter->key_) parent->left_ = iter;
		if (parent->key_ < iter->key_) parent->right_ = iter;

		while (iter->parent_ != nullptr) { 
			iter = iter->balance(); 
			iter = iter->parent_;
		}

		top_ = top_->balance();

		while (top_->parent_ != nullptr) {
			top_ = top_->parent_;
		}


	}

	template <typename key_t>
	key_t AVLTree<key_t>::find_k_ordinal_stat(size_t k) const {
	
		if (top_ == nullptr) {
			throw std::underflow_error("Tree is empty\n");
		}

		Node<key_t>* iter = top_;
		size_t on_the_left = iter->left_size_;

		while (1) {

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
		throw std::out_of_range("Tree contains fewer elements than k\n");
	}


	template <typename key_t>
	size_t AVLTree<key_t>::find_num_less_that_k(size_t k) const {

		if (top_ == nullptr) {
			throw std::underflow_error("Tree is empty\n");
		}

		Node<key_t> * iter = top_;
		size_t on_the_left = iter->left_size_;

		while (1) {

			if (iter->key_ > k) {

				if (iter->left_ == nullptr) {
					return on_the_left;
				}
				on_the_left -= iter->left_size_;
				iter = iter->left_;
				on_the_left += iter->left_size_;
				continue;
			}
			if (iter->key_ == k) {

				return on_the_left;
			}
			if (iter->key_ < k) {

				if (iter->right_ == nullptr) {
					++on_the_left;
					return on_the_left;
				}
				iter = iter->right_;
				on_the_left += iter->left_size_ + 1;
			}
		}
	}

	template <typename key_t>
	int Node<key_t>::height() {
		if (this != nullptr) return height_;
		else return 0;
	}

	template <typename key_t>
	int Node<key_t>::balance_factor() {
		return right_->height() - left_->height();
	}

	template <typename key_t>
	void Node<key_t>::fix_height() {
		int left_height = left_->height();
		int right_height = right_->height();
		if (left_height > right_height) height_ = left_height + 1;
		else height_ = right_height + 1;
	}

	template <typename key_t>
	Node<key_t> * Node<key_t>::right_rotate() {

		Node<key_t>* lifted = left_;
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

	template <typename key_t>
	Node<key_t> * Node<key_t>::left_rotate() {

		Node<key_t> * lifted = right_;
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

	template <typename key_t>
	Node<key_t> * Node<key_t>::balance() {

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

	template <typename key_t>
	void AVLTree<key_t>::dump() {

		printf("Enter file name, where will be dump graph\n");
		char answer[MAX_NAME_SIZE] = {};

		fseek(stdin, 0, SEEK_END);

		std::cin.getline(answer, MAX_NAME_SIZE, '\n');

		std::ofstream potok;
		potok.open(answer);

		if (!potok.is_open()) return;

		potok << "digraph G {\n";
		print_graph(top_, potok);
		potok << "}\n";

		potok.close();
	}

	template <typename key_t>
	void print_graph(Node<key_t>* node, std::ofstream& potok) { // So slooow

		if (node->left_ != nullptr) {
			potok << "\"" << node->key_ << "-" << node->left_size_;
			potok << "\" -> \"" << node->left_->key_;
			potok << "-" << node->left_->left_size_ << "\";\n";

			print_graph(node->left_, potok);
		}

		if (node->right_ != nullptr) {
			potok << "\"" << node->key_ << "-" << node->left_size_;
			potok << "\" -> \"" << node->right_->key_;
			potok << "-" << node->right_->left_size_ << "\";\n";

			print_graph(node->right_, potok);
		}
// It's turn off because we want print left_size
		/*if (node->parent_ != nullptr) {
			potok << "\"" << node->key_;
			potok << "\" -> \"" << node->parent_->key_;
			potok << "\";\n";
		}*/
	}

}