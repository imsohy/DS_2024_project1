#ifndef BASICHEADER_H
#define BASICHEADER_H
#include "Time.h"		//include <sstream>, <string>, <exception>, using namespace std
#include <utility>		//include pair
#define CAP 100			//maximum node number of SubtitleQueue and each subtitle list in SectionLit

typedef std::pair<Time, std::string> Datapair; //pair of subtitle Time, subtitle String. every Node class data is made with this pair. thus, key is time.
#endif //BASICHEADER_H