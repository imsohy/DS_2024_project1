#pragma once
#include "SubtitleBSTNode.h"
#include "SubtitleQueue.h"										//for SearchRange(). it uses SubtitleQueue as buffer.

class SubtitleBST
{
private:
	SubtitleBSTNode* root;
	
	// Search (private)
	void SearchRange(SubtitleBSTNode* const& node, const Time& start_time, const Time& end_time, SubtitleQueue* const& bufferSQ) const; //Workhorse
public:
	SubtitleBST();
	~SubtitleBST();

	SubtitleBSTNode* getRoot();

	// Insert
	void Insert(const Datapair& thePair);
	// Print
	void PrintBST(ostream& os) const;
	void PrintBST(ostream& os, SubtitleBSTNode* const& node) const;
	// Search
	void SearchRange(const Time& start_time, const Time& end_time, SubtitleQueue* const& bufferSQ) const; //Driver
	// Delete

};
