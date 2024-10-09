#pragma once
#include "Time.h"
#include <string>
class SubtitleQueueNode
{
private:
	Time subtitleTime;			//subtitle time
	std::string subtitleData;	//subtitle data
public:
	SubtitleQueueNode(const Time& input_subtitleTime, const std::string& input_subtitleData) { 
		this->subtitleTime = input_subtitleTime;
		this->subtitleData = input_subtitleData;
	}
	~SubtitleQueueNode() { }
};
