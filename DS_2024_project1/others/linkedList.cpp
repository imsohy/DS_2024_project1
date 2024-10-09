#include <iostream>
template <class T>											//Ŭ���� Chain�� ���� �ڷ��� �Ϲ�ȭ
class Chain;												//nonzero single LL�� �����ϴ� Ŭ����

template <class T>											//Ŭ���� ChainNode�� ���� �ڷ��� �Ϲ�ȭ
class ChainNode {
	template <class T> friend class Chain;					//���� 1
public:
	ChainNode(const T data, ChainNode <T>* link = NULL);	//T�� �����Ϳ�, ChainNode �� ������ �ε�! ChainNode<T>  Ŭ���� �ڷ��� �ڿ� ���� ��������
private:
	T data;
	ChainNode <T>* link;
};

template <class T>
ChainNode<T>::ChainNode(const T data, ChainNode <T>* link): data(data),link(link) {};

template <class T>
class Chain {												//Stack�� Queue�� ��� ��밣��
public:
	//constructor
	Chain(void);
	virtual ~Chain();										//���� ata, ChainNode<T>* link) : data(data3
	//Specification
	void Print(void);										//print whole Chain
	bool IsEmpty(void);										//Check whether Queue is empt
	void StackPush(T data);									//make
	void StackPop(void);									//make stack pop at the top
	void QueuePush(T data);									//make Q push at the rear
	void QueuePop(void);									//make Q push at the top 
private:
	ChainNode<T>* first;									//first�� stack�� top���� ����. ���� queue�� front�ε� �� �����̶���.
	ChainNode<T>* last;										//last�� queue�� rear �� �� �����̶���. �׷��ϱ� NULL�ڿ� ��� �߰��ϴ°Ŵ�. 
};

template <class T>
Chain<T>::Chain() : first(NULL), last(NULL) {}	//ü�� �ʱ�ȭ. first, last �ʱ�ȭ
template <class T>
Chain<T>::~Chain() {							//�ϴ� �ȿ� �ִ°� �ϴ� �����ϰ� �ڱ� �����ؾ߰���
	ChainNode<T>* deleteNode = NULL;			//�����ʹ� ����� ���ÿ� �ʱ�ȭ�� �������Ѵ�. �̷��ź��� ��鸰��

	while (first != NULL)
	{
		deleteNode = first;
		first = deleteNode->link;
		delete deleteNode;
	}											//����Ʈ��带 ó������ ���, ó���� ���� ���� �ű���� ù��� ���� �����Ѵ�. �������� ��� �Űܰ���.
												//��Ʈ ���ͷ��̼�: ����Ʈ��尡 �Ѱ��� �ְ� ������尡 ���̾ �� ���� �۽�Ʈ�� �����.
}

template <class T>
inline bool Chain<T>::IsEmpty(void)
{
	return first == NULL;
}

template <class T>
void Chain<T>::Print(void)							//print whole Chain. implement; ������ �ϳ��� ���������� ����
{
	ChainNode<T>* printNode = first;				//��� ��� ���. ������ ���� ���ÿ� �ʱ�ȭ.
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
void Chain<T>::StackPush(T data) {					//first ���ҿ� push�ϵ��� �Ѵ�. one step push�Ѵ�.
	first = new ChainNode<T>(data, first);
	cout << "StackPush : " << data << endl;
}

template <class T>
void Chain<T>::StackPop(void) {						//pop�� top�� �ϳ� �������� �ű�� �׳� �ع����� �Ǵ°ſ���...
	ChainNode<T>* top = first;

	//����� ���α׷��� ����
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
//Queue spec implementation. ť�� ��� �����ұ�? last�� ���� ó���� ������ ���ҿ� ��� �ٿ��ְ�, first�� ���� �����ؼ� �־��ָ� �ȴ�.
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
	ChainNode<T>* front = first;					//pop�� �߻��ϴ� ��ġ
	if (IsEmpty())
		cout << "Queue is Empty" << endl;
	else {
		cout << "QueuePop:" << front->data << endl;
		first = front->link;
		delete front;
	}
}


/* ���� 1. ��friend Class B������ template <class T> friend class A
�� ��°�� �� ��° template<class T>�� ���� �ڷ������� ��޵˴ϴ�. template<class T>�� ���ø� �Ķ���ͷ�, 
���ø� Ŭ������ �Լ��� �ڷ����� �Ϲ�ȭ�Ͽ� �پ��� �ڷ����� ����� �� �ֵ��� ���ִ� ���Դϴ�.
���� ù ��° template<class T>�� Chain Ŭ������ ���ø� �Ķ���͸� �����ϰ�, 
�� ��° template<class T>�� ChainNode Ŭ������ ���ø� �Ķ���͸� �����մϴ�.
���⼭ �� ��° template<class T>�� ChainNode �ȿ��� Chain Ŭ������ friend�� ������ �� ���� ������,
������ �ڷ��� T�� �ǹ��մϴ�.
��, ��� ������ ���ø� �Ķ���� T�� ó���ȴٰ� ���ø� �˴ϴ�.
*/

/* ���� 2. B���� A�� ģ���� �����Ҷ�
B class �ȿ��� A Ŭ������ friend�� �����Ѵ�.
class A {...};
class B
{
friend class A;
};
�̷��� B�� A���� ������ϴ� ����� ���� �ȴ�.
*/

/* ���� 3. Virtual Destructor

*/