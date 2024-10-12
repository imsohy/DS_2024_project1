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
	while (front != nullptr)
	{
		deleteNode = front;
		front = front->GetNext();
		delete deleteNode;
		nodecnt--;
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
			front = rear = newnode;
		else
		{
			rear->SetNext(newnode);
			rear = rear->GetNext();
		}
		nodecnt++;
	}
	else throw "fatal error: full queue push()";		//full queue push() fatal error; 
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
	if (!IsEmpty())
	{
		SubtitleQueueNode* deleteNode = front;
		front = front->GetNext();
		Datapair deleteNodeData = deleteNode->GetData();
		delete deleteNode;
		nodecnt--;
		return deleteNodeData;
	}
	else throw "fatal error: empty queue pop()";		//empty queue pop() fatal error (do not happen)
}
Datapair SubtitleQueue::Front() const
{
	if (!IsEmpty())
		return front->GetData();
	else throw "empty queue front() error";		//empty queue front() error (do not happen)
}
void SubtitleQueue::PrintQueue(ostream& os) const
{
	SubtitleQueueNode* walker = front;
	while (walker != nullptr)
	{
		os << walker->GetSubTime() << " - " << walker->GetSubString() << std::endl;
		walker = walker->GetNext();
	}
}