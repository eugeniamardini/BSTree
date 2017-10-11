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

#include "BSTree.h"
#include <iostream>
using namespace std;

//-------------------------------Default Constructor---------------------------
// Creates a new BSTree object
// Preconditions:none
// Postconditions: a new BSTree object is created with root set to NULL
BSTree::BSTree()
{
	root = NULL;
}

//-----------------------------Constructor-------------------------------------
// Creates a new BSTree object
// Preconditions: TreeData pointer key points to a TreeData object, and this 
// BSTree is empty
// Postconditions: a new BSTree is created with the root equal to the value
// of a TreeData object passes in; root's children get initialized to NULL.
BSTree::BSTree(TreeData *key)
{
	if (key != NULL)
	{
		root->item = key;
		root->left = root->right = NULL;
	}
	root = NULL;
}

//--------------------------------Copy Constructor----------------------------
// makes a deep copy of a BSTree
// Preconditions: sourceTree must be allocated in memory
// Postconditions: sourceTree is copied into this tree
BSTree::BSTree (const BSTree &sourceTree)
{
	root = NULL;
	*this = sourceTree;
}

//-------------------------------- insert -------------------------------------
// Inserts a Node with a TreeData object's value into this BSTree
// Preconditions: TreeData object key has been allocated in memory
// Postconditions: insertHelper function is called and true is returned if key
// is inserted, and false gets returned if key is found in this BSTree (thus,
// not inserted). if key is inserted for the first time, its count becomes 1, 
// else its count gets incremented by 1.
bool BSTree::insert(TreeData *key)
{
	bool inserted;
	if (key != NULL)
	{
		inserted = insertHelper(root, key);
	}
	else
	{
		inserted = false;
	}
	return inserted;
}

//-------------------------------- insertHelper -------------------------------
// Inserts character into the BSTree or increments the count if the character 
// is found in the tree. 
// Preconditions: TreeData object key has been allocated in memory
// Postconditions: true is returned if key is inserted, and false gets
// returned if key is found in this BSTree (thus, not inserted). if key is 
// inserted for the first time, its count becomes 1, else its count gets
// incremented by 1.
bool BSTree::insertHelper (Node *&root, TreeData *key)
{
	bool inserted;
	if (root == NULL)
	{
		root = new Node;
		root->item = key;
		root->count=1;
		root->left = root->right = NULL;
		return true;
	}
	else
	{
		if (*key < *root->item)
		{
			inserted = insertHelper(root->left, key);
		}
		else if (*key > *root->item)
		{
			inserted =  insertHelper(root->right, key);
		}
		else
		{
			root->count++;
			inserted = false;
		}
	}
	return inserted;
}

//-------------------------------- retrieve -----------------------------------
// Finds a TreeData object in the BSTree
// Preconditions: key is a valid TreeData object
// Postconditions: retrieveHelper function is called and a pointer is
// returned if key is found, else (if key is not found) NULL is returned.
const TreeData * BSTree::retrieve(const TreeData & key) const
{
	TreeData *someNode = retrieveHelper(root, key);
	return someNode;
}

//-------------------------------- retrieveHelper -----------------------------
// Finds a TreeData object in the BSTree
// the parameter is the TreeData to find in the tree. Return NULL if the item
// is not found.
// Preconditions: key is a valid TreeData object
// Postconditions:a pointer is returned if key is found, else (if key is not 
// found) NULL is returned.
TreeData * BSTree::retrieveHelper(Node * root, const TreeData & key) const
{
	if (root == NULL)
	{
		return NULL;
	}
	else if (key == *root->item)
	{
		return root->item;
	}
	else if (key < *root->item)
	{
		return retrieveHelper(root->left , key);
	}
	else 
	{
		return retrieveHelper (root->right, key);
	}
}

//----------------------------------  =  --------------------------------------
//assignes one BSTree to another (making a deep copy)
//Preconditions: sourceTree has been allocated in memory
//Postconditions: this BSTree gets emptied, and sourceTree gets copied into 
//this BSTree with the help of copyTree function
const BSTree& BSTree::operator=(const BSTree &sourceTree)
{
	if (this == &sourceTree)
	{
		return *this;
	}
	this->makeEmpty();
	this->copyTree(this->root, sourceTree.root );
	return *this;
}

//----------------------------------  copyTree  -------------------------------
// Copies contents of sourceTree into this BSTree
// Preconditions: this tree is empty (root == NULL)
// Postconditions:sourceTree gets copied into this BSTree--> this tree is equal
// to sourceTree
void BSTree::copyTree(Node * &root,  Node * copyRoot) const
{
	if (copyRoot != NULL)
	{
		root = new Node;
		TreeData * ptr = new TreeData(*copyRoot->item);
		root->item = ptr;
		root->count=copyRoot->count;
		root->left = root->right = NULL;
		copyTree(root->left, copyRoot->left);
		copyTree (root->right, copyRoot->right);
	}
}

