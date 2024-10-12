#pragma once
#include "SubtitleBSTNode.h"
#include "SubtitleQueue.h"										//for SearchRange(). it uses SubtitleQueue as buffer.

class SubtitleBST
{
private:
	SubtitleBSTNode* root;
	
	/*Search(private)*/

	// SearchRange() Workhorse.
	// inorder Search BST node in the range of start_time ~ end_time, save data at buffer SubtitleQueue.
	// used in SECTION (...)
	void SearchRange(SubtitleBSTNode* const& pCur, const Time& start_time, const Time& end_time, SubtitleQueue* const& bufferSQ) const;

	/*Delete(private)*/
	
	// return one node with the matching delete_time, saves its parent pointer.
	// used in DELETE EQUAL delete_time
	SubtitleBSTNode* SearchEqual(const Time& delete_time, SubtitleBSTNode* parent) const;

	// DeleteUnder() Workhorse.
	// Post-Order delete every node under delete_time.
	// returns
	// used in DELETE UNDER delete_time
	SubtitleBSTNode* DeleteUnder(SubtitleBSTNode* node, const Time& delete_time, bool& deleted);
	
	// delete the node given. must need its parent info.
	// used in DELETE EQUAL delete_time / DELETE UNDER delete_time.
	void DeleteNode(SubtitleBSTNode*  nodeToDelete, SubtitleBSTNode* parent);
	
	//find the successor (minimum node in the subtree) with the root is given node value.
	// return the successor ptr, save successor at given reference.
	// used in DELETE EQUAL delete_time / DELETE UNDER delete_time
	SubtitleBSTNode* FindMin(SubtitleBSTNode* node, SubtitleBSTNode*& parent) const;
public:
	SubtitleBST();
	~SubtitleBST();

	SubtitleBSTNode* getRoot();		//return root

	/*Insert*/

	// make new node with given Datapair to data, insert in the right position.
	// used in QPOP
	void Insert(const Datapair& thePair);

	/*Print*/

	// PrintBST() Driver.
	// Print whole BST.
	// used in PRINT
	void PrintBST(ostream& os) const;

	// PrintBST() Workhorse.
	// Print whole BST inorder.
	// used in PRINT
	void PrintBST(ostream& os, SubtitleBSTNode* const& node) const;

	void PrintStructure(ostream& os, SubtitleBSTNode* node, int space) const;

	/*Search*/

	// SearchRange() Driver.
	// Search BST node in the range of start_time ~ end_time, save data at buffer SubtitleQueue.
	// bufferSQ saves section Datapairs.
	// used in SECTION (...)
	void SearchRange(const Time& start_time, const Time& end_time, SubtitleQueue* const& bufferSQ) const; //Driver
	
	/*Delete*/

	// Post-Order delete whole BST.
	// used in EXIT
	void DeleteBST(SubtitleBSTNode* const& node);

	// find and delete EVERY node that node subtitle Time = delete_time.
	// used in DELETE EQUAL delete_time
	void DeleteEveryEqual(const Time& delete_time);
	
	// DeleteUnder() Driver.
	// find and delete every node that node subtitle Time < delete_time.
	// used in DELETE UNDER delete_time
	void DeleteUnder(const Time& delete_time);
};
