#pragma once
#include "basicheader.h"
class SubtitleListNode
{
private:
	Datapair data;
	SubtitleListNode*	next;

public:
	SubtitleListNode(const Datapair& inputdata) : next(nullptr), data(inputdata){}
	~SubtitleListNode() {}
	
	inline Time getSubTime() { return data.first; }
	inline string getSubString() { return data.second; }
	SubtitleListNode*	getNext()			{ return next; }

	void setNext(SubtitleListNode* next)	 	{ this->next = next; }
};
