/**~*~*~* 
 Binary tree abstract base class
===========================================
Name: Chu Jia Xian
*~*/ 
  
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
    virtual ~BinaryTree() { destroyTree(rootPtr); }
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int getCount() const {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(const ItemType &)) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(const ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(const ItemType &)) const{_postorder(visit, rootPtr);}
	void printLeafNodes(void visit(const ItemType &)) const{_printLeafNodes(visit, rootPtr);}
    void printTree(void visit(const ItemType &, int)) const{_printTree(visit, rootPtr, 1);}
	
	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType &newData) = 0;
	//virtual bool remove(const ItemType &data) = 0;
	virtual bool search(const ItemType &target, ItemType & returnedItem) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(const ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(const ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(const ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _printLeafNodes(void visit(const ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void visit(const ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const;
   
}; 

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if(nodePtr) // != nullptr
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        //cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
        delete nodePtr;
    }
}  



//Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(const ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    /* Write your code here */
	if (nodePtr)
    {
		ItemType temp = nodePtr->getItem();
        visit(temp);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}  

//Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(const ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}  

//Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(const ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    /* Write your code here */
	if (nodePtr)
    {
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
		ItemType temp = nodePtr->getItem();
        visit(temp);
    }
}  

//Prints tree as an indented list
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void visit(const ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const
{
     /* Write your code here */
	if (!nodePtr) 
        return;

    // copy into a local so we can bind to ItemType&
    ItemType temp = nodePtr->getItem();
    visit(temp, level);

    // first do the right subtree (indented one more level)
    _printTree(visit, nodePtr->getRightPtr(), level + 1);

    // then the left subtree
    _printTree(visit, nodePtr->getLeftPtr(),  level + 1);
}

//Print leaf nodes
template<class ItemType>
void BinaryTree<ItemType>::_printLeafNodes(void visit(const ItemType &), BinaryNode<ItemType>* nodePtr) const
{
     /* Write your code here */
	if (nodePtr) {
		// Leaf if no children
		if (!nodePtr->getLeftPtr() && !nodePtr->getRightPtr()) visit(nodePtr->getItem());
		_printLeafNodes(visit, nodePtr->getLeftPtr());
		_printLeafNodes(visit, nodePtr->getRightPtr());
	}
}

#endif


