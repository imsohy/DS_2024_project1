#include <iostream>
template <class T>											//클래스 Chain에 대한 자료형 일반화
class Chain;												//nonzero single LL을 관리하는 클래스

template <class T>											//클래스 ChainNode에 대한 자료형 일반화
class ChainNode {
	template <class T> friend class Chain;					//설명 1
public:
	ChainNode(const T data, ChainNode <T>* link = NULL);	//T형 데이터와, ChainNode 형 포인터 인데! ChainNode<T>  클래스 자료형 뒤에 꺾쇠 잊지말기
private:
	T data;
	ChainNode <T>* link;
};

template <class T>
ChainNode<T>::ChainNode(const T data, ChainNode <T>* link): data(data),link(link) {};

template <class T>
class Chain {												//Stack과 Queue로 모두 사용간으
public:
	//constructor
	Chain(void);
	virtual ~Chain();										//설명 ata, ChainNode<T>* link) : data(data3
	//Specification
	void Print(void);										//print whole Chain
	bool IsEmpty(void);										//Check whether Queue is empt
	void StackPush(T data);									//make
	void StackPop(void);									//make stack pop at the top
	void QueuePush(T data);									//make Q push at the rear
	void QueuePop(void);									//make Q push at the top 
private:
	ChainNode<T>* first;									//first를 stack의 top으로 쓴다. 또한 queue의 front로도 쓸 예정이란다.
	ChainNode<T>* last;										//last를 queue의 rear 로 쓸 예정이란다. 그러니까 NULL뒤에 계속 추가하는거다. 
};

template <class T>
Chain<T>::Chain() : first(NULL), last(NULL) {}	//체인 초기화. first, last 초기화
template <class T>
Chain<T>::~Chain() {							//일단 안에 있는거 싹다 삭제하고 자기 삭제해야겠지
	ChainNode<T>* deleteNode = NULL;			//포인터는 선언과 동시에 초기화를 해저야한다. 이런거부터 흔들린다

	while (first != NULL)
	{
		deleteNode = first;
		first = deleteNode->link;
		delete deleteNode;
	}											//딜리트노드를 처음으로 잡고, 처음을 다음 노드로 옮긴다음 첫노드 팝을 진행한다. 다음에도 계속 옮겨간다.
												//라스트 이터레이션: 딜리트노드가 한개가 있고 다음노드가 널이어서 널 노드로 퍼스트가 간경우.
}

template <class T>
inline bool Chain<T>::IsEmpty(void)
{
	return first == NULL;
}

template <class T>
void Chain<T>::Print(void)							//print whole Chain. implement; 포인터 하나만 지속적으로 갱신
{
	ChainNode<T>* printNode = first;				//출력 대상 노드. 포인터 선언 동시에 초기화.
	cout << "Print: ";
	while (printNode != NULL)
	{
		cout << printNode->data << ' ';
		printNode = printNode->link;
	}
	cout << "\n end of print." << endl;
}

//Stack spec implementation 
template <class T>
void Chain<T>::StackPush(T data) {					//first 원소에 push하도록 한다. one step push한다.
	first = new ChainNode<T>(data, first);
	cout << "StackPush : " << data << endl;
}

template <class T>
void Chain<T>::StackPop(void) {						//pop은 top을 하나 안쪽으로 옮기고 그냥 해버리면 되는거였다...
	ChainNode<T>* top = first;

	//방어적 프로그래밍 먼저
	if (IsEmpty()) {
		cout << "StackPop: empty!" << endl;
	}
	else
	{
		cout < "stackpop: " << top->data << endl;
		first = top->link;
		delete top;
	}
}
//Queue spec implementation. 큐를 어떻게 구현할까? last를 가장 처음에 삽입한 원소에 계속 붙여주고, first를 새로 생성해서 넣어주면 된다.
template <class T>
void Chain<T>::QueuePush(T data) {
	if (IsEmpty())
		first = last = new ChainNode<T>(data, NULL);
	else
		last = last->link = new ChainNode<T>(data, NULL);
	cout << "Queue Push : " << data << endl;
}
template <class T>
void Chain<T>::QueuePop() {
	ChainNode<T>* front = first;					//pop이 발생하는 위치
	if (IsEmpty())
		cout << "Queue is Empty" << endl;
	else {
		cout << "QueuePop:" << front->data << endl;
		first = front->link;
		delete front;
	}
}


/* 설명 1. 피friend Class B에서의 template <class T> friend class A
두 번째와 세 번째 template<class T>는 같은 자료형으로 취급됩니다. template<class T>는 템플릿 파라미터로, 
템플릿 클래스나 함수의 자료형을 일반화하여 다양한 자료형을 사용할 수 있도록 해주는 것입니다.
따라서 첫 번째 template<class T>는 Chain 클래스의 템플릿 파라미터를 정의하고, 
두 번째 template<class T>는 ChainNode 클래스의 템플릿 파라미터를 정의합니다.
여기서 세 번째 template<class T>는 ChainNode 안에서 Chain 클래스를 friend로 선언할 때 사용된 것으로,
동일한 자료형 T를 의미합니다.
즉, 모두 동일한 템플릿 파라미터 T로 처리된다고 보시면 됩니다.
*/

/* 설명 2. B에서 A를 친구로 선언할때
B class 안에서 A 클래스를 friend로 선언한다.
class A {...};
class B
{
friend class A;
};
이러면 B가 A에게 착취당하는 관계로 보면 된다.
*/

/* 설명 3. Virtual Destructor

*/