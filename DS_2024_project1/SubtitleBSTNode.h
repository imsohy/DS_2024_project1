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

	//get property
	inline Time getSubTime() { return data.first; }
	inline string getSubString() { return data.second; }
	inline Datapair getData() { return data; }
	inline SubtitleBSTNode* getLeft() { return left; }
	inline SubtitleBSTNode* getRight() { return right; }

	//set property
	inline void setData(const Datapair& inputPair) { data = inputPair; }
	inline void setLeft(SubtitleBSTNode* left)		{ this->left = left; }
	inline void setRight(SubtitleBSTNode* right)	{ this->right = right; }

};
