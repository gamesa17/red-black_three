#pragma once

#include <iostream>
#include "Node.h"

class RBNode : public Node
{
public:
	int color = 0;

	RBNode* right = nullptr;
	RBNode* left = nullptr;
	RBNode* parent = parent;

	RBNode();

};