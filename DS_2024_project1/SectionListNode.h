#pragma once
#include "SubtitleListNode.h"

class SectionListNode
{
private:
	int section_num;						//section number
	SubtitleListNode*	subListHead;		//always start print whole section in SectionList::Search(), from the subListHead.
	SubtitleListNode*	subListTail;		//always Insert SubtitleListNode at the subListTail. 
	SectionListNode*	next;				//next SectionListNode
	
public:
	SectionListNode(int section_num) : section_num(section_num), 
		subListHead(nullptr), subListTail(nullptr), next(nullptr) {}
	~SectionListNode() {
		SubtitleListNode* deleteNode = nullptr;
		while (subListHead != nullptr)
		{
			deleteNode = subListHead;
			subListHead = subListHead->getNext();
			delete deleteNode;
		}
	}
	inline int getSectionNum() { return section_num;  }
	inline SubtitleListNode* getSubListHead() { return subListHead; }
	inline SubtitleListNode* getSubListTail() { return subListTail; }
	inline void setSubListHead(SubtitleListNode* const& newhead) { subListHead = newhead; }
	inline void setSubListTail(SubtitleListNode* const& newtail) { subListTail = newtail; }
	SectionListNode*	getNext()		 	{ return next; }						
	void setNext(SectionListNode* next)	 					{ this->next = next; }
};
