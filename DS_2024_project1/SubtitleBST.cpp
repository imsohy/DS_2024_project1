#include "SubtitleBST.h"
#include <iostream>			//for debug

SubtitleBST::SubtitleBST() : root(nullptr)
{
	
}
SubtitleBST::~SubtitleBST()
{

}

SubtitleBSTNode* SubtitleBST::getRoot()
{
	return root;
}

// Insert
void SubtitleBST::Insert(const std::pair<Time, std::string>& thePair) 	//pp is the parent of the p
{
	SubtitleBSTNode* p = root, * pp = nullptr;
	//binary search the right place of thePair
	while (p) {
		pp = p;					//store current pointer
		if (thePair.first < p->getSubTime()) p = p->getLeft();
		else if (thePair.first > p->getSubTime()) p = p->getRight();
		else throw "fatal error: duplicated key node inserted";
	}

	//perform insertion (pp is the last searched node, p is the right place of thePair
	p = new SubtitleBSTNode(thePair);
	if (root != nullptr) //tree not empty
		if (thePair.first < pp->getSubTime()) pp->setLeft(p);
		else pp->setRight(p);
	else root = p; //if tree is empty

	return;
}
// Print

// Search

// Delete
