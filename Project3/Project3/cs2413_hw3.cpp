/**
* CS 2413 - Assignment 3: implement sorting lists in descending order with bubble sort and merge sort
* @file cs2413_h3.cpp
* @author Sarah Brown
*/

#include <iostream>
#include <vector>
const int MAX_SIZE = 256;
using namespace std;

/**
* Passes a list (stored in a vector) and sorts it in descending order with bubble sort
* @param vector list -- list to be sorted, passed by pointer
* @return void
*/
void bubbleSort(vector<int> *list)
{
	bool swap; // boolean to tell if a swap has occured on loop pass
	int temp; // temp variable to store swapped
	for (unsigned int i = 0; i < list->size(); i++) // loops through list until sorted
	{
		swap = false; // sets swap to be false on each loop through list
		for (unsigned int j = 0; j < list->size()-i-1; j++) // passes through list to sort one item
		{
			if (list->at(j) < list->at(j + 1)) // if current item is smaller than the next item
			{
				temp = list->at(j); // stores value at j
				(*list)[j] = (*list)[j + 1]; // updates value at j to be value at j+1
				(*list)[j + 1] = temp; // changes value at j+1 with temp variable
				swap = true; // changes bool to be true since swap happened
			}
		}

		if (!swap) // breaks out of for loop if a pass of the loop occurred without a swap
		{
			break; // break out of loop
		}
	}
}

/**
* Passes a list (stored in a vector) and sorts it in descending order with selection sort
* @param vector list -- list to be sorted, passed by pointer
* @return void
*/
void selectionSort(vector<int> *list)
{
	int indexLargest; // stores index of largest value
	int temp; // temp variable for swapping
	
	for (unsigned int i = 0; i < list->size() - 1; ++i) 
	{
		indexLargest = i; // stores current index of largest value
		for (unsigned int j = 1 + i; j < list->size(); ++j)
		{
			// if value at index j is greater than value at index i, update index
			if (list->at(j) > list->at(i))
			{
				indexLargest = j; // updates largest value index
			}
		}

		// swaps values if a new largest is found
		if (i != indexLargest)
		{
			temp = list->at(i); // stores value at i
			(*list)[i] = (*list)[indexLargest]; // updates value at i to be value at the largestIndex
			(*list)[indexLargest] = temp; // changes value at largestIndex with temp value
		}
	}
}

/**
* Passes a list (stored in a vector) and sorts it in descending order with merge sort (with selection sort)
* @param vector list -- list to be sorted, passed by pointer
* @return void
*/
void mergeSort(vector<int> *list)
{
	int mergeIndex = 0; // merge position
	unsigned int leftIndex = 0; // left position
	unsigned int rightIndex = 0; // right position
	int middle = (list->size()) / 2; // variable to store midpoint of list
	vector<int> leftVector {list->begin(), list->begin()+middle}; // make left subvector
	vector<int>	rightVector {list->begin()+middle, list->end()}; // make right subvector

	selectionSort(&leftVector); // sort left subvector
	selectionSort(&rightVector); // sort right subvector

	// loop to merge two subvectors, will leave loop when one subvector is empty
	while (leftIndex < leftVector.size() && rightIndex < rightVector.size())
	{
		// if left is bigger, add value from left subvector
		if (leftVector.at(leftIndex) >= rightVector.at(rightIndex))
		{
			(*list)[mergeIndex] = leftVector.at(leftIndex); // add value back to the sorted list
			leftIndex++; // increase left position index
		}

		// otherwise, right will be bigger so add value from right subvector
		else
		{
			(*list)[mergeIndex] = rightVector.at(rightIndex); // add value back to the sorted list
			rightIndex++; // increase right position index
		}
		mergeIndex++; // increase merge position index
	}

	// while there are still values in the left subvector, add them back to the sorted list
	while (leftIndex < leftVector.size())
	{
		(*list)[mergeIndex] = leftVector.at(leftIndex); // add value back to the sorted list
		leftIndex++; // increase left position index
		mergeIndex++; // increase merge position index
	}

	while (rightIndex < rightVector.size())
	{
		(*list)[mergeIndex] = rightVector.at(rightIndex); // add value back to the sorted list
		rightIndex++; // increase right position index
		mergeIndex++; // increase merge position index
	}
}

/**
*  Uses cin to read in the input and modify a list (stored in a vector)  and return the task number
*  @param vector list -- list to be modified, passed by pointer
*  @return task number '0' or '1' to specifiy which operation should be performed
*/
char readInput(vector<int> *list)
{
	// input processing variables
	char task, c;
	int n;

	cin >> task; 	// read in task value
	c = cin.peek(); // peek to see if the next value is a s

	// loop through input until an S is found
	while (c != 's' && c != 'S')
	{
		cin >> n; // read in next value
		list->push_back(n); // add to vector
		c = cin.peek(); // peek to see next value

		// loop to avoid space/blank characters
		while (isblank(c))
		{
			cin.ignore(1); // ignore cin if c is a space
			c = cin.peek(); // peek to see next value
		}
	}
	return task; // return task value
}

/**
*  Uses cout to print a sorted list (stored in a vector)
*  @param vector a -- list to be printed
*  @return void
*/
void print(vector<int> a)
{
	// loops through input vector
	for (unsigned int i = 0; i < a.size(); i++)
		cout << a.at(i) << ' '; // print vector value at i and a space
}

int main()
{
	vector <int> list; 	// declare list
	char task = readInput(&list); // read input, modify list, and set task

	// perform task 0, bubble sort
	if (task == '0')
	{
		bubbleSort(&list); // call bubbleSort function
	}

	// perform task 1, merge sort (with selection sort)
	else if (task == '1')
	{
		mergeSort(&list); // call mergeSort function
	}

	print(list); // print sorted list

	return 0; // exit
}