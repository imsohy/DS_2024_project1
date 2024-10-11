#pragma once
#include "SubtitleQueueNode.h"

//Subtitle Queue, linked list data structure
class SubtitleQueue
{
private:
	SubtitleQueueNode* front;				//new element is popped from here	
	SubtitleQueueNode* rear;				//new element is pushed to here
	short capacity;							//queue capacity. = 100 if the value is not given
	short nodecnt;							//counter. counts number of nodes inside the queue
public:
	SubtitleQueue(int queueCapacity = CAP);		
	~SubtitleQueue();						//have pointer, must be called

	bool IsEmpty() const;					//returns true if nodecnt == 0
	bool IsFull() const;					//returns true if nodecnt == capacity
	void Push(const Time& inputTime, const std::string& inputSub);	//if the queue is not full, push new SubtitleQueueNode on rear
	void Push(const Datapair& inputPair);
	Datapair Pop();					//if the queue is not empty, return the front data as pair, pop.
	Datapair Front() const;			//if the queue is not empty, return the front data as pair.
	void PrintQueue(std::ostream& os);			//print data from the front to the rear

	//for debug
	inline short GetNodeCnt() { return nodecnt; }	//returns nodecnt;
};
