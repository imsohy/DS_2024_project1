#ifndef SUBTITLELISTNODE_H
#define SUBTITLELISTNODE_H
#include "basicheader.h"
class SubtitleListNode
{
private:
	Datapair data; //subtitle time, subtitle data
	SubtitleListNode*	next;

public:
	SubtitleListNode(const Datapair& inputdata) : next(nullptr), data(inputdata){}
	~SubtitleListNode() {}
	
	//get property
	inline Time getSubTime() { return data.first; }
	inline string getSubString() { return data.second; }
	SubtitleListNode*	getNext()			{ return next; }

	//set property
	void setNext(SubtitleListNode* next)	 	{ this->next = next; }
};
#endif //SUBTITLELISTNODE_H