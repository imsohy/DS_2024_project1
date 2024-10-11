#include "SubtitleBST.h"


SubtitleBST::SubtitleBST() : root(nullptr) {}
SubtitleBST::~SubtitleBST()
{
	//delete entire BSTnodes with post-traversal
	
}

SubtitleBSTNode* SubtitleBST::getRoot()
{
	return root;
}

// Insert
void SubtitleBST::Insert(const Datapair& thePair) 					//pp is the parent of the p
{
	SubtitleBSTNode* p = root, * pp = nullptr;
	//binary search the right place of thePair, key = Time
	while (p) {
		pp = p;														//store current pointer
		if (thePair.first < p->getSubTime()) p = p->getLeft();
		else if (thePair.first >= p->getSubTime()) p = p->getRight();
	}

	//perform insertion (pp is the last searched node, p is the searched place of thePair
	p = new SubtitleBSTNode(thePair);
	if (root != nullptr)											//tree not empty
		if (thePair.first < pp->getSubTime()) pp->setLeft(p);		// insert pair key < last searched node key 
		else pp->setRight(p);										// insert pair key >= last searched node key
	else root = p;													 //if tree is empty

	return;
}

// Search (BST node in the range of start_time ~ end_time, save data at buffer SubtitleQueue)
// Search - Driver
void SubtitleBST::SearchRange(const Time& start_time, const Time& end_time, SubtitleQueue* const& bufferSQ) const
{
	SearchRange(root, start_time, end_time, bufferSQ);
}
// Search - Workhorse
void SubtitleBST::SearchRange(SubtitleBSTNode* const& node, const Time& start_time,
	const Time& end_time, SubtitleQueue* const& bufferSQ) const //Workhorse
{
	if (node == nullptr) return; //if current node is leaf
	//inorder range search.
	// if current node key is greater than start_time, search left subtree Recursively.
	if (node->getSubTime() > start_time)
		SearchRange(node->getLeft(), start_time, end_time, bufferSQ);
	// if current node key is in the range of [start_time, end_time], add to buffer SubtitleQueue
	if (node->getSubTime() >= start_time && node->getSubTime() <= end_time)
		bufferSQ->Push(node->getData());
	// if current node key is lesser than or equal to end_time, search right subtree Recursively.
	if (node->getSubTime() <= end_time)
		SearchRange(node->getRight(), start_time, end_time, bufferSQ);
}
// Print (BST inorder)
// Print - Driver
void SubtitleBST::PrintBST(ostream& os) const {
	PrintBST(os, root);
}
// Print - Workhorse
void SubtitleBST::PrintBST(ostream& os, SubtitleBSTNode* const & node) const{
	//inorder visit
	if (node)
	{
		PrintBST(os, node->getLeft());
		os << node->getSubTime() << " - " << node->getSubString() << endl;
		PrintBST(os, node->getRight());
	}
}
// Delete
