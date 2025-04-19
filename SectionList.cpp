#include "SectionList.h"
SectionList::SectionList(): head(nullptr), tail(nullptr)
{

}
SectionList::~SectionList()
{
	SectionListNode* deleteNode = nullptr;
	while (head != nullptr) {
		deleteNode = head;
		head = head->getNext();
		delete deleteNode;
	}
}

SectionListNode* SectionList::getHead()
{
	return head;
}

// Insert
// Insert - Generate new section header at the tail.
void SectionList::GenerateNewSection(const int& section_num)
{
	//generate new section header node
	SectionListNode* newSectionHeader = new SectionListNode(section_num);
	if (head == nullptr)	//if SectionList is empty, insert new section header as SectionList head.
		head = tail = newSectionHeader;	
	else //if SectionList is not empty, insert new section header to tail.
	{
		tail->setNext(newSectionHeader);			//set current tail's next SectionListNode to newnode
		tail= tail->getNext();						//set tail to it.
	}
}
// Insert - insert new SubtitleListNode, to the sublistTail of tail. (tail = section header)
void SectionList::InsertSubtitle(Datapair inputData)
{
	//generate new subtitle list node
	SubtitleListNode* newSublistNode = new SubtitleListNode(inputData);
	if (tail->getSubListHead() == nullptr) // if section_header's subtitle list is empty, insert newSubtitleListNode as subtitle list head.
	{
		tail->setSubListHead(newSublistNode);
		tail->setSubListTail(newSublistNode);
	}
	else //if subtitle list is not empty, insert new subtitle list node to its tail
	{
		tail->getSubListTail()->setNext(newSublistNode); //set the subtitle list tail's nextnode to new SubtitleListNode
		tail->setSubListTail(tail->getSubListTail()->getNext()); //move the subtitle list tail to its nextnode
	}
}
// Search - Search the matching section
SectionListNode* SectionList::Search(ostream& os, const int& key_section_num)
{
	SectionListNode* section_walker = head;		//start Search() from head

	//search SectionListNode with the section number
	while (section_walker != nullptr)
	{
		if (section_walker->getSectionNum() == key_section_num) break;	//if section number equals to the key, break.
		else section_walker = section_walker->getNext();	//else, move walker to next node 
	} //walker points the section header with key section number
	if (section_walker == nullptr) throw "no such section number";	//section number not found
	
	return section_walker;		//return found section header
}
// Print - print section node. search is needed first.
void SectionList::PrintSection(ostream& os, SectionListNode* const section_header) const {
	
	SubtitleListNode* subtitle_walker = section_header->getSubListHead(); //start PrintSection() fron sublist head
	//print section informantion
	os << "Section " << section_header->getSectionNum() << endl;
	//print subtitle list
	while (subtitle_walker != nullptr)
	{
		os << subtitle_walker->getSubTime() << " - " << subtitle_walker->getSubString() << endl;
		subtitle_walker = subtitle_walker->getNext();
	}
}