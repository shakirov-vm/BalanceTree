#include <cstdio>

#include "tree.h"

namespace avl_tree {

	/*Node* AVLTree::insert(Node* node, key_t key) {

		if (node == nullptr) return new Node(key);
		if (key < node->key_) {
			node->left_ = insert(node->left_, key);
		}
		else if (node->key_ == key) {
			printf("That key - %d is in tree!\n", key);
			return balance(node); // ???
		}
		else {
			node->right_ = insert(node->right_, key);
		}
		return balance(node);
	}*/

	Node* AVLTree::insert(Node* node, key_t key) {

		if (!node) return new Node(key);
		if (key < node->key_) {
			node->left_ = insert(node->left_, key);
		}
		else {
			node->right_ = insert(node->right_, key);
		}
		//bad:
		Node* top = node;
		while (top->parent_ != nullptr) top = top->parent_;
		top_ = top;
		return balance(node);
	}

	/*bool AVLTree::insert(key_t key) {

		if (top_ == nullptr) {
			top_ = new Node{ key };
			return true;
		}

		Node* iter = top_;

		while (true) {
			printf("iter_key - %d, key - %d\n", iter->key_, key);

			//iter->balance();
			if (iter->key_ > key) {
				if (iter->left_ == nullptr) { // or >=?
					iter->left_ = new Node{ key, 1, nullptr, nullptr, iter };
					iter = iter->left_;
					printf("We push %d\n", iter->key_);
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
					iter->right_ = new Node{ key, 1, nullptr, nullptr, iter };
					iter = iter->right_;
					printf("We push %d\n", iter->key_);
					break;
				}

				iter = iter->right_;
			}
		}

		//iter->balance();
		//while (iter->parent_ != nullptr) {
		printf("\n");
		do {	??????????????????????
			printf("Before: key - %d, I am - %p, left - %p, rigth - %p, parent - %p\n\n", iter->key_, iter, iter->left_, iter->right_, iter->parent_);
			iter = iter->balance();
			printf("Before: key - %d, I am - %p, left - %p, rigth - %p, parent - %p\n\n", iter->key_, iter, iter->left_, iter->right_, iter->parent_);
			iter = iter->parent_;
		} while (iter->parent_ != nullptr);

		return true;
	}*/


	//void Node::fixheight() {
		/*if (parent_ != nullptr) printf("Parent - %p ", parent_);
		if (this != nullptr) printf("this - %p ", this);
		if (left_ != nullptr) printf("left - %p ", left_);
		if (right_ != nullptr) printf("right - %p ", right_);
		printf("\n");*/

		/*int height_left, height_right;

		if (left_ == nullptr) height_left = 0;
		else height_left = left_->height_;

		if (right_ == nullptr) height_right = 0;
		else height_right = right_->height_;*/

		/*int height_left = left_->height();
		int height_right = right_->height();
		if (height_left > height_right) height_ = height_left + 1;
		else height_ = height_right + 1;
	}*/
	int Node::height() {
		if (this == nullptr) return 0;
		else return height_;
	}

	int Node::balance_factor() {
		//printf("AND NODE IS %p\n", this);
		if (this == nullptr) printf("ALARM\n");
		return right_->height() - left_->height();
	}


	void Node::fixheight() {
	
		int height_left = left_->height();
		int height_right = right_->height();
		height_ = (height_left > height_right ? height_left : height_right) + 1;
	}
////////////////////////////////////////////////////////////////////////////////////////Must we fill parents??
	Node* AVLTree::right_rotate(Node* node) { //node это ось

		/*if (node == top_) {
			printf("Need redo top\n");
			top_ = node->left_;
		}*/

		Node* lifted = node->left_;

		lifted->parent_ = node->parent_;
		node->parent_ = lifted;

		node->left_ = lifted->right_;
		lifted->right_ = node;

		/*if (top_ == lifted) {
			printf("NO\n");
			printf("lifted - %p, node - %p\n", lifted->parent_, node->parent_);
			lifted->parent_ = nullptr;
			node->parent_ = lifted;
		}*/

		node->fixheight();
		lifted->fixheight();
		return lifted;
	}

	Node* AVLTree::left_rotate(Node* node) { //node это ось
		/*if (node == top_) {
			printf("Need redo top\n");
			top_ = node->right_;
		}
		*/
		Node* lifted = node->right_;

		lifted->parent_ = node->parent_;
		node->parent_ = lifted;

		node->right_ = lifted->left_;
		lifted->left_ = node;

		/*if (top_ == lifted) {
			printf("YES");
			printf("lifted - %p, node - %p\n", lifted->parent_, node->parent_);
			lifted->parent_ = nullptr;
			node->parent_ = lifted;
		}*/

		node->fixheight();
		lifted->fixheight();
		return lifted;
	}

	Node* AVLTree::balance(Node* node) {

		node->fixheight();
		//printf("Node - %p, parent - %p, key - %d\n", node, node->parent_, node->key_);
		//printf("NODE IS %p\n", node);
		if (node->balance_factor() == 2) {
			//printf("Go to 2, height - %d, left - %p, right - %p\n", node->height(), node->left_, node->right_);
			if (node->right_->balance_factor() < 0) node->right_ = right_rotate(node->right_);
			return left_rotate(node);
		}
		if (node->balance_factor() == -2) {
			//printf("Go to -2, height - %d, left - %p, right - %p\n", node->height(), node->left_, node->right_);
			if (node->left_->balance_factor() > 0) node->left_ = left_rotate(node->left_);
			return right_rotate(node);
		}
		return node; // балансировка не нужна
	}

}