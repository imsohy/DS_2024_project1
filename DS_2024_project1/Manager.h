#pragma once
#include "SubtitleQueue.h"
#include "SubtitleBST.h"
#include "SectionList.h"
#include "Time.h"
#include <fstream>
#include <sstream>							//to read command by stringstream
#include <string>							//to use string
using namespace std;

class Manager
{
private:

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
