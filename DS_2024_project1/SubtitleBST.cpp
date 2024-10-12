#include "SubtitleBST.h"
#include <iostream> //for debug
#include <iomanip> //for debug

SubtitleBST::SubtitleBST() : root(nullptr) {}
SubtitleBST::~SubtitleBST()
{
	//delete entire BSTnodes with post-traversal
	DeleteBST(root);
}
SubtitleBSTNode* SubtitleBST::getRoot()
{
	return root;
}

/*Insert*/
void SubtitleBST::Insert(const Datapair& thePair) 					
{
	SubtitleBSTNode* pCur = root, * pPre = nullptr; //pCur is currently searching node, pPre is its parent
	//binary search the right place of thePair.
	//searchkey : time of inserting datapair
	while (pCur) {
		pPre = pCur;													
		// Search recursively. go to subtree that searchkey is possessed in.
		
		// if searchkey < current node key, go to left subtree
		if (thePair.first < pCur->getSubTime()) pCur = pCur->getLeft();
		// if searchkey >= current node key, go to right subtree
		else if (thePair.first >= pCur->getSubTime()) pCur = pCur->getRight(); 
		//***this includes duplicated key. if disable duplicated key, we use > instead
		//and manage duplicated case.
	}

	//perform insertion (pPre is the last searched node)
	pCur = new SubtitleBSTNode(thePair);
	if (root != nullptr)												//if tree not empty
		if (thePair.first < pPre ->getSubTime()) pPre->setLeft(pCur);	//if searchkey(inset data key) < last searched nodekey 
		else pPre->setRight(pCur);										
	else root = pCur;													 //if tree is empty

	return;
}
void SubtitleBST::SearchRange(const Time& start_time, const Time& end_time, SubtitleQueue* const& bufferSQ) const
{
	SearchRange(root, start_time, end_time, bufferSQ);
}
void SubtitleBST::SearchRange(SubtitleBSTNode* const& pCur, const Time& start_time,
	const Time& end_time, SubtitleQueue* const& bufferSQ) const
{   //pCur is currently searching node. bufferSQ is a buffer to save nodes
	if (pCur == nullptr) return;				//if current node is null child, return.
	//searchkey : start_time, end_time
	
	// if start time < current node key, search left subtree also.
	if (start_time < pCur->getSubTime()) 
		SearchRange(pCur->getLeft(), start_time, end_time, bufferSQ); 
	//if start_time <= current node key <= end_time, buffer the current node Datapair. (visit)
	if (start_time <= pCur->getSubTime() && end_time >= pCur->getSubTime())
		bufferSQ->Push(pCur->getData());
	// if end time >= current node key, search rigt subtree also
	if (end_time >= pCur->getSubTime())
		SearchRange(pCur->getRight(), start_time, end_time, bufferSQ);
	//***if there is no duplicated node, we use > instead 
	// the result would be same, but total iteration decreases.
}

/*Print*/
void SubtitleBST::PrintBST(ostream& os) const {
	PrintBST(os, root);
}
void SubtitleBST::PrintBST(ostream& os, SubtitleBSTNode* const & node) const{
	// inorder print 
	if (node)
	{
		//go to left subtree Recursive
		PrintBST(os, node->getLeft());							
		//visit (print datapair)
		os << node->getSubTime() << " - " << node->getSubString() << endl; 
		//go to right subtree Recursive
		PrintBST(os, node->getRight());						
	}
}

