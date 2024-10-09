#include "bst.h"
#include <iostream> //for operation BST::Ascend

template <class K, class E>
BST<K, E>::~BST() {

}

template <class K, class E>
void BST<K, E>::Ascend(void) const //Driver
{
	//start from root
	//보통 이렇게 된 경우 워크호스랑 아래와 같이 또 분리해서 준다.
	Ascend(root);
	std::cout << "\n end printing BST ascending order\n";
	return;
}
template <class K, class E>
void BST<K, E>::Ascend(TreeNode<pair<K, E>>* p) //WorkHorse
{
	if (p != NULL)
	{
		Ascend(p->leftChild);
		std::cout << p->data.second << ' '; //버그: 마지막에 ' ' 한번 더 출력
		Ascend(p->rightChild);
	}
	return;
}

template<class K, class E> //Driver
pair<K, E>* BST<K, E>::Get(const K& k) const
{
	//Search the binary search tree (*this) for a pair with key k
	//if such a pair is found, return a pointer to this pair; otherwise, return NULL
	return Get(root, k);
}
template<class K, class E> //Workhorse, function overloading
pair<K, E>* BST<K, E>::Get(TreeNode<pair<K,E>> *p, const K&k) const
{
	//키값 확인하러들어온 노드가 null일경우
	if (p == NULL) return NULL; 

	//노드는 NULL이 아니고, key 값이 현재노드 key보다 크거나 작은 경우 서브트리 탐색
	if (k < p->data.first) return Get(p->leftChild,k);
	if (k > p->data.first) return Get(p->rightChild,k);
	
	//위의 조건에 하나도 부합하지 않은 경우 k = key이므로 현재 데이터 반환
	return &p->data; //&(p->data)로 읽음
}

template <class K, class E>
void BST<K, E>::Insert(const pair<K, E>& thePair) //Insert thePair into the binary search tree
{	
	//pp is the parent of p
	//Search for thepair first
	TreeNode<pair<K, E>>* p = root, * pp = NULL;
	//searching k values; go down untill find the place
	while (p) {
		pp = p; //save the current pointer because there's no pointer pointing upright
		if (thePair.first < p->data.first) p = p->leftChild;
		else if (thePair.first > p->data.first) p = p->rightChild;
		else // duplicated, update associated element
		{
			p->data.second = thePair.second; return;
		}
	} //pp가 가장 마지막으로 탐색한 노드가 되고 p가 저장할 위치가 됨
	
	//found the place, perform insertion
	p = new TreeNode<pair<K, E>>(thePair);
	if (root != NULL) //tree not empty
		if (thePair.first < pp->data.first) pp->leftchild = p;
		else pp->rightchild = p; // (현재 pp의 자리에 같은 경우는 이미 처리했거든.)
	else root = p; //루트에 채워주기
	
	return;
}

template<class K, class E>
void BST<K,E>::Delete(const K& k)
{
	TreeNode <pair<K, E>> *p = root, *q = 0; //q는 p의 부모노드
	
	//key에 해당하는 노드 찾기
	while (p && k != p->data.first) { //현재 탐색하는 노드가 NULL이거나 key값이같지 않은경우
		q = p; //현재노드를 부모노드에 저장
		if (k < p->data.first) p = p->leftChild;
		else p = p->rightChild;
	}//q는 마지막으로 탐색하고 나온 노드, p는 키값을 찾은 자식노드

	//case: unfound
	if (p == 0) return; //다 거치고 나서 데이터가 안찾아졌는지 p로 확인

	//case : degree 0
	if (p->leftChild == 0 && p->rightChild == 0) {
		//먼저 q노드의 포인터정보를 초기화
		if (q == 0) root = 0; //root 보자마자 바로 key찾았으면 q는 초기상태니까 루트임
		else if (q->leftChild == p) q->leftChild = 0;
		else q->rightChild = 0;
		//공간을 초기화
		delete p;
	}

	//case : degree 1 + p have only rightchild
	if (p->leftChild == 0) {//p가 오른쪽 자식이 있으면
		//먼저 q노드의 포인터정보를 초기화
		if (q == 0) root = p->rightChild; //root가 p였다면, 존재하는 p의 rightchild(손자)랑 연결
		else if (q->leftChild == p) q->leftChild = p->rightChild;
		else q->rightChild = p->rightChild;
		delete p;
	}
	//case : degree 1 + p have only leftchild
	if (p->rightChild == 0) {
		if (q == 0) root = p->leftChild; //root가 p였다면, 존재하는 p의 leftChild(손자)랑 연결
		else if (q->leftChild == p) q->leftChild = p->leftChild;
		else q->rightChild = p->rightChild;
		delete p;
	}
	
	//case : degree 2 
	else {
		//find the smallest node in the right subtree 
		//일단 p -> 우 -> 좌 3개의 포인터를 저장해둠. 왜? p의, right subtree로 들어간거잖아.
		TreeNode<pair<K, E>>* prevprev = p, //prevprev를 key찾은 노드인 p로 잡고
			* prev = p->rightChild, //prev를 p의 오른쪽 노드로 잡고
			* curr = p->rightChild->leftChild; //curr를 그것의 왼쪽으로 잡음. 어캐 들어가는지 알지?
		
		// rightsubtree -> 좌 -> 좌.....로 계에에에속해서 curr이 비었을때까지 내려감
		while(curr)
		{
			prevprev = prev;
			prev = curr;
			curr = curr->leftChild;
		}

		//curr is 0, prev is the node to be deleted, prevprev is prev's parent
		//prevprev에 prev의 정보를 이어줘야하는거임. 그런데, 이어줄 정보는 rightchild밖에없고.
		//두가지 케이스가 있음; p -> rightsubtree -> 좌가 바로 0인 경우랑 한번 이상 더 좌로 가는경우
		//그림 그려야돼 꼭 
		p->data = prev->data;
		if (prevprev == p) prevprev->rightChild = prev->rightChild;
		else prevprev->leftChild = prev->rightChild;
		delete prev;
	}
	return;
}

