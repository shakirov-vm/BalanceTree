#include <cstdio>
#include <stack>

#include "tree.h"

namespace avl_tree {

	AVLTree::~AVLTree() {
		printf("WE DELETE %p\n", this);
		std::stack<Node*> stk;
		Node* last_node = nullptr;
		Node* stk_top = nullptr;
		Node* iter = top_;

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
					printf("visited %d\n", stk_top->key_);
					if (iter != nullptr) printf("iter is %d ", iter->key_);
					if (last_node != nullptr) printf("last_node is %d ", last_node->key_);
					if (stk_top != nullptr) printf("stk_top is %d ", stk_top->key_);
					printf("\n");
					if (last_node != nullptr) printf("we DELETE %d\n", last_node->key_);
					delete last_node;
					last_node = stk_top;
				}
			}
			if (iter != nullptr) printf("iter is %d ", iter->key_);
			if (last_node != nullptr) printf("last_node is %d ", last_node->key_);
			if (stk_top != nullptr) printf("stk_top is %d ", stk_top->key_);
			printf("\n");
		}
		if (last_node != nullptr) printf("we DELETE %d\n", last_node->key_);
		delete last_node;
	}

	AVLTree::AVLTree(const AVLTree& other) {
		
		Node* iter = other.top_;
		//top_ = new Node(other.top_->key_, nullptr, nullptr, nullptr, other.top_->left_size_, other.top_->right_size_, other.top_->height_);
		Node* parent = nullptr;
		Node* clone = nullptr;
		//Node(key_t key = 0, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, int left_size = 0, int right_size = 0, int height = 1) :
		
		std::stack<Node*> stk;
		while (stk.size() != 0 || iter != nullptr) {
			if (iter != nullptr) {
				parent = clone;
				//printf("ITER IS %d\n", iter->key_);
				clone = new Node(iter->key_, nullptr, nullptr, nullptr, iter->left_size_, iter->right_size_, iter->height_);
				//printf("Clone is %d\n", clone->key_);
				clone->parent_ = parent;
				if (parent != nullptr) {
					if (parent != nullptr && parent->parent_ != nullptr) {
						printf("WE Up, parent - %d, parent-parent - %d\n", parent->key_, parent->parent_->key_);
						parent = parent->parent_;
					}
					if (clone->key_ < parent->key_) parent->left_ = clone;
					if (clone->key_ > parent->key_) parent->right_ = clone;

				}
				printf("visited %d\n", iter->key_);
				if (iter->right_ != nullptr) {
					stk.push(iter->right_);
				}
				iter = iter->left_;
			}
			else {
				iter = stk.top();
				stk.pop();

			}
			if (iter != nullptr) printf("iter is %d ", iter->key_);
			if (clone != nullptr) printf("clone is %d ", clone->key_);
			if (parent != nullptr) printf("parent is %d ", parent->key_);
			printf("\n");
		}
		printf("\n\n\nClone is %d\n", clone->key_);
		while (clone->parent_ != nullptr) clone = clone->parent_;
		top_ = clone;
		printf("Clone is %d\n", clone->key_);
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
				iter = iter->left_;
			}
			else if (iter->key_ == key) {
				printf("That key - %d is in tree!\n", key);
				return false;
			}
			else {
				parent = iter;
				iter = iter->right_;
			}
		}

		while (iter->parent_ != nullptr) { 
			iter = iter->balance(); 
			iter = iter->parent_;
		}
		while (top_->parent_ != nullptr) {
			top_ = top_->parent_;
		}

		return true;
	}

	int Node::height() {
		if (this != nullptr) return height_;
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