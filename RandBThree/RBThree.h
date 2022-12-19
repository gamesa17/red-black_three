#pragma once

#include "RBNode.h"
#include "Three.h"

typedef RBNode* RBNodePtr;

class RBThree : public Three<RBNode>
{
private:

	RBNodePtr root;
	RBNodePtr TNULL;

	void initializeNULLNode(RBNodePtr node, RBNodePtr parent);
	void preOrderHelper(RBNodePtr node);
	void inOrderHelper(RBNodePtr node);
	void postOrderHelper(RBNodePtr node);
	RBNodePtr searchTreeHelper(RBNodePtr node, int key);
	void fixDelete(RBNodePtr x);
	void rbTransplant(RBNodePtr u, RBNodePtr v);
	void deleteNodeHelper(RBNodePtr node, int key);
	void fixInsert(RBNodePtr k);
	void printHelper(RBNodePtr root, std::string indent, bool last);


public:
	RBThree();
	~RBThree();

	void preorder();
	void inorder();
	void postorder();
	RBNodePtr searchTree(int k);
	RBNodePtr minimum(RBNodePtr node);
	RBNodePtr maximum(RBNodePtr node);
	RBNodePtr successor(RBNodePtr x);
	RBNodePtr predecessor(RBNodePtr x);
	RBNodePtr leftRotate(RBNodePtr x) override;
	RBNodePtr rightRotate(RBNodePtr x) override;
	void insert(int key) override;
	void deleteNode(int data) override;
	void prettyPrint() override;
	RBNodePtr getRoot();

};