//----------------------------------  depth  ---------------------------------
// Finds the depth of a TreeData object in the BSTree
// Preconditions: key is a valid TreeData object and this tree may contain a
// node with the sought TreeData object
// Postconditions: depthHelper is called and the integer that represents the 
// depth of a TreeData object is returned if the object key is found in this 
// BSTree; if not found -1 is returned.
int BSTree::depth (const TreeData &key) const
{
	return depthHelper(root, key);
}

//----------------------------------  depthHelper  ----------------------------
// Finds the depth of a TreeData object in the BSTree
// Preconditions: root has been allocated in memory
// Postconditions: depthHelper is called and the integer that represents the 
// depth of a TreeData object is returned if the object key is found in this 
// BSTree; if not found -1 is returned.
int BSTree::depthHelper(Node *root, const TreeData &key) const
{
	if(root == NULL)
	{
		return -1;
	}
	if (*root->item == key)
	{
		return 0;
	}
	int tryBranch = depthHelper(root->left, key);
	if(tryBranch == -1)
	{
		tryBranch = depthHelper(root->right, key);
	}
	if(tryBranch == -1)
	{
		return -1;
	}
	else
	{
		return 1 + tryBranch;
	}
}

//----------------------------------  descendants  ----------------------------
// Finds the number of descendants of a node with the given TreeData object
// Preconditions: key is a valid TreeData object and this tree may contain a 
// node with the given TreeData object
// Postconditions: findDescendants is called and the integer that represents
// the number of descendants of a TreeData object is returned if the object key
// is found in this BSTree; if not found -1 is returned.
int BSTree::descendants (const TreeData &key) const
{
	int descendants;
	descendants = findDescendants (root, key);
	return descendants;
}

//----------------------------------  findDescendants  ------------------------
// Finds the number of descendants of a node with the given TreeData object
// Preconditions: the TreeData object key is valid and this tree may contain a 
// node with the given TreeData object
// Postconditions: countDescendants is called if the given character is at the 
// root of the tree; the integer that represents the number of descendants of a
// TreeData object is returned if the object key is found in this 
// BSTree; if not found -1 is returned.
int BSTree::findDescendants (Node * root, const TreeData &key) const
{
	if (root != NULL)
	{
		if (*root->item == key)
		{
			return countDescendants(root);
		}
		if( key < *root->item)
		{
			return findDescendants(root->left, key);
		}
		else if (key > *root->item)
		{
			return findDescendants(root->right, key);
		}
	}
	return -1;
}

//----------------------------------  countDescendants  -----------------------
//Counts the number of descendants of given TreeData object
//Preconditions: this tree does contain a node with the given TreeData object
//Postconditions: the integer that represents the number of descendants of a
//TreeData object is returned.
int BSTree::countDescendants (Node *root) const
{
	int descendantsLeft = 0, descendantsRight= 0;
	if (root == NULL)
	{
		return 0;
	}
	if (root->left != NULL )
	{
		descendantsLeft = countDescendants (root->left) + 1;
	}
	if (root->right != NULL)
	{
		descendantsRight = countDescendants(root->right) + 1;
	}
	return descendantsLeft + descendantsRight;
}


//------------------------------  ==  -----------------------------------------
// Determines if two BSTrees are equal.
// Preconditions: both trees are allocated in memory
// Postconditions: areEqual helper function is called, and true is returned if 
// the trees have the same data, the same structure, and the same number of 
// occurrences for each character, false otherwise.
bool BSTree::operator==(const BSTree &b) const
{
	return areEqual(this->root, b.root);
}

//------------------------------  areEqual  -----------------------------------
// Determines if two BSTrees are equal.
// Preconditions: both trees are allocated in memory
// Postconditions: true is returned if the trees have the same data, the same
// structure, and the same number of occurrences for each character, false
// otherwise.
bool BSTree::areEqual (Node *root, Node *r) const
{
	if(root == NULL)
	{
		return r == NULL;
	}
	if (r == NULL)
	{
		return false;
	}
	if (*r->item != *root->item)
	{
		return false;
	}
	if (r->count != root->count)
	{
		return false;
	}
	if (areEqual(root->left, r->left) && areEqual(root->right, r->right))
	{
		return true;
	}
	return false;
}

//------------------------------  !=  -----------------------------------------
// Determines if two BSTrees are not equal.
// Preconditions: both trees are allocated in memory
// Postconditions: false is returned if the trees have the same data, the same 
// structure, and the same number of occurrences for each character, true
// otherwise.
bool BSTree::operator!=(const BSTree &otherTree) const
{
	return !(*this == otherTree);
}

