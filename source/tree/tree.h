#pragma once

namespace avl_tree {

	using key_t = int;

	struct Node {
		key_t key_;
		Node* left_;
		Node* right_;
		Node* parent_;

		int left_size_;
		int right_size_;

		int height_;

		Node(key_t key = 0, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) :
			key_(key),
			left_(left),
			right_(right),
			parent_(parent),
			left_size_(0),
			right_size_(0),
			height_(1) {}

		void dump() {
			if (this == nullptr) {
				printf("node is nullptr\n");
				return;
			}
			printf("node is %d ", key_);
			if (left_ != nullptr) printf("left is %d, ", left_->key_);
			if (right_ != nullptr) printf("right is %d, ", right_->key_);
			if (parent_ != nullptr) printf("parent is %d, ", parent_->key_);
			printf("\n");
		}

		int balance_factor();
		void fix_height();
		int height();
		Node* balance();
		Node* left_rotate();
		Node* right_rotate();

	};

	class AVLTree {
		Node* top_;

	public:

		AVLTree(key_t key = 0) {
			top_ = new Node(key);
		}
		bool insert(key_t key);
		void dump();

	};

	int depth_calc(Node* child, Node* parent, int add);


	FILE* FileOpen(const char* text, const char* mode);
	void print_graph(Node* node, FILE* potok);

}



/*
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
	printf("Right rotate: lifted - %d, node - %d\n", lifted->key_, key_);
	//if ((parent_ != nullptr) && (parent_->left_ = this)) parent_->left_ = lifted;
	//if ((parent_ != nullptr) && (parent_->right_ = this)) parent_->right_ = lifted;

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
	printf("Left rotate: lifted - %d, node - %d\n", lifted->key_, key_);
	//if ((parent_ != nullptr) && (parent_->left_ = this)) parent_->left_ = lifted;
	//if ((parent_ != nullptr) && (parent_->right_ = this)) parent_->right_ = lifted;

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

Node* Node::insert_process(Node* node, key_t key) {

	if (node == nullptr) {
		printf("We do new node - %d\n", key);
		return new Node(key, 1, nullptr, nullptr, node);
	}
	if (key < node->key_) {
		node->left_ = insert_process(node->left_, key);
	}
	else {
		node->right_ = insert_process(node->right_, key);
	}
	return node->balance();
}

void AVLTree::recalculate_top() {
	printf("top before - %d\n", top_->key_);
	while (top_->parent_ != nullptr) top_ = top_->parent_;
	printf("top after - %d\n", top_->key_);
}

Node* AVLTree::insert(key_t key) {
	Node* node = top_->insert_process(top_, key);
	recalculate_top();
	return node;
}*/