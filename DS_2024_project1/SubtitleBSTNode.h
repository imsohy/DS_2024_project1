#pragma once
#include "basicheader.h"

class SubtitleBSTNode
{
private:
	//data field
	Datapair data;

	//BST node specification
	SubtitleBSTNode*	left;
	SubtitleBSTNode*	right;

public:

	SubtitleBSTNode() : left(nullptr), right(nullptr) {}
	SubtitleBSTNode(Datapair inputPair) : left(nullptr), right(nullptr), data(inputPair) {}
	~SubtitleBSTNode() {}

	Time getSubTime() { return data.first; }
	std::string getSubString() { return data.second; }
	Datapair getData() { return data; }
	SubtitleBSTNode*	getLeft()				{ return left; }
	SubtitleBSTNode*	getRight()				{ return right; }

	void setLeft(SubtitleBSTNode* left)		{ this->left = left; }
	void setRight(SubtitleBSTNode* right)	{ this->right = right; }

};
