#pragma once
#include "Node.h"


template<class Node>

class Three abstract
{
private:
	Node* root;
	Node* TNULL;

public:
	virtual Node* leftRotate(Node*) = 0;
	virtual Node* rightRotate(Node*) = 0;
	virtual void insert(int key) = 0;
	virtual void deleteNode(int key) = 0 ;
	virtual void prettyPrint() = 0;

};