#include "Manager.h"
using namespace std;

Manager::Manager()
{
    SQptr = new SubtitleQueue;
    SBSTptr = new SubtitleBST;
    SLptr = new SectionList;
}
Manager::~Manager()     //EXIT
{
    delete SQptr;
    delete SBSTptr;
    delete SLptr;
    PrintSuccess("EXIT");
}

void Manager::Run(const char* command)
{
    // Open command & log file
    fcmd.open(command);                                     // file open in read state
    flog.open("log.txt");                                   // file open in write state. print all log here
    if (!fcmd)                                              // if faild to open
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Read and Run command
    string line;                                         // saves a line of operation
    string command_name;                                 // saves the command name
    string delete_mode;                                 // saves the DELETE mode argument (UNDER, EQUAL)
    int section_num = -1;                                    // saves the section number of PRINT, SECTION
    Time start_time;                                    // saves the start time of SECTION
    Time end_time;                                      // saves the end time of SECTION
    Time key_time;                                      // saves the key time of DELETE UNDER, DELETE EQUAL

    while (getline(fcmd, line))                              // read line from filestream
    {
        istringstream iss(line);                             // saves line to stringstream.
        string extra;                                        // checks extra arguments left on stringstream. in PRINT, it is converted to section_number
        // Read command name / check if its valid
        if (!(iss >> command_name)) {               
            PrintErrorCode(1000);                   //Error 1000; cannot read command name
            iss.clear();                            //clear stream failbit
        }
        // compare command name 
        else {
            //LOAD
            if (command_name == "LOAD")
            {
                //check if there's no extra arguments
                if (!(iss>>extra))
                    Load();                                  //run LOAD
                else
                    PrintErrorCode(100);                    //Error 100; extra arguments left in line
            }
            //QPOP
            else if (command_name == "QPOP")
            {
                //check if there's no extra argumets
                if (!(iss>>extra))
                    Qpop();                        //run QPOP
                else
                    PrintErrorCode(200);          //Error 200; extra argumets left in line
            }
            //PRINT
            else if (command_name == "PRINT")
            {
                //check if PRINT has arguments
                if (!(iss >> extra))
                    Print();                        //run PRINT
                //convert extra argument to section number
                else
                {
                    try {
                        section_num = -1;
                        section_num = stoi(extra);           //exception std::invalid_argument, std::out of range
                        //check if section number is invalid
                        if (section_num < 0)
                            PrintErrorCode(300);            //Error 300; invalid section number
                        //check if there's no extra arguments
                        else if (!(iss >> extra))
                            Print(section_num);            //run PRINT section_num
                        else
                            PrintErrorCode(300);           //Error 300; extra arguments left in line
                    }
                    catch (const invalid_argument& e) {
                        PrintErrorCode(300);               //Error 300; argument not a number
                    }
                    catch (const out_of_range& e) {
                        PrintErrorCode(300);               //Error 300; argument not a number
                    }
                }
            }
            //SECTION
            else if (command_name == "SECTION")
            {
                //get the arguments / check if its valid
                if (!(iss >> section_num >> start_time >> end_time)) {
                    PrintErrorCode(400);                   //Error 400; invalid or insufficient argument
                    iss.clear();                        //clear stream failbit
                }
                //check if there's no extra arguments
                else if (!(iss>>extra))
                    Section(section_num, start_time, end_time);
                else
                    PrintErrorCode(400);                   //Error 400; extra arguments left in line
            }
            //DELETE
            else if (command_name == "DELETE")
            {
                //get the argumets / check if its valid
                if (!(iss >> delete_mode >> key_time)) {
                    PrintErrorCode(500);                   //Error 500; invalid or insufficient argument
                    iss.clear();
                }
                //check if there's no extra arguments
                else if (!(iss>>extra)) {
                    if (delete_mode == "EQUAL")
                    {
                        DeleteEqual(key_time);
                    }
                    else if (delete_mode == "UNDER")
                    {
                        DeleteUnder(key_time);
                    }
                    else
                        PrintErrorCode(500); //Error 500; extra arguments left in line
                }
                else
                    PrintErrorCode(500); //Error 500; extra arguments left in line
            }
            //EXIT
            else if (command_name == "EXIT")
            {
                //check if there's no extra arguments
                if (!(iss>>extra))
                {
                    break;
                }
                else
                    PrintErrorCode(600);           //Error 600; extra arguments left in line
            }
            //invalid command name
            else
                PrintErrorCode(1000);               //Error 1000; invalid command name;
        }
    } // end while
    
    fcmd.close();
    flog.close();
    return;
}

//print cmd name if successed
void Manager::PrintSuccess(const char* cmd)                 
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============\n" << endl;
}
// print error code if failed or invalid command
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============\n" << endl;
}

// Run LOAD
void Manager::Load(){
    if (!(SQptr->IsEmpty()) || SBSTptr->getRoot() || SLptr->getHead()) { //if data already exist in datastructures
        PrintErrorCode(100);
        return;
    }
    else {
        //open file stream
        ifstream fsub;  //subtitle filestream
        fsub.open("subtitle.txt");
        if (!fsub) {        //failed to open
            PrintErrorCode(100);
            fsub.close();
            return;
        }
        else
        {
            Time inputTime;
            string inputString;
            try 
            {
                //get data from subtitle.txt
                while (fsub >> inputTime)                              //get input subtitle time
                {
                    fsub.ignore(1);                                     //ignore whitespace between time and string
                    getline(fsub, inputString);                        //get input subtitle data
                    //try push to SubtitleQueue
                    SQptr->Push(inputTime, inputString);
                }
                //successfully Loadd, print result
                flog << "===== LOAD =====" << endl;
                SQptr->PrintAll(flog);
//                flog << SQptr->GetNodeCnt() << " subtitles loaded." << endl; //for debug
                flog << "===============\n" << endl;
            }
            catch (int nodecnt)             //catch; full queue push() fatal error
            {  
                //error log (no project specification, made option
                PrintErrorCode(100);
                flog << "full push fatal error: cannot push to subtitle queue. terminate program" << endl;
                exit(-1);
            }
        }
    }

}
// Run QPOP
void Manager::Qpop() {
    if (SQptr->IsEmpty()) {             //empty queue pop() fatal error
        PrintErrorCode(200);            //print error log
        exit(-1);                       //terminate program
    }
    else
    {
        try {
            //get SubtitleQueueNode count, only work if Subtitle queue is not empty 
            while (SQptr->GetNodeCnt() > 0)
            {
                //Pop() the Subtitle Queue,insert to subtitle BST
//                flog << "pop " << SQptr->GetNodeCnt() << "th element."<<endl;     //for debug
//                std::pair<Time, std::string> thePair = SQptr->Front();            //for debug
//                flog << thePair.first << " - " << thePair.second << endl;         //for debug
                SBSTptr->Insert(SQptr->Pop());
            }
            PrintSuccess("QPOP");
        }
        catch (int nodecnt)             //must not occur
        {
            flog << "Qpop malfunctioned" << endl;
            exit(-1);
        }
    }
}
// Run PRINT 
void Manager::Print() {
    PrintSuccess("PRINT");
}
// Run PRINT section_num
void Manager::Print(const int& section_num) {
    PrintSuccess("PRINT");
}
// Run SECTION
void Manager::Section(const int& section_num, const Time& start_time, const Time& end_time) {
    PrintSuccess("SECTION");
}
// Run DELETE equal
void Manager::DeleteEqual(const Time& key_time) {
    PrintSuccess("DELETE");
}
// Run DETETE under
void Manager::DeleteUnder(const Time& key_time) {
    PrintSuccess("DELETE");
}