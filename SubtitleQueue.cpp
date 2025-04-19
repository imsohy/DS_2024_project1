#include "SubtitleQueue.h"

SubtitleQueue::SubtitleQueue(int queueCapacity)
{
	capacity = queueCapacity;
	front = rear = nullptr;
	nodecnt = 0;
}
SubtitleQueue::~SubtitleQueue()
{
	SubtitleQueueNode* deleteNode = nullptr;
	while (front != nullptr)			//delete every subtitle queue node
	{
		deleteNode = front;				//save front node
		front = front->GetNext();		//move front to nextnode
		delete deleteNode;				//delete before frontnode
		nodecnt--;						//manage nodecnt change
	}
}
bool SubtitleQueue::IsEmpty () const
{
	return nodecnt == 0;
}
bool SubtitleQueue::IsFull() const
{
	return nodecnt == capacity;
}
void SubtitleQueue::Push(const Time& inputTime, const std::string& inputSub)
{
	if (!IsFull())
	{
		SubtitleQueueNode* newnode = new SubtitleQueueNode(inputTime, inputSub);
		if (IsEmpty()) 
			front = rear = newnode;			//push on empty queue
		else
		{				
			rear->SetNext(newnode);			//set newnode to rear's next
			rear = rear->GetNext();			//move rear to it
		}
		nodecnt++;							//manage nodecnt change
	}
	else throw "fatal error: full queue push()";		//full queue push() fatal error; expected error
}
void SubtitleQueue::Push(const Datapair& inputPair)
{
	if (!IsFull())
	{
		SubtitleQueueNode* newnode = new SubtitleQueueNode(inputPair);
		if (IsEmpty())	
			front = rear = newnode;
		else {
			rear->SetNext(newnode);
			rear= rear->GetNext();
		}
		nodecnt++;
	}
	else throw "fatal error: full queue push()";		//full queue push() fatal error (will not happen)
}
Datapair SubtitleQueue::Pop()
{
	if (!IsEmpty())		//only work if queue is empty
	{
		SubtitleQueueNode* deleteNode = front;			//save current front node 
		front = front->GetNext();						//move front to nextnode
		Datapair deleteNodeData = deleteNode->GetData(); //save current front node data
		delete deleteNode;								//delete before front node
		nodecnt--;										//manage nodecnt change
		return deleteNodeData;							//return popped data
	}
	else throw "fatal error: empty queue pop()";		//empty queue pop() malfunction (do not happen)
}
Datapair SubtitleQueue::Front() const
{
	if (!IsEmpty())
		return front->GetData();
	else throw "empty queue front() error";		//empty queue front() malfunction (do not happen)
}
void SubtitleQueue::PrintQueue(ostream& os) const
{
	SubtitleQueueNode* walker = front;			//start from front, walks
	while (walker != nullptr)
	{
		os << walker->GetSubTime() << " - " << walker->GetSubString() << std::endl;
		walker = walker->GetNext();
	}
}