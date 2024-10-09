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
		//no duplicated element
	}


	//perform insertion (pp is the last searched node, p is the right place of thePair
	p = new SubtitleBSTNode(thePair);
	
	p->inserted_at = ++total_inserted;

	if (root != nullptr) //tree not empty
		if (thePair.first < pp->getSubTime()) pp->setLeft(p);
		else pp->setRight(p);
	else root = p; //if tree is empty

	return;
}
// Print

void SubtitleBST::PrintStructure(SubtitleBSTNode* node, int space, int height)
{
	if (node == nullptr) return;
	space += height;
	PrintStructure(node->getRight(), space);
	std::cout << std::endl;
	for (int i = height; i < space; i++) std::cout << " ";
	std::cout << node->inserted_at << "\n";

	PrintStructure(node->getLeft(), space);
}

// Search

// Delete
