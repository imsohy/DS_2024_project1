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

//강의자료에서는 dictionary에서 버추얼 함수 쓰고 서브클래스로 상속받으라고 했지만 어쩌라고

template <class K, class E>
class BST {	
private:
	TreeNode<pair<K, E>>* root; //pair <K,E> 형의 자료를 공간을 가리키는 루트. 여기부터 시작한다.
public:
	//manager function
	BST() : root(NULL) {}; //아무리 할 게 없어도 root는 초기화해야지.
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
