#ifndef SUBTITLEBST_H
#define SUBTITLEBST_H
#include "SubtitleBSTNode.h"
#include "SubtitleQueue.h" //for SearchRange(). it uses SubtitleQueue as buffer.

// /**/: the smallest operation this method do.
// used in: the biggest operation this method do.
// called by: function that calles this method.
class SubtitleBST
{
private:
	SubtitleBSTNode* root;
	/*Print(private)*/

	// PrintBST() Workhorse. Print whole BST inorder.
	// used in: PRINT
	// called by SubtitleBST::PrintBST()
	void PrintBST(ostream& output_stream, SubtitleBSTNode* const& node_recurse_start) const;

	/*Search(private)*/

	// SearchRange() Workhorse. 
	// inorder Search BST node in the range of start_time ~ end_time, save data at buffer SubtitleQueue.
	// used in: SECTION (...)
	// called by: SubtitleBST::Searchrange()
	void SearchRange(SubtitleBSTNode* const& pCur, 
		const Time& start_time, const Time& end_time, SubtitleQueue* const& bufferSQ) const;

	// return one node with the matching delete_time, saves its parent pointer.
	// used in: DELETE EQUAL delete_time
	// called by: SubtitleBST::DeleteEveryEqual().
	SubtitleBSTNode* SearchEqual(const Time& delete_time, SubtitleBSTNode* parent) const;

	// Search the successor (minimum node in the subtree) with the root is given node value.
	// return the successor ptr, save successor at parent reference.
	// used in: DELETE EQUAL delete_time / DELETE UNDER delete_time
	// called by: SubtitleBST::DeleteNode().
	SubtitleBSTNode* FindMin(SubtitleBSTNode* node, SubtitleBSTNode*& parent) const;

	/*Delete(private)*/
	
	// DeleteUnder() Workhorse. return recurrence result of pCur's childnode.
	// Post-Order tree traversal.
	// used in: DELETE UNDER delete_time
	// called by: SubtitleBST::DeleteUnder()
	SubtitleBSTNode* DeleteUnder(const Time& delete_time, SubtitleBSTNode* pCur, SubtitleBSTNode* pPar, bool& deleted);
	
	// delete the node given. must need its parent info.
	// used in: DELETE EQUAL delete_time / DELETE UNDER delete_time.
	// called by: SubtitleBST::DeleteEveryEqual(), SubtitleBST::DeleteUnder()
	void DeleteNode(SubtitleBSTNode*  nodeToDelete, SubtitleBSTNode* parent);

public:
	SubtitleBST();
	~SubtitleBST();
	SubtitleBSTNode* getRoot();		//return root

	/*Insert*/

	// make new node with given Datapair to data, insert in the right position.
	// used in: INSERT
	// called by: Manager::Insert()
	void Insert(const Datapair& thePair);

	/*Print*/

	// PrintBST() Driver. Print whole BST.
	// used in: PRINT
	// called by Manager::Print()
	void PrintBST(ostream& output_stream) const;

	// print tree structure (turned to left 90 degree)
	// used for debug.
	void PrintStructure(ostream& output_stream, SubtitleBSTNode* node_recurse_start, int space) const;

	/*Search*/

	// SearchRange() Driver.
	// Search BST node in the range of start_time ~ end_time, save data at buffer SubtitleQueue.
	// used in: SECTION (...)
	// called by: Manager::Section()
	void SearchRange(const Time& start_time, const Time& end_time, SubtitleQueue* const& bufferSQ) const; //Driver
	
	/*Delete*/

	// delete whole BST by Post-order traversal.
	// used in: EXIT
	// called by SubtitleBST::~Subtitle()
	void DeleteBST(SubtitleBSTNode* const& node);

	// DeleteEveryEqual() Driver.
	// find and delete EVERY node that node subtitle Time = delete_time.
	// used in: DELETE EQUAL delete_time
	// called by: Manager::DeleteEqual()
	void DeleteEveryEqual(const Time& delete_time);
	
	// DeleteUnder() Driver.
	// find and delete every node that node subtitle Time < delete_time.
	// used in DELETE UNDER delete_time
	// called by: Manager::DeleteUnder()
	void DeleteUnder(const Time& delete_time);
};

#endif //SUBTITLEBST_H
