#ifndef SECTIONLISTNODE_H
#define SECTIONLISTNODE_H
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
	~SectionListNode() {					//delete every subtitle list node repeatedly from sublisthead
		SubtitleListNode* deleteNode = nullptr;
		while (subListHead != nullptr)
		{
			deleteNode = subListHead;		//save current sublisthead
			subListHead = subListHead->getNext(); //move sublisthead to next
			delete deleteNode;				//delete before sublisthead
		}
	}
	//get property
	inline int getSectionNum() { return section_num;  }
	inline SubtitleListNode* getSubListHead() { return subListHead; }
	inline SubtitleListNode* getSubListTail() { return subListTail; }
	SectionListNode* getNext() { return next; }

	//set property
	inline void setSubListHead(SubtitleListNode* const& newhead) { subListHead = newhead; }
	inline void setSubListTail(SubtitleListNode* const& newtail) { subListTail = newtail; }
	void setNext(SectionListNode* next)	 					{ this->next = next; }
};
#endif //SECTIONLISTNODE_H