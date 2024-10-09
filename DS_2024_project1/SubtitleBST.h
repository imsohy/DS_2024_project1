#pragma once
#include "SubtitleBSTNode.h"

class SubtitleBST
{
private:
	SubtitleBSTNode* root = nullptr;
public:
	SubtitleBST();
	~SubtitleBST();

	SubtitleBSTNode* getRoot();

	// Insert
	void Insert(const std::pair<Time, std::string>& thePair);
	// Print
	
	// Search
	// Delete

};
