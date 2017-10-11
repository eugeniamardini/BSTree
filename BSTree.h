//----------------------------------------------------------------------------
// BSTree.h
// Author: Yauheniya Zapryvaryna CSS 343 Winter 2015 UWB
//----------------------------------------------------------------------------
// DESCRIPTION: Class BSTree implements a binary search tree by using a struct 
//			   Node, which has a pointer to a TreeData object.
// FUNCTIONALITY: 
//	--compares 2 BSTrees among themselves
//	--outputs the contents of a BSTree to the console in the Frequency Table 
//	  format;
//	--creates a deep copy of a BSTree
//	--adds non-repeating TreeData objects;
//	--retrieves a pointer to a TreeData object;
//	--counts the depth and/ot # of descendants of a particular Treedata object;
//	--removes an occurrence of a TreeData object
//	--deallocates its memory upon a makeEmpty command from the driver.
// ASSUMPTIONS:
//	--text file to be read by the program contains only characters, w/o any 
//	  special cases (such as '\n', '\t' etc.)
//	--in overloaded operator<<, a TreeData object is displayed and  followed by
//	  a space and the number of its occurrences in the text file.
//-----------------------------------------------------------------------------

#pragma once
#include "TreeData.h"
#include <iostream>
using namespace std;

class BSTree
{
//-----------------------------  <<  ----------------------------------------
// Overloaded output operator for class BSTree
// Preconditions: root is not NULL and BSTree to be output is allocated
// in memory
// Postconditions: the displayHelper function is called upon this tree, 
// and the constents of the tree get output to to console in the inorder
// manner. 
friend ostream& operator<<(ostream & , const BSTree &);

public:
	//-------------------------------Default Constructor-----------------------
	// Creates a new BSTree object
	// Preconditions:none
	// Postconditions: a new BSTree object is created with root set to NULL
	BSTree();

	//-----------------------------Constructor---------------------------------
	// Creates a new BSTree object
	// Preconditions:TreeData pointer key points to a TreeData object, and this 
	// BSTree is empty
	// Postconditions: a new BSTree is created with the root equal to the value
	// of a TreeData object passes in; root's children get initialized to NULL.
	BSTree(TreeData * );

	//--------------------------------Copy Constructor-------------------------
	// Makes a deep copy of a BSTree
	// Preconditions: sourceTree must be allocated in memory
	// Postconditions: sourceTree is copied into this tree
	BSTree(const BSTree & );

	//-------------------------------- insert --------------------------------
	// Inserts a Node with a TreeData object's value into this BSTree
	// Preconditions: TreeData object key has been allocated in memory
	// Postconditions: insertHelper function is called and true is returned if
	// key is inserted, and false gets returned if key is found in this BSTree 
	// (thus, not inserted). if key is inserted for the first time, its count 
	// becomes 1, else its count gets incremented by 1.
	bool insert(TreeData *);

	//-------------------------------- retrieve ----------------------------
	// Finds a TreeData object in the BSTree
	// Preconditions: the object passed in is a valid TreeData object
	// Postconditions: retrieveHelper function is called and a pointer is
	// returned if key is found, else (if key is not found) NULL is returned.
	const TreeData * retrieve(const TreeData & ) const;

	//----------------------------------  =  ----------------------------------
	// Assignes one BSTree to another (making a deep copy)
	// Preconditions: the tree to be copied into *this has been allocated in 
	// memory
	// Postconditions:this BSTree gets emptied, and sourceTree gets copied into 
	// this BSTree with the help of copyTree function
	const BSTree& operator=(const BSTree &);

	//----------------------------------  depth  ------------------------------
	// Finds the depth of a TreeData object in the BSTree
	// Preconditions: the object passed in is a valid TreeData object and this 
	// tree may contain a node with the sought TreeData object
	// Postconditions: depthHelper is called and the integer that represents the 
	// depth of a TreeData object is returned if the object key is found in this 
	// BSTree; if not found -1 is returned.
	int depth(const TreeData &) const;

	//----------------------------------  descendants  ------------------------
	// Finds the number of descendants of a node with the given TreeData object
	// Preconditions: the TreeData object is valid and this tree may contain a 
	// node with the given TreeData object
	// Postconditions: findDescendants is called and the integer that 
	// represents the number of descendants of a TreeData object is returned if
	// the object key is found in this BSTree; if not found -1 is returned.
	int descendants(const TreeData & ) const;

	//------------------------------  ==  -------------------------------------
	// Determines if two BSTrees are equal.
	// Preconditions: both trees are allocated in memory
	// Postconditions: areEqual helper function is called, and true is returned
	// if the trees have the same data, the same structure, and the same number
	// of occurrences for each character, false otherwise.
	bool operator==(const BSTree &) const;

	//------------------------------  !=  -------------------------------------
	// Determines if two BSTrees are not equal.
	// Preconditions: both trees are allocated in memory
	// Postconditions: false is returned if the trees have the same data, the 
	// same structure, and the same number of occurrences for each character, 
	// true otherwise.
	bool operator!=(const BSTree &) const;

	//------------------------------  remove  ---------------------------------
	// Removes one occurrence of a character from the BST. 
	// Preconditions: the tree may have a character to remove
	// Postconditions: removeHelper is called; if count is greater than one,
	// count is decremented and true is returned. If count is 1, the item is 
	// removed from the tree and true is returned. Otherwise, false is returned
	bool remove(const TreeData &);

