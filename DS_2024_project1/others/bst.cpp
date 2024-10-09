#include "bst.h"
#include <iostream> //for operation BST::Ascend

template <class K, class E>
BST<K, E>::~BST() {

}

template <class K, class E>
void BST<K, E>::Ascend(void) const //Driver
{
	//start from root
	//���� �̷��� �� ��� ��ũȣ���� �Ʒ��� ���� �� �и��ؼ� �ش�.
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
		std::cout << p->data.second << ' '; //����: �������� ' ' �ѹ� �� ���
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
	//Ű�� Ȯ���Ϸ����� ��尡 null�ϰ��
	if (p == NULL) return NULL; 

	//���� NULL�� �ƴϰ�, key ���� ������ key���� ũ�ų� ���� ��� ����Ʈ�� Ž��
	if (k < p->data.first) return Get(p->leftChild,k);
	if (k > p->data.first) return Get(p->rightChild,k);
	
	//���� ���ǿ� �ϳ��� �������� ���� ��� k = key�̹Ƿ� ���� ������ ��ȯ
	return &p->data; //&(p->data)�� ����
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
	} //pp�� ���� ���������� Ž���� ��尡 �ǰ� p�� ������ ��ġ�� ��
	
	//found the place, perform insertion
	p = new TreeNode<pair<K, E>>(thePair);
	if (root != NULL) //tree not empty
		if (thePair.first < pp->data.first) pp->leftchild = p;
		else pp->rightchild = p; // (���� pp�� �ڸ��� ���� ���� �̹� ó���߰ŵ�.)
	else root = p; //��Ʈ�� ä���ֱ�
	
	return;
}

template<class K, class E>
void BST<K,E>::Delete(const K& k)
{
	TreeNode <pair<K, E>> *p = root, *q = 0; //q�� p�� �θ���
	
	//key�� �ش��ϴ� ��� ã��
	while (p && k != p->data.first) { //���� Ž���ϴ� ��尡 NULL�̰ų� key���̰��� �������
		q = p; //�����带 �θ��忡 ����
		if (k < p->data.first) p = p->leftChild;
		else p = p->rightChild;
	}//q�� ���������� Ž���ϰ� ���� ���, p�� Ű���� ã�� �ڽĳ��

	//case: unfound
	if (p == 0) return; //�� ��ġ�� ���� �����Ͱ� ��ã�������� p�� Ȯ��

	//case : degree 0
	if (p->leftChild == 0 && p->rightChild == 0) {
		//���� q����� ������������ �ʱ�ȭ
		if (q == 0) root = 0; //root ���ڸ��� �ٷ� keyã������ q�� �ʱ���´ϱ� ��Ʈ��
		else if (q->leftChild == p) q->leftChild = 0;
		else q->rightChild = 0;
		//������ �ʱ�ȭ
		delete p;
	}

	//case : degree 1 + p have only rightchild
	if (p->leftChild == 0) {//p�� ������ �ڽ��� ������
		//���� q����� ������������ �ʱ�ȭ
		if (q == 0) root = p->rightChild; //root�� p���ٸ�, �����ϴ� p�� rightchild(����)�� ����
		else if (q->leftChild == p) q->leftChild = p->rightChild;
		else q->rightChild = p->rightChild;
		delete p;
	}
	//case : degree 1 + p have only leftchild
	if (p->rightChild == 0) {
		if (q == 0) root = p->leftChild; //root�� p���ٸ�, �����ϴ� p�� leftChild(����)�� ����
		else if (q->leftChild == p) q->leftChild = p->leftChild;
		else q->rightChild = p->rightChild;
		delete p;
	}
	
	//case : degree 2 
	else {
		//find the smallest node in the right subtree 
		//�ϴ� p -> �� -> �� 3���� �����͸� �����ص�. ��? p��, right subtree�� �����ݾ�.
		TreeNode<pair<K, E>>* prevprev = p, //prevprev�� keyã�� ����� p�� ���
			* prev = p->rightChild, //prev�� p�� ������ ���� ���
			* curr = p->rightChild->leftChild; //curr�� �װ��� �������� ����. ��ĳ ������ ����?
		
		// rightsubtree -> �� -> ��.....�� �迡�������ؼ� curr�� ����������� ������
		while(curr)
		{
			prevprev = prev;
			prev = curr;
			curr = curr->leftChild;
		}

		//curr is 0, prev is the node to be deleted, prevprev is prev's parent
		//prevprev�� prev�� ������ �̾�����ϴ°���. �׷���, �̾��� ������ rightchild�ۿ�����.
		//�ΰ��� ���̽��� ����; p -> rightsubtree -> �°� �ٷ� 0�� ���� �ѹ� �̻� �� �·� ���°��
		//�׸� �׷��ߵ� �� 
		p->data = prev->data;
		if (prevprev == p) prevprev->rightChild = prev->rightChild;
		else prevprev->leftChild = prev->rightChild;
		delete prev;
	}
	return;
}

