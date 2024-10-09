#pragma once
#include "Time.h"
#include <string>
#include <utility>

class SubtitleBSTNode
{
private:
	//data field
	std::pair<Time, std::string> data;

	//BST node specification
	SubtitleBSTNode*	left;
	SubtitleBSTNode*	right;

public:

	SubtitleBSTNode() : left(nullptr), right(nullptr) {}
	SubtitleBSTNode(std::pair<Time, std::string> inputPair) : left(nullptr), right(nullptr), data(inputPair) {}
	~SubtitleBSTNode() {}

	Time getSubTime() { return data.first; }
	std::string getSubString() { return data.second; }
	SubtitleBSTNode*	getLeft()				{ return left; }
	SubtitleBSTNode*	getRight()				{ return right; }

	void setLeft(SubtitleBSTNode* left)		{ this->left = left; }
	void setRight(SubtitleBSTNode* right)	{ this->right = right; }

	short inserted_at = 0;				//remembers what line this data was in SubtitleQueue, for debug
};