	//--------------------------------makeEmpty--------------------------------
	// Empties the BSTree
	// Preconditions: none
	// Postconditions: the helper function is called, and the tree's memory is 
	// deallocated
	void makeEmpty();

	//--------------------------------isEmpty----------------------------------
	// Checks whether the BSTree is empty
	// Preconditions: the BSTree has a root with allocated memory 
	// Postconditions: true is returned if BSTree is empty, false otherwise.
	bool isEmpty() const;

	//---------------------------- Destructor ---------------------------------
	// Destructor for class BSTree
	// Preconditions: none
	// Postconditions: BSTree is destructed, memory occupied previously by the 
	// tree is deallocated
	~BSTree();

private:
	struct Node {
		TreeData *item;
		Node *right;
		Node *left;
		int count;
	};
	Node *root;

	//----------------------------------  depthHelper  ------------------------
	// Finds the depth of a TreeData object in the BSTree
	// Preconditions: root has been allocated in memory
	// Postconditions: depthHelper is called and the integer that represents 
	// the depth of a TreeData object is returned if the object key is found in 
	// this BSTree; if not found -1 is returned.
	int depthHelper(Node *, const TreeData &) const;

	//-------------------------------- retrieveHelper -------------------------
	// Finds a TreeData object in the BSTree
	// the parameter is the TreeData to find in the tree. Return NULL if the 
	// item is not found.
	// Preconditions: the object passed in is a valid TreeData object
	// Postconditions:a pointer is returned if key is found, else(if key is not 
	// found) NULL is returned.
	TreeData * retrieveHelper(Node * , const TreeData &) const;

	//-------------------------------- insertHelper ---------------------------
	// Inserts character into the BSTree or increments the count if the 
	// character is found in the tree. 
	// Preconditions: TreeData object key has been allocated in memory
	// Postconditions: true is returned if key is inserted, and false gets
	// returned if key is found in this BSTree (thus, not inserted). if key is 
	// inserted for the first time, its count becomes 1, else its count gets
	// incremented by 1.
	bool insertHelper(Node *& , TreeData *);

	//--------------------------------makeEmptyHelper--------------------------
	// Clears the tree's contents, deleting the TreeData objects themselves
	// Preconditions: none
	// Postconditions: the tree's memory is deallocated
	void makeEmptyHelper(Node *&);

	//-----------------------------  displayhelper  ---------------------------
	// Outputs the contents of the BSTree to the console in the Frequency table 
	// format, required by the assignment specs (character followed by space
	// and followed by the frequency of that character).
	// Preconditions: root is not NULL
	// Postconditions: the constents of the tree get output to to console in
	// the inorder traversing manner. 
	ostream& displayHelper(ostream &, const BSTree &, Node *) const;

	//------------------------------  removeHelper  ---------------------------
	// Removes one occurrence of a character from the BST. 
	// Preconditions: the tree may have a character to remove
	// Postconditions: removeHelper is called; if count is greater than one, 
	// count is decremented and true is returned. If count is 1, the item is 
	// removed from the tree and true is returned. Otherwise, false is returned
	bool removeHelper(Node *& , const TreeData &);

	//------------------------------  removeRoot  -----------------------------
	// Removes a node with the last occurrence of a character from the BST. 
	// Preconditions: root is not NULL; the tree has this character and it is 
	// the character's last occurrence
	// Postconditions: the node with the character is removed, and the new root
	// is assigned to the value returned by findAndDeleteSmallest()
	void removeRoot(Node *&);

	//------------------------------  findAndDeleteSmallest  ------------------
	// Finds the node with the smallest TreeData value
	// Preconditions: root is not NULL
	// Postconditions: the smallest value in the subtree is returned and node
	// is deleted
	TreeData * findAndDeleteSmallest(Node *& , int &);

	//----------------------------------  findDescendants  --------------------
	// Finds the number of descendants of a node with the given TreeData object
	// Preconditions: the TreeData object is valid and this tree may contain a 
	// node with the given TreeData object
	// Postconditions: countDescendants is called if the given character is at
	// the root of the tree; the integer that represents the number of 
	// descendants of a TreeData object is returned if the object key is found
	// in this BSTree; if not found -1 is returned.
	int findDescendants(Node *, const TreeData &) const;

	//----------------------------------  countDescendants  -------------------
	// Counts the number of descendants of given TreeData object
	// Preconditions: this tree does contain a node with the given TreeData 
	// object
	// Postconditions: the integer that represents the number of descendants of
	// a TreeData object is returned.
	int countDescendants(Node * )const;

	//----------------------------------  copyTree  ---------------------------
	//Copies contents of sourceTree into this BSTree
	//Preconditions: this tree is empty (its root is NULL)
	//Postconditions:sourceTree gets copied into this BSTree--> this tree is
	// equal to sourceTree
	void copyTree(Node *&, Node *) const;

	//------------------------------  areEqual  -------------------------------
	// Determines if two BSTrees are equal.
	// Preconditions: both trees are allocated in memory
	// Postconditions: true is returned if the trees have the same data, the 
	// same structure, and the same number of occurrences for each character, 
	// false otherwise.
	bool areEqual(Node *, Node *) const;
};

