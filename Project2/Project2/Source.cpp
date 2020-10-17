/*
* Name: Sarah Brown
* ID: 113386317
* Course: CS 2413
* Assignment 2: implement doubly linked list and binary search on input data.
*/

#include <iostream>
const int MAX_SIZE = 256;

using namespace std;

class Course* head = NULL;

/*
* Class definition for course capacity storage
*/
class Course
{
private:
	int capacity;
	class Course* ptr_prev;
	class Course* ptr_next;
public:
	Course();
	void setCapacity(int val);
	int getCapacity();
	void setPrev(class Course* ptr);
	class Course* getPrev();
	void setNext(class Course* ptr);
	class Course* getNext();
};

/*
* Course constructor for the Class course
*/
Course::Course()
{
	capacity = 0;
	ptr_prev = NULL;
	ptr_next = NULL;
}

/*
* Accessor function for capacity
*/
void Course::setCapacity(int val)
{
	capacity = val;
}

/*
* Accessor function for capacity
*/
int Course::getCapacity()
{
	return capacity;
}

/*
* Accessor function for ptr_prev
*/
void Course::setPrev(class Course* ptr)
{
	ptr_prev = ptr;
}

/*
* Accessor function for ptr_prev
*/
class Course* Course::getPrev()
{
	return ptr_prev;
}

/*
* Accessor function for ptr_next
*/
void Course::setNext(class Course* ptr)
{
	ptr_next = ptr;
}

/*
* Accessor function for ptr_next
*/
class Course* Course::getNext()
{
	return ptr_next;
}

/*
* Function to return length of linked list
*/
int getListLength()
{
	class Course* curNode = head;
	int count = 0;
	while (curNode != NULL)
	{
		count++;
		curNode = curNode->getNext();
	}
	return count;
}

/*
* Function to return Course pointer at particular index
*/
class Course* getItemAtIndex(int index)
{
	int listLength = getListLength();

	// empty list
	if (head == NULL)
	{
		return NULL;
	}

	// index outside of list length
	else if (index > listLength)
	{
		return NULL;
	}

	// returns pointer at specific index by increasing curNode
	else
	{
		class Course* curNode = head;

		for (int i = 0; i < index; i++)
		{
			curNode = curNode->getNext();
		}
		return curNode;
	}
}

/*
* Function to perform binary search
*/
int binarySearch(int searchKey)
{
	// get length of linked list
	int length = getListLength();

	// set starting low/high values
	int low = 0;
	int high = length - 1;

	// loop through until the low/high values match
	while (high >= low)
	{
		// set midpoint
		int midpoint = (high + low) / 2;

		// move domain right
		if (getItemAtIndex(midpoint)->getCapacity() < searchKey)
		{
			low = midpoint + 1;
		}

		// move domain left
		else if (getItemAtIndex(midpoint)->getCapacity() > searchKey)
		{
			high = midpoint - 1;
		}

		// return index of value
		else
		{
			return midpoint;
		}
	}

	// value not contained
	return -1;
}

/*
* Function to insert value
*/
void insert_value(int val)
{
	// declare and allocate pointer
	class Course* newPtr = new class Course;
	class Course* curNode = NULL;
	newPtr->setCapacity(val);

	// case 1, no head
	if (head == NULL)
	{
		head = newPtr;
	}

	// case 2, normal insert
	else
	{
		// find insert point
		// checks to see if new value is less than value at head of list
		if (newPtr->getCapacity() < head->getCapacity())
		{
			// insert value at head
			newPtr->setNext(curNode);
			curNode->setPrev(newPtr);
			head = newPtr;
		}

		else
		{
			// set current node to be head
			curNode = head;

			while (curNode != NULL)
			{
				// insert in middle of list
				if (newPtr->getCapacity() < curNode->getCapacity())
				{
					newPtr->setNext(curNode);
					newPtr->setPrev(curNode->getPrev());
					newPtr->getPrev()->setNext(newPtr);
					curNode->setPrev(newPtr);
					break;
				}

				// insert at end of list
				else if (curNode->getNext() == NULL)
				{
					newPtr->setPrev(curNode);
					curNode->setNext(newPtr);
					break;
				}

				// update current node pointer
				curNode = curNode->getNext();
			}
		}
	}
}

/*
* Function to delete value
*/
void delete_value(int index, int valDelete)
{
	// creates pointer to move and gets length of list
	class Course* curNode = head;
	int length = getListLength();

	// deletes head of list
	if (index == 0)
	{
		head = curNode->getNext();
		head->setPrev(NULL);
		delete curNode;
	}

	// deletes tail of list
	else if (index == length - 1)
	{
		curNode->getPrev()->setPrev(NULL);
		delete curNode;
	}

	// deletes object at index
	else
	{
		for (int i = 0; i < index; i++)
		{
			curNode = curNode->getNext();
		}

		curNode->getPrev()->setNext(curNode->getNext());
		curNode->getNext()->setPrev(curNode->getPrev());
		delete curNode;
	}
}

/*
* Function to print linked list
*/
void print()
{
	class Course* curNode = head;

	while (curNode != NULL)
	{
		cout << curNode->getCapacity() << " ";
		curNode = curNode->getNext();
	}
}

int main()
{
	// declare variables
	int task, searchKey;
	int nextInputVal;


	// read in command and searchKey
	cin >> task >> searchKey;

	// read in inputList
	cin >> nextInputVal;
	while (nextInputVal != 0)
	{
		insert_value(nextInputVal);
		cin >> nextInputVal;
	}

	// perform task 0, binary search
	if (task == 0)
	{
		int index = binarySearch(searchKey);
		cout << index;
	}

	// perform task 1, deletion/insertion
	else if (task == 1)
	{
		int index = binarySearch(searchKey);

		// insert
		if (index == -1)
		{
			insert_value(searchKey);
			print();
		}

		// delete
		else
		{
			delete_value(index, searchKey);
			print();
		}
	}

	return 0;
}