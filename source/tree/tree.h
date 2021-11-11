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

		int left_depth_;
		int right_depth_;

		Node(key_t key = 0, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) :
			key_(key),
			left_(left),
			right_(right),
			parent_(parent),
			left_size_(0),
			right_size_(0),
			left_depth_(0),
			right_depth_(0) {}

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