//------------------------------  remove  -------------------------------------
// Removes one occurrence of a character from the BST. 
// Preconditions: key is a valid TreeData object and the tree may have a 
// character to remove
// Postconditions: removeHelper is called; if count is greater than one, count 
// is decremented and true is returned. If count is 1, the item is removed from
// the tree and true is returned. Otherwise, false is returned

bool BSTree::remove(const TreeData &key)
{
	return removeHelper (root, key);
}

//------------------------------  removeHelper  -------------------------------
// Removes one occurrence of a character from the BST. 
// Preconditions: the tree may have a character to remove
// Postconditions: removeRoot is called if the characer's occurence is last in 
// the tree; true is returned if the character is found
// and its one occurrence removed, false if not found.
bool BSTree::removeHelper(Node * &root, const TreeData &key)
{
	if(root == NULL)
	{
		return false;
	}
	else if (key  == *root->item)
	{
		if (root->count == 1)
		{
			removeRoot(root);return true;
		}
		else 
		{
			root->count--;return true;
		}	
		
	}
	else if (key < *root->item)
	{
		return removeHelper(root->left, key);
	}
	else
	{
		return removeHelper(root->right, key);
	}
}

//------------------------------  removeRoot  ---------------------------------
// Removes a node with the last occurrence of a character from the BST. 
// Preconditions: root is not NULL; the tree has this character and it is the
// character's last occurrence
// Postconditions: the node with the character is removed, and the new root is
// assigned to the value returned by findAndDeleteSmallest()
void BSTree::removeRoot(Node *&root)
{
	if (root->left == NULL && root->right == NULL)
	{
		delete root->item;
		delete root;
		root = NULL;
	}
	else if (root->left ==NULL)
	{
		Node *temp = root;
		root = root->right;
		delete temp->item;
		delete temp;
	}
	else if (root->right == NULL)
	{
		Node *temp = root;
		root = root->left;
		delete temp->item;
		delete temp;
	}
	else
	{
		delete root->item;
		int count = 0;
		root->item = findAndDeleteSmallest(root->right, count);
		root->count = count;
	}
}

//------------------------------  findAndDeleteSmallest  ----------------------
// Finds the node with the smallest TreeData value
// Preconditions: root is not NULL
// Postconditions: the smallest value in the subtree is returned and node is
// deleted
TreeData * BSTree::findAndDeleteSmallest(Node *&root, int &count)
{
	if (root->left == NULL)
	{
		TreeData *key = root->item;
		count = root->count;
		Node *temp = root;
		root = root->right;
		delete temp;
		return key;
	}
	else
	{
		return findAndDeleteSmallest(root->left, count);
	}
}

//--------------------------------makeEmpty------------------------------------
// Empties the BSTree
// Preconditions: none
// Postconditions: the helper function is called, and the tree's memory is 
// deallocated
void BSTree::makeEmpty()
{
	makeEmptyHelper(root);
}

//--------------------------------makeEmptyHelper------------------------------
// Clears the tree's contents, deleting the TreeData objects themselves
// Preconditions: none
// Postconditions: the tree's memory is deallocated
void BSTree::makeEmptyHelper(Node * &root)
{
	if (root != NULL)
	{
		makeEmptyHelper(root->left);
		makeEmptyHelper(root->right);
		delete root->item;
		delete root;
		root = NULL;
	}
}

//--------------------------------isEmpty------------------------------------
// Checks whether the BSTree is empty
// Preconditions: the BSTree has a root with allocated memory 
// Postconditions: true is returned if BSTree is empty, false otherwise.
bool BSTree::isEmpty() const
{
	return root == NULL;
}

//-----------------------------  <<  ----------------------------------------
// Overloaded output operator for class BSTree
// Preconditions: root is not NULL and b (BSTree) is allocated in memory
// Postconditions: the displayHelper function is called upon this tree, 
// and the constents of the tree get output to to console in the inorder
// manner. 
ostream& operator<<(ostream& output, const BSTree &b)
{
	return b.displayHelper(output, b, b.root);
}

//-----------------------------  displayhelper  -------------------------------
// Outputs the contents of the BSTree to the console in the Frequency table 
// format, required by the assignment specs (character followed by space and 
// followed by the frequency of that character).
// Preconditions: root is not NULL
// Postconditions: the constents of the tree get output to to console in the 
// inorder traversing manner. 
ostream& BSTree::displayHelper(ostream& output, const BSTree &b, Node *root) const
{
	if (root != NULL)
	{
		displayHelper(output, b, root->left);
		output << *root->item << " " << root->count<< endl;
		displayHelper(output, b, root->right);
	}
	return output;
}

//---------------------------- Destructor -------------------------------------
// Destructor for class BSTree
// Preconditions: none
// Postconditions: BSTree is destructed, memory occupied previously by the tree
// is deallocated
BSTree::~BSTree()
{
	this->makeEmpty();
}
