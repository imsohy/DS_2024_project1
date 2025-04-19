#ifndef MANAGER_H
#define MANAGER_H
#include "basicheader.h"		//include several headers in basicheader.h
#include "SubtitleQueue.h"
#include "SubtitleBST.h"
#include "SectionList.h"
#include <fstream>


class Manager
{
private:
	SubtitleQueue* SQptr = nullptr;		//saves SubtitleQueue instance during Run()
	SubtitleBST* SBSTptr = nullptr;		//saves SubtitleBST instance during Run()
	SectionList* SLptr = nullptr;		//saves SectionList instance during Run()
	ifstream fcmd;
	ofstream flog;
public:
	Manager();
	~Manager();

	void Run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	void Load();
	// QPOP
	void Qpop();
	// PRINT
	void Print();
	void Print(const int& section_num);
	// SECTION
	void Section(const int& section_num, const Time& start_time, const Time& end_time);
	// DELETE
	void DeleteEqual(const Time& key_time);
	void DeleteUnder(const Time& key_time);

};
#endif //MANAGER_H