/*Delete*/
void SubtitleBST::DeleteBST(SubtitleBSTNode* const& node)
{
    //Post-Order delete every node
    if (node == nullptr) return;
	DeleteBST(node->getLeft());			//go to left subtree
	DeleteBST(node->getRight());		//go to right subtree
	delete node;                        //visit(delete)
}
void SubtitleBST::DeleteEveryEqual(const Time& delete_time)
{
    bool deleted = false;                                     //true if any node have been deleted.
    while (true) {
        SubtitleBSTNode* parent = nullptr;                  //SearchEqual() will save parent node here.
        // Find the node along with its parent
        SubtitleBSTNode* nodeToDelete = SearchEqual(delete_time, parent);
        if (!nodeToDelete) break; // If no matching node, exit loop

        // Delete the found node
        DeleteNode(nodeToDelete, parent);
        deleted = true;
    }
    //if not found even once (inclue empty root case)
    if (!deleted)
        throw "not found";
}
void SubtitleBST::DeleteUnder(const Time& delete_time)
{
    bool deleted = false;                           // track if any node has been deleted
    root = DeleteUnder(root, delete_time, deleted); //return root the result of Post-Order delete
    // If no node was deleted, throw an exception
    if (!deleted) 
        throw "not found";
}
SubtitleBSTNode* SubtitleBST::DeleteUnder(SubtitleBSTNode* node, const Time& delete_time, bool& deleted)
{
    // base case: if the current node is null, return null
    if (node == nullptr) return nullptr;

    // Post-Order traverse the tree.
    
    //postorder recurrence
    node->setLeft(DeleteUnder(node->getLeft(), delete_time, deleted)); //Recurse Left subtree 
    node->setRight(DeleteUnder(node->getRight(), delete_time, deleted)); //Recurse Right subtree
    // now check the current node. if its time is less than delete_time, delete it
    if (node->getSubTime() < delete_time)
    {
        SubtitleBSTNode* parent = nullptr;                                  // parent of this node
        DeleteNode(node, parent);                                           // call DeleteNode(), delete node.

        deleted = true; 

        PrintStructure(cout, root, 2); //for debug
        // return null after deletion, as the node is no longer valid
        return nullptr;
    }
    PrintStructure(cout, root, 2); //for debug
    // if the node's time is not less than delete_time, return the node itself (not modified)
    return node;
}
SubtitleBSTNode* SubtitleBST::SearchEqual(const Time& delete_time, SubtitleBSTNode* parent) const
{
    SubtitleBSTNode* pCur = root;       //start searching from root
    parent = nullptr;                  // Initialize parent to nullptr
    
    //binary search the tree.
    //search key: delete_time. 
    while (pCur) {
        if (delete_time < pCur->getSubTime()) {
            parent = pCur;  // Save the current node as parent
            pCur = pCur->getLeft(); // move to left subtree
        }
        else if (delete_time > pCur->getSubTime()) {
            parent = pCur;  // Save the current node as parent
            pCur = pCur->getRight(); // Move to right subtree
        }
        else {
            return pCur;  // match successed
        }
    }
    return nullptr;  // Not found, or if root was nullptr(empty tree)
}
void SubtitleBST::DeleteNode(SubtitleBSTNode* nodeToDelete, SubtitleBSTNode* parent)
{
    if (!nodeToDelete) throw "search malfunctioned"; // if search malfunctioned, given nullptr. (not going to happen)

    // if the node is a leaf node (degree 0)
    if (!nodeToDelete->getLeft() && !nodeToDelete->getRight()) 
    {
        if (nodeToDelete == root) {
            root = nullptr; //root was a leaf to delete
        }
        else {
            if (parent->getLeft() == nodeToDelete) {
                parent->setLeft(nullptr); // Disconnect the left child
            }
            else {
                parent->setRight(nullptr); // Disconnect the right child
            }
        }
        delete nodeToDelete;
    }
    // if the node has one child (degree 1), connect child to grandparent and delete
    else if (!nodeToDelete->getLeft() || !nodeToDelete->getRight()) 
    {
        //save nodeToDelete's child
        SubtitleBSTNode* child = nodeToDelete->getLeft() ? nodeToDelete->getLeft() : nodeToDelete->getRight();

        if (nodeToDelete == root) {
            root = child; // If deleting the root nodeToDelete
        }
        else {
            if (parent->getLeft() == nodeToDelete) {
                parent->setLeft(child); // link the parent's left child
            }
            else {
                parent->setRight(child); // link the parent's right child
            }
        }
        delete nodeToDelete;
    }
    // if the node has two child (degree 2), find successor, replace with it.
    else
    {
        // find the successor (= minimum node in the right subtree)
        SubtitleBSTNode* successorParent;                                                   // saves successor's parent while FindMin().
        SubtitleBSTNode* successor = FindMin(nodeToDelete->getRight(), successorParent);    // start from nodeToDelete's rightChild as a root, return smallest node to successor, saves its parent to successorparent
        // replace the data of nodeToDelete with the successor's data
        nodeToDelete->setData(successor->getData());

        //***successor cannot have left child (because it is leftmost node of nodeToDelete's right subtree.)
        //it can have no child or only right child, so just connecting successorParent wih successor's rightchild will work.

        // Delete the successor node.
        // successor is a left child (nodeToDelete right-> successorParent left -> node left-> ... -> successor)
        if (successorParent->getLeft() == successor) {
            successorParent->setLeft(successor->getRight());
        }
        // Successor is a right child (in this case it is nodeToDelete's right child directly; nodetodelete = successorParent right-> successor)
        else {
            successorParent->setRight(successor->getRight());
        }
        //deallocate node
        delete successor;
    }
}
SubtitleBSTNode* SubtitleBST::FindMin(SubtitleBSTNode* node, SubtitleBSTNode*& parent) const
{
    parent = nullptr; // Initialize parent to nullptr
    while (node->getLeft()) {
        parent = node;  // save the current node as parent
        node = node->getLeft(); // move to the leftmost node.
    }
    return node;  // return the minimum node
}

//for debug
void SubtitleBST::PrintStructure(ostream& os, SubtitleBSTNode* node, int space) const
{
    int COUNT = 10;

    // return if node is null
    if (node == nullptr)
        return;

    // print right node recursively
    space += COUNT;

    PrintStructure(os, node->getRight(), space);

    // print current node
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << node->getSubTime() << "\n";

    // print left node recursive
    PrintStructure(os, node->getLeft(), space);
}