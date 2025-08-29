#include "Manager.h"

Manager::Manager()
{   
    SQptr = nullptr;
    SBSTptr = nullptr;
    SLptr = nullptr;
}
Manager::~Manager() {}
void Manager::Run(const char* command)
{
    // Open command & log file
    fcmd.open(command);                                   
    flog.open("log.txt");                                
    if (!fcmd)                                              // if failed to open
    {
        flog << "Fail to open command file" << endl;
        exit(-1);                                           //fatal error
    }

    // Read and Run command
    string line;                                         // saves a line of operation
    string command_name;                                 // saves the command name
    string delete_mode;                                 // saves the DELETE mode argument (UNDER, EQUAL)
    int section_num = -1;                                    // saves the section number of PRINT, SECTION
    Time start_time;                                    // saves the start time of SECTION
    Time end_time;                                      // saves the end time of SECTION
    Time delete_time;                                      // saves the key time of DELETE UNDER, DELETE EQUAL

    // read line from filestream
    while (getline(fcmd, line))                              
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
                        section_num = stoi(extra);          //stoi can make exception std::invalid_argument, std::out of range
                        //check if section number is invalid
                        if (section_num < 0)                
                            PrintErrorCode(300);            //section number under zero
                        //check if there's no extra arguments
                        else if (!(iss >> extra))      
                            //execute PRINT section_num
                            Print(section_num);            
                        else                               
                            PrintErrorCode(300);           //extra arguments left in line
                    } 
                    catch (const invalid_argument& e) { 
                        PrintErrorCode(300);               //not an int
                    }
                    catch (const out_of_range& e) { 
                        PrintErrorCode(300);               //out of range of int
                    }
                }
            }
            //SECTION
            else if (command_name == "SECTION")
            {
                //get the arguments / check if its valid
                if (!(iss >> section_num >> start_time >> end_time)) 
                {
                    PrintErrorCode(400);                    //invalid or insufficient argument
                    //clear stream failbit
                    iss.clear();                            
                }
                //check if there's no extra arguments
                else if (!(iss>>extra))
		{
		    if(section_num < 0)
		    {
			PrintErrorCode(400);	//invalid section number
			return;
		    }
		    else
			//execute SECTION (...)
                    Section(section_num, start_time, end_time);
		}
		else
                    PrintErrorCode(400);                   //extra arguments left
            }
            //DELETE
            else if (command_name == "DELETE")
            {
                //get the argumets / check if its valid
                if (!(iss >> delete_mode >> delete_time)) 
                {
                    PrintErrorCode(500);                   //invalid or insufficient argument
                    //clear stream failbit
                    iss.clear();
                }
                //check if there's no extra arguments
                else if (!(iss>>extra)) {
                    //check delete mode
                    if (delete_mode == "EQUAL")
                    {
                        //execute DELETE EQUAL delete_time
                        DeleteEqual(delete_time);
                    }
                    else if (delete_mode == "UNDER")
                    {
                        //execute DELETE UNDER delete_time
                        DeleteUnder(delete_time);
                    }
                    else
                        PrintErrorCode(500); //invalid deletemode
                }
                else
                    PrintErrorCode(500); //extra argument 
            }
            //EXIT
            else if (command_name == "EXIT")
            {
                //check if there's no extra arguments
                if (!(iss>>extra))
                {
                    //deallocate memory
                    delete SQptr;
                    delete SBSTptr;
                    delete SLptr;
                    fcmd.close();
                    PrintSuccess("EXIT");
		    flog.close();
                    //return to main()
                    return;
                }
                else
                    PrintErrorCode(1000);           //Error 1000; extra arguments left in line
            }
            //invalid command name
            else
                PrintErrorCode(1000);               //Error 1000; invalid command name;
        }
    } // end while
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

