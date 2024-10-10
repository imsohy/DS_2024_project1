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
		front = deleteNode->GetNext();
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
		SubtitleQueueNode* newnode = new SubtitleQueueNode(inputTime, inputSub, nullptr);
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
std::pair<Time,std::string> SubtitleQueue::Pop()
{
	if (!IsEmpty())
	{
		SubtitleQueueNode* deleteNode = front;
		front = front->GetNext();
		std::pair<Time, std::string> pairedData;
		pairedData = std::make_pair(deleteNode->GetSubTime(),deleteNode->GetSubString());
		delete deleteNode;
		nodecnt--;
		return pairedData;
	}
	else throw "fatal error: empty queue pop()";		//empty queue pop() fatal error (will not happen)
}
std::pair<Time, std::string> SubtitleQueue::Front() const
{
	if (!IsEmpty())
		return std::make_pair(front->GetSubTime(), front->GetSubString());
	else throw "empty queue front() error";		//empty queue front() error (will not happen)
}
void SubtitleQueue::PrintAll(std::ostream& os)
{
	SubtitleQueueNode* walker = front;
	while (walker != nullptr)
	{
		os << walker->GetSubTime() << " - " << walker->GetSubString() << std::endl;
		walker = walker->GetNext();
	}
}