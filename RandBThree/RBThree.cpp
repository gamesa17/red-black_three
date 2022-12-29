#include <string>
#include "RBThree.h"


RBThree::RBThree()
{
	TNULL = new RBNode();
	TNULL->color = 0;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	root = TNULL;
}
RBThree::~RBThree() {}


void RBThree::initializeNULLNode(RBNodePtr node, RBNodePtr parent) {
	node->key = 0;
	node->parent = parent;
	node->left = nullptr;
	node->right = nullptr;
	node->color = 0;
}

void RBThree::preOrderHelper(RBNodePtr node) {
	if (node != TNULL) {
		std::cout << node->key << " ";
		preOrderHelper(node->left);
		preOrderHelper(node->right);
	}
}

void RBThree::inOrderHelper(RBNodePtr node) {
	if (node != TNULL) {
		inOrderHelper(node->left);
		std::cout << node->key << " ";
		inOrderHelper(node->right);
	}
}

void RBThree::postOrderHelper(RBNodePtr node) {
	if (node != TNULL) {
		postOrderHelper(node->left);
		postOrderHelper(node->right);
		std::cout << node->key << " ";
	}
}

RBNodePtr RBThree::searchTreeHelper(RBNodePtr node, int key) {
	if (node == TNULL || key == node->key) {
		return node;
	}

	if (key < node->key) {
		return searchTreeHelper(node->left, key);
	}
	return searchTreeHelper(node->right, key);
}

void RBThree::fixDelete(RBNodePtr x) {
	RBNodePtr s;
	while (x != root && x->color == 0) {
		if (x == x->parent->left) {
			s = x->parent->right;
			if (s->color == 1) {
				s->color = 0;
				x->parent->color = 1;
				leftRotate(x->parent);
				s = x->parent->right;
			}

			if (s->left->color == 0 && s->right->color == 0) {
				s->color = 1;
				x = x->parent;
			}
			else {
				if (s->right->color == 0) {
					s->left->color = 0;
					s->color = 1;
					rightRotate(s);
					s = x->parent->right;
				}

				s->color = x->parent->color;
				x->parent->color = 0;
				s->right->color = 0;
				leftRotate(x->parent);
				x = root;
			}
		}
		else {
			s = x->parent->left;
			if (s->color == 1) {
				s->color = 0;
				x->parent->color = 1;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->right->color == 0 && s->right->color == 0) {
				s->color = 1;
				x = x->parent;
			}
			else {
				if (s->left->color == 0) {
					s->right->color = 0;
					s->color = 1;
					leftRotate(s);
					s = x->parent->left;
				}

				s->color = x->parent->color;
				x->parent->color = 0;
				s->left->color = 0;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 0;
}

void RBThree::rbTransplant(RBNodePtr u, RBNodePtr v) {
	if (u->parent == nullptr) {
		root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void RBThree::deleteNodeHelper(RBNodePtr node, int key) {
	RBNodePtr z = TNULL;
	RBNodePtr x, y;
	while (node != TNULL) {
		if (node->key == key) {
			z = node;
		}

		if (node->key <= key) {
			node = node->right;
		}
		else {
			node = node->left;
		}
	}

	if (z == TNULL) {
		std::cout << "Не удалось найти узел с данным ключом." << std::endl;
		return;
	}

	y = z;
	int y_original_color = y->color;
	if (z->left == TNULL) {
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if (z->right == TNULL) {
		x = z->left;
		rbTransplant(z, z->left);
	}
	else {
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		}
		else {
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (y_original_color == 0) {
		fixDelete(x);
	}
}

void RBThree::fixInsert(RBNodePtr k) {
	RBNodePtr u;
	while (k->parent->color == 1) {
		if (k->parent == k->parent->parent->right) {
			u = k->parent->parent->left;
			if (u->color == 1) {
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->left) {
					k = k->parent;
					rightRotate(k);
				}
				k->parent->color = 0;
				k->parent->parent->color = 1;
				leftRotate(k->parent->parent);
			}
		}
		else {
			u = k->parent->parent->right;

			if (u->color == 1) {
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->right) {
					k = k->parent;
					leftRotate(k);
				}
				k->parent->color = 0;
				k->parent->parent->color = 1;
				rightRotate(k->parent->parent);
			}
		}
		if (k == root) {
			break;
		}
	}
	root->color = 0;
}

void RBThree::printHelper(RBNodePtr root, std::string indent, bool last) {
	if (root != TNULL) {
		std::cout << indent;
		if (last) {
			std::cout << "R----";
			indent += "     ";
		}
		else {
			std::cout << "L----";
			indent += "|    ";
		}

		std::string sColor = root->color ? "RED" : "BLACK";
		std::cout << root->key << "(" << sColor << ")" << std::endl;
		printHelper(root->left, indent, false);
		printHelper(root->right, indent, true);
	}
}

void RBThree::preorder()
{
	std::cout << "Pre-Order Traversal of Three: " << std::endl;
	preOrderHelper(this->root);
}

void RBThree::inorder() {
	std::cout << "In-Order Traversal of Three: " << std::endl;
	inOrderHelper(this->root);
}

void RBThree::postorder() {
	std::cout << "Post-Order Traversal of Three: " << std::endl;
	postOrderHelper(this->root);
}

RBNodePtr RBThree::searchTree(int k) {
	return searchTreeHelper(this->root, k);
}

RBNodePtr RBThree::minimum(RBNodePtr node) {
	while (node->left != TNULL) {
		node = node->left;
	}
	return node;
}

RBNodePtr RBThree::maximum(RBNodePtr node) {
	while (node->right != TNULL) {
		node = node->right;
	}
	return node;
}

RBNodePtr RBThree::successor(RBNodePtr x) {
	if (x->right != TNULL) {
		return minimum(x->right);
	}

	RBNodePtr y = x->parent;
	while (y != TNULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

RBNodePtr RBThree::predecessor(RBNodePtr x) {
	if (x->left != TNULL) {
		return maximum(x->left);
	}

	RBNodePtr y = x->parent;
	while (y != TNULL && x == y->left) {
		x = y;
		y = y->parent;
	}

	return y;
}

RBNodePtr RBThree::leftRotate(RBNodePtr x) {
	RBNodePtr y = x->right;
	x->right = y->left;
	if (y->left != TNULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;

	return x, y;
}

RBNodePtr RBThree::rightRotate(RBNodePtr x) {
	RBNodePtr y = x->left;
	x->left = y->right;
	if (y->right != TNULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	}
	else if (x == x->parent->right) {
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;

	return x, y;
}

void RBThree::insert(int key) {
	RBNodePtr node = new RBNode;
	node->parent = nullptr;
	node->key = key;
	node->left = TNULL;
	node->right = TNULL;
	node->color = 1;

	RBNodePtr y = nullptr;
	RBNodePtr x = this->root;

	while (x != TNULL) {
		y = x;
		if (node->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	node->parent = y;
	if (y == nullptr) {
		root = node;
	}
	else if (node->key < y->key) {
		y->left = node;
	}
	else {
		y->right = node;
	}

	if (node->parent == nullptr) {
		node->color = 0;
		return;
	}

	if (node->parent->parent == nullptr) {
		return;
	}

	fixInsert(node);
}

RBNodePtr RBThree::getRoot() {
	return this->root;
}

void RBThree::deleteNode(int data) {
	deleteNodeHelper(this->root, data);
}

void RBThree::prettyPrint() {
	if (root) {
		printHelper(this->root, "", true);
	}
}
