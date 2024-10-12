#pragma once
#include "SectionListNode.h"

class SectionList
{
private:
	SectionListNode* head;				//always start Search() from the head
	SectionListNode* tail;				//always GenerateNewSection() to the tail. tail = section header.

public:
	SectionList();
	~SectionList();

	//get property
	SectionListNode* getHead();

	// Insert
	void GenerateNewSection(const int& section_num);			//insert new SectionListNode at the tail (= section header)
	void InsertSubtitle(Datapair inputData);				//insert new SubtitleListNode, at the subListTail of tail.
	// Search
	SectionListNode * Search(ostream& os, const int& key_section_num);							//search the matching section number
	// Print
	void PrintSection(ostream& os, SectionListNode* const) const;
};
