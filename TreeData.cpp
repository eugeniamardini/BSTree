//----------------------------------------------------------------------------
// TreeData.h
//Author: Yauheniya Zapryvaryna CSS 343 Winter 2015 UWB
//----------------------------------------------------------------------------
// DESCRIPTION: Class TreeData implements an abstract data type held by BSTree's
//			   nodes.The TreeData is represented by the character data type.
// FUNCTIONALITY: 
//	--compares 2 TreeData objects among themselves
//	--outputs the TreeData object to the console;
//	--creates a deep copy of one TreeData object 
// ASSUMPTIONS:
//	--text file to be read by the program contains only characters, w/o any 
//	  special cases (such as '\n', '\t' etc.)
//	--in overloaded operator<<, a TreeData object is displayed with no 
//	  surrounding spaces.
//-----------------------------------------------------------------------------

#include "TreeData.h"
#include <iostream>
using namespace std;

//-------------------------------Default Constructor---------------------------
// Preconditions:none
// Postconditions: a new TreeData object is created with ch of value '\0'
TreeData::TreeData()
{
	this->ch = '\0';
}

//-----------------------------Constructor-------------------------------------
// Preconditions:none
// Postconditions: a new TreeData object is created with the ch value equal to 
// parameter key
TreeData::TreeData(char key)
{
	this->ch = key;
}

//--------------------------------Copy Constructor----------------------------
// Makes a copy of a TreeData object
// Preconditions: character TreeData object has a valid ch value
// Postconditions: character is copied into this->ch
TreeData::TreeData (const TreeData &character)
{
	this->ch = character.ch;
}

//------------------------------  <  -----------------------------------------
// Determine if this TreeData object is smaller than the one passed in (key).
// Preconditions: two TreeData objects have a valid character value, and 
// can be compared by ASCII decimal value
// Postconditions: true is returned if this TreeData object's decimal value is
// smaller than of the one passed in as a parameter, and false if it is bigger.
bool TreeData::operator<(const TreeData &key) const
{
	return this->ch < key.ch;
}

//------------------------------  >  -----------------------------------------
// Determine if this TreeData object is bigger than the one passed in (key).
// Preconditions: two TreeData objects have a valid character value, and 
// can be compared by ASCII decimal value
// Postconditions: true is returned if this TreeData object's decimal value is
// bigger than of the one passed in as a parameter, and false if it's otherwise
bool TreeData::operator>(const TreeData &key) const
{
	return this->ch > key.ch;
}

//------------------------------  ==  -----------------------------------------
// Determine if two TreeData objects are equal
// key is the TreeData object to be compared to.
// Preconditions: both TreeData objects have a valid character value ch and can
// be compared by ASCII decimal value.
// Postconditions:true is returned if the objects have the same character value
// ch, false otherwise.
bool TreeData::operator==(const TreeData &key) const
{
	return this->ch == key.ch;
}

//------------------------------  !=  -----------------------------------------
// Determine if two TreeData objects are not equal.
// Preconditions: both TreeData objects have a valid character value ch and can
// be compared by ASCII decimal value.
// Postconditions:true is returned if the objects don't have the same character 
// value ch, false otherwise.
bool TreeData::operator!=(const TreeData &key) const
{
	return !(this->ch == key.ch);
}

//----------------------------------  =  --------------------------------------
// assignes TreeData object character to *this (making a deep copy)
// Preconditions: character TreeData object has a valid ch value
// Postconditions: character is copied into *this
const TreeData & TreeData::operator=(const TreeData &character)
{
	if (this == &character)
	{
		return *this;
	}
	this->ch = character.ch;
}

//-----------------------------  <<  ----------------------------------------
// Overloaded output operator for class TreeData; key is the TreeData object
// to be output.
// Preconditions: a TreeData object must have a valid character value ch
// Postconditions: the TreeData's value (char) is sent to the output w/o
// spaces.
ostream& operator<<(ostream& output, const TreeData &key)
{
	output << key.ch;
	return output;
}

//---------------------------- Destructor -------------------------------------
// Destructor for class TreeData
// Preconditions: none
// Postconditions: TreeData object is destructed appropriately
TreeData::~TreeData()
{
}
