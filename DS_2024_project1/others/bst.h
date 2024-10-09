#pragma once
#include <utility> //to use key

using namespace std; 
template <class T>
class TreeNode
{
private:
	//data field
	T data;	//have data
	TreeNode<T>* leftChild, * rightChild; //to point left right child.
public:
	//manager function
	TreeNode(T data) : data(data), leftChild(NULL), rightChild(NULL) {};
};

//�����ڷῡ���� dictionary���� ���߾� �Լ� ���� ����Ŭ������ ��ӹ������ ������ ��¼���

template <class K, class E>
class BST {	
private:
	TreeNode<pair<K, E>>* root; //pair <K,E> ���� �ڷḦ ������ ����Ű�� ��Ʈ. ������� �����Ѵ�.
public:
	//manager function
	BST() : root(NULL) {}; //�ƹ��� �� �� ��� root�� �ʱ�ȭ�ؾ���.
	//specification
	//print node inorder (driver,workhorse)
	~BST();
	void Ascend(void) const;
	void Ascend(TreeNode<pair<K, E>>* p);
	//search the node matching to the given key (driver,workhorse) function overloading
	pair<K, E>* Get(const K&) const;
	pair<K, E>* Get(TreeNode<pair<K, E>>* p, const K& k) const;
	//search given key, insert(or update) node to bst
	void Insert(const pair<K, E>&);
	//search given key, delete node from bst
	void Delete(const K&);
};
