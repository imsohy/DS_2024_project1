#pragma once
#include "Time.h"
#include <string>
class SubtitleQueueNode
{
private:
	//subtitle data
	Time subtitleTime;			//subtitle time
	std::string subtitleString;	//subtitle string

	//node link data
	SubtitleQueueNode* nextNode = nullptr;	//next SubtititleQueueNode;	 only accessible to SubtitleQueue and this class
public:
	SubtitleQueueNode() {};
	//setting data
	SubtitleQueueNode(const Time& inputTime, const std::string& inputString, SubtitleQueueNode* inputLink = nullptr) { 
		subtitleTime = inputTime;
		subtitleString = inputString;
		nextNode = inputLink;
	}
	//copy constructor only gets value
	SubtitleQueueNode(const SubtitleQueueNode& origin) {
		subtitleTime = origin.subtitleTime;
		subtitleString = origin.subtitleString;
		nextNode = nullptr;
	}
	~SubtitleQueueNode() {	}

	//getting data
	inline Time GetSubTime() { return subtitleTime; }		//get subtitleTime of this node
	inline std::string GetSubString() { return subtitleString; }	//get subtitleString of this node
	//getting next node
	inline SubtitleQueueNode* GetNext() {return nextNode;}			//get nextNode of this node
	//modify next node
	inline void SetNext(SubtitleQueueNode* const inputLink) { nextNode = inputLink; } //set next node
};
