#pragma once
#include "basicheader.h"

class SubtitleQueueNode
{
private:
	//subtitle data
	Datapair data;

	//node link data
	SubtitleQueueNode* nextNode;	//next SubtititleQueueNode. initialized nullptr

public:
	//base constructor
	SubtitleQueueNode() : nextNode(nullptr) {};
	//constructor with parameter
	SubtitleQueueNode(const Time& inputTime, const std::string& inputString) { 
		data = std::make_pair(inputTime, inputString);
		nextNode = nullptr;
	}
	SubtitleQueueNode(const Datapair& inputPair) {
		data = inputPair;
		nextNode = nullptr;
	}
	//copy constructor only gets value
	SubtitleQueueNode(const SubtitleQueueNode& origin) {
		data = origin.data;
		nextNode = nullptr;
	}
	~SubtitleQueueNode() {	}

	//getting data
	inline Datapair GetData() { return data; }		//return data pair
	inline Time GetSubTime() { return data.first; }		//get subtitle Time of this node
	inline std::string GetSubString() { return data.second; }	//get subtitle String of this node
	//getting next node
	inline SubtitleQueueNode* GetNext() {return nextNode;}			//get nextNode of this node
	//modify next node
	inline void SetNext(SubtitleQueueNode* const inputLink) { nextNode = inputLink; } //set next node
};