// LOAD
void Manager::Load(){
    //allocate new Subtitle Queue if SQptr isn't allocated
    if(!SQptr) SQptr = new SubtitleQueue();
    //if data already exist in datastructures print errorcode 100
    else if ( !(SQptr->IsEmpty()) ||            //if Subtitle Queue has data
        (SBSTptr && SBSTptr->getRoot()) ||      //if Subtitle BST exist and it has data
        (SLptr && SLptr->getHead()) )          //if Section List exist and it has data
    {
        PrintErrorCode(100);
        return;
    }
    
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
        //get data from subtitle.txt
        Time subtitleTime;
        string subtitleString;
        try 
        {
            while (fsub >> subtitleTime)                              // read time  
            {
                fsub.ignore(1);                                       //ignore " "
                getline(fsub, subtitleString);                        //read string
                //try push to SubtitleQueue
                SQptr->Push(subtitleTime, subtitleString);            // this can have valid error
            }
            //successfully Loadd, print result
            flog << "===== LOAD =====" << endl;
            SQptr->PrintQueue(flog);
//                flog << SQptr->GetNodeCnt() << " subtitles loaded." << endl; //for debug
            flog << "===============\n" << endl;
        }
        //if data is more than 100 and push() from data 
        catch (const char* pusherror)             
        {  
            PrintErrorCode(100);
            exit(-1);               //fatal error
        }
    }
}
// QPOP
void Manager::Qpop() {
    //allocate new SubtitleBST if SubtitleBST ptr is null
    if (!SBSTptr) SBSTptr = new SubtitleBST();
    if (!SQptr || SQptr->IsEmpty()) {   //if SubtitleQueue not allocated || if its empty
        PrintErrorCode(200);            
        exit(-1);                       //fatal error
    }
    //build BST with Popped data in Subtitle Queue
    while (!(SQptr->IsEmpty()))         //only work if Subtitle queue is not empty(nodecnt > 0)
    {        
// for debug (prints Datapair to be inserted)
//      flog << "pop " << SQptr->GetNodeCnt() << "th element."<<endl;    
//      std::pair<Time, std::string> thePair = SQptr->Front();            
//      flog << thePair.first << " - " << thePair.second << endl;   
        
        //Pop() the Subtitle Queue,insert to subtitle BST
        SBSTptr->Insert(SQptr->Pop());
        //***Pop() actually never be executed in empty SubtitleQueue, so exit() doesn't happen that case
        //however, we can think QPOP in empty SubtitleQueue as same case
    }
    PrintSuccess("QPOP");
}
// PRINT 
void Manager::Print() {
    if (!SBSTptr || SBSTptr->getRoot() == nullptr) { PrintErrorCode(300); return; }
    flog << "===== PRINT =====" << endl;
    flog << "Subtitle_BST" << endl;
    SBSTptr->PrintBST(flog);
    flog << "===============\n" << endl;
}
// PRINT section_num
void Manager::Print(const int& key_section_num) {
    if (!SLptr) { PrintErrorCode(300); return;} //return if Section List not created
    try
    {   
        //search SectionListNode that matches the key
        SectionListNode* section_header = SLptr->Search(flog, key_section_num);
        
        //print section
        flog << "===== PRINT =====" << endl;
        SLptr->PrintSection(flog, section_header);
        flog << "===============\n" << endl;
    }
    catch (const char* notfound)
    {
        PrintErrorCode(300); return;    //if section number doesn't exist, print error code
    }
}
// SECTION (...)
void Manager::Section(const int& section_num, const Time& start_time, const Time& end_time) {
    //allocate new SectionList if it doesn't exist 
    if (!SLptr) SLptr = new SectionList();
    //create new SectionListNode to tail (even though SubtitleQueue doesn't exist or no node will be found in SearchRange())
    SLptr->GenerateNewSection(section_num);
    //PrintErrorCode() if SubtitleBST pointer is null
    if (!SBSTptr) { PrintErrorCode(400); return; }
    //allocate buffer SubtitleQueue. this saves SearchRange() result from SubtitleBST.
    SubtitleQueue* bufferSQ = new SubtitleQueue(CAP);
    //Search every SubtiteBSTNode in the range of start_time ~ end_time. save it to bufferSQ.
    SBSTptr->SearchRange(start_time, end_time, bufferSQ);  
    //print error message if no node found in SearchRange()
    if (bufferSQ->IsEmpty()) { 
        PrintErrorCode(400); 
        delete bufferSQ;            //deallocate bufferSQ
        return; 
    }
    //Pop buffer, insert to generated section head.
    while (!(bufferSQ->IsEmpty())) {
        SLptr->InsertSubtitle(bufferSQ->Pop());
    }
    delete bufferSQ;               //deallocate bufferSQ
    PrintSuccess("SECTION");
    return;
}
// DELETE EQUAL (...)
void Manager::DeleteEqual(const Time& delete_time) {
    if (!SBSTptr) { PrintErrorCode(500); return; }      //if SubtitleBST pointer is not allocated, return
    try 
    {
        SBSTptr->DeleteEveryEqual(delete_time);
        PrintSuccess("DELETE");
    }
    //catch error if SubtitleBST doesn't have any nodes that,
    //subtitle Time = delete_time (or, if it was empty tree)
    catch (const char* notfound)
    {
        PrintErrorCode(500);
    }
}
// DETETE UNDER (...)
void Manager::DeleteUnder(const Time& delete_time) {
    if (!SBSTptr) { PrintErrorCode(500); return; } //if SubtitleBST pointer is not allocated, return.
    try 
    {
        SBSTptr->DeleteUnder(delete_time);
        PrintSuccess("DELETE");
    }
    //catch error if SubtitleBST doesn't have any nodes that
    //subtitle Time < delete_time (or, if it was empty tree)
    catch (const char* notfound)
    {
        PrintErrorCode(500);
    }
}
