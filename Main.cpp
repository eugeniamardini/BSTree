//---------------------------------------------------------------------------
// MAIN.CPP
// Driver code for testing BSTree (Binary Search Tree) class.
// Authors:  Clark Olson and Carol Zander
//---------------------------------------------------------------------------
// This code tests all of the basic functionality of the BSTree class
// for CSS 343 HW 2.  It is not meant to exhaustively test the class.
//
// Assumptions:
//   -- a text file named "HW2.txt" exists in the same directory as the code
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "BSTree.h"
using namespace std;


//-------------------------- buildTree --------------------------------------
// Builds a BSTree of characters by reading them from a file stream
// Preconditions:   infile has been successfully initialized
// Postconditions:  T stores the characters (and number of occurrences)
//                   of the unprocessed characters remaining in infile, 
//                   (in addition to whatever was previously stored in T)

void buildTree(ifstream &infile, BSTree &T) {
   char ch;

   for (;;) {
      ch = infile.get();                   // gets each and every character
      if (infile.eof()) break;             // no more data

      TreeData* ptr = new TreeData(ch);
      bool success = T.insert(ptr); 
      if (!success) {                      // must be repeat character
         delete ptr;                       // deallocate if not inserted 
      }
   }
}



//-------------------------- main -------------------------------------------
// Tests the BSTree class by reading data from "test.txt" and playing with it
// Preconditions:   None (although it won't test anything if "test.txt"
//					 doesn't exist.)
// Postconditions:  All of the basic operations of the BSTree class are used. 
//                  Should compile, run to completion, and output correct 
//                  answers if BSTree is implemented correctly.

int main() {
   // create file object and open the datafile
   ifstream infile("HW2.txt");
   if (!infile) {
      cerr << "File could not be opened." << endl;
      return 1;
   }

   // test copy constructor, operator=, self-assignment
   BSTree T, T2, duplicate;
   buildTree(infile, T);
     // test operator<<
   cout << "Frequency table:  " << endl;
   cout << T;
   cout << endl;
   BSTree first(T);
   duplicate = duplicate = T;
   cout << duplicate << endl;
   duplicate.makeEmpty();
   cout << "empty dup " << duplicate << endl;

   // test operator<<
   cout << "Frequency table:  " << endl;
   cout << T;
   cout << endl;

   // test retrieve
   const TreeData *p1 = T.retrieve('n');  // need char TreeData constructor
   cout << "Retrieve 'n':       " << (p1 != NULL ? "found" : "not found") 
      << endl;
   const TreeData *p2 = T.retrieve('z');  
   cout << "Retrieve 'z':       " << (p2 != NULL ? "found" : "not found") 
      << endl;

   //test operator==, operator!=
   T2 = T;
   cout << "T == T2?            " << (T == T2 ? "equal" : "not equal") << endl;
   cout << "T != T2?            " << (T != T2 ? "not equal" : "equal") << endl;
   BSTree T3 = T2;                        // test copy constructor, too
   T2.makeEmpty();
   TreeData *newData = new TreeData('z'); 
   bool success = T3.insert(newData);
   if (!success) delete newData;
   cout << "T == T3?            " << (T == T3 ? "equal" : "not equal") << endl;
   cout << "T != T3?            " << (T != T3 ? "not equal" : "equal") << endl;

   // test depth and descendants
   // if 'q' is in tree, might want to try another character
   cout << "depth of 'a': " << T.depth('a') << endl;
   cout << "depth of 'q': " << T.depth('q') << endl;
   cout << "descendants of 'a': " << T.descendants('a') << endl;
   cout << "descendants of 'q': " << T.descendants('q') << endl;

   // test remove
   if (!T.remove('f'))
	   cout << "Node 'f' not found." << endl;
   else
	   cout << "Node 'f' removed." << endl;
   cout << "depth of 'a':       " << T.depth('a') << endl;
   if (!T.remove('q'))
	   cout << "Node 'q' not found." << endl;
   else
	   cout << "Node 'q' removed." << endl;
   cout << "depth of 'q':       " << T.depth('q') << endl;
   cout << "freq : " << T << endl;
   // test isEmpty, makeEmpty
   cout << "T empty?            " << (T.isEmpty() ? "empty" : "not empty") << endl;
   cout << "Making T empty. " << endl;
   T.makeEmpty();
   cout << "T empty?            " << (T.isEmpty() ? "empty" : "not empty") << endl;

   return 0;
}