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
* Class to store key and satellite data together
*/
class satKey
{
	private:
		char satellite; // stores character value for satellite data
		int key; // stores int value for key data
	public:
		satKey();
		void setSatellite(char val); //  function to set satellite value
		char getSatellite(); // accessor function to get satellite value
		void setKey(int val); //  function to set key value
		int getKey(); // accessor function to get key value
};

// Course constructor for the Class hashValue 
satKey::satKey()
{
	satellite = '*';
	key = -1;
}

// Mutator function to set satellite
void satKey::setSatellite(char val)
{
	satellite = val;
}

// Accessor function to get satellite value
char satKey::getSatellite()
{
	return satellite;
}

// Mutator function to set key
void satKey::setKey(int val)
{
	key = val;
}

// Accessor function to get key value
int satKey::getKey()
{
	return key;
}

/**
* Class to create a linkedlist to use for task 1 and task 2 implementations
*/
class hashValue
{
	private:
		char satellite; // stores character value for satellite data
		int key; // stores int value for key data
		class hashValue* ptr_next; // pointer for next value
	public:
		hashValue(); // constructor class
		void setSatellite(char val); //  function to set satellite value
		char getSatellite(); // accessor function to get satellite value
		void setKey(int val); //  function to set key value
		int getKey(); // accessor function to get key value
		void setNext(class hashValue* ptr); // function to set next pointer
		class hashValue* getNext(); // accessor function to get next pointer
};

// Course constructor for the Class hashValue 
hashValue::hashValue()
{
	satellite = '*';
	key = -1;
	ptr_next = NULL;
}

// Mutator function to set satellite
void hashValue::setSatellite(char val)
{
	satellite = val;
}

// Accessor function to get satellite value
char hashValue::getSatellite()
{
	return satellite;
}

// Mutator function to set key
void hashValue::setKey(int val)
{
	key = val;
}

// Accessor function to get key value
int hashValue::getKey()
{
	return key;
}

// Mutator function to set ptr_next
void hashValue::setNext(class hashValue* ptr)
{
	ptr_next = ptr;
}

// Accessor function to get ptr_next
class hashValue* hashValue::getNext()
{
	return ptr_next;
}

/**
* Passes a list (stored in a vector) and sorts it in descending order with bubble sort
* @param vector list -- list to be sorted, passed by pointer
* @return vector output -- output retrieved from table based on the search keys, '*' if a search key is not found
*/
vector<char> directAddress(vector<int>* keys, vector<char>* satellite, vector<int>* searchKeys)
{
	int maxKeySize = 0; // variable to store max key size
	vector<char> hashTable, directTable; // create vectors to store hash table and resulting direct table
	int sizeOutput = searchKeys->size(); // variable to store how many output values
	directTable.resize(sizeOutput, '*'); // resizes output and fills with *

	// loop to find largest key value
	for (unsigned int i = 0; i < keys->size(); i++)
	{
		if (keys->at(i) > maxKeySize)
			maxKeySize = keys->at(i);
	}

	// resize hashtable vector to be equal to maxKeySize+1 and fill with '*'
	hashTable.resize(maxKeySize+1, '*');

	// loop through keys vector and assign the corresponding satellite data to the hashtable
	for (unsigned int i = 0; i < keys->size(); i++)
	{
		hashTable[keys->at(i)] = satellite->at(i);
	}

	// check the hashtable for values from the search keys
	for (unsigned int i = 0; i < searchKeys->size(); i++)
	{
		directTable[i] = hashTable[searchKeys->at(i)];
	}

	// return resulting info
	return directTable;
}

/**
* Passes a list (stored in a vector) and sorts it in descending order with selection sort
* @param vector list -- list to be sorted, passed by pointer
* @return void
*/
vector<char> separateChaining(vector<int>* keys, vector<char>* satellite, int* modulusValue, vector<int>* searchKeys)
{
	vector<hashValue*> hashTable; // vector to store hashTable pointers
	vector<char> directTable; // vector to store char values for direct table
	class hashValue* currentPtr; // pointer for current pointer data
	int sizeOutput = searchKeys->size(); // variable to store how many output values
	directTable.resize(sizeOutput, '*'); // resizes output and fills with *

	// resize hashTable vector to equal modulus size
	hashTable.resize(*modulusValue, NULL); 

	// loops through key vector and adds data to hashTable vector
	for (unsigned int i = 0; i < keys->size(); i++)
	{
		class hashValue* newPtr = new class hashValue; // pointer for data at i
		newPtr->setSatellite(satellite->at(i)); // stores satellite data
		newPtr->setKey(keys->at(i)); // stores key value
		currentPtr = hashTable[keys->at(i) % *modulusValue]; // assigns current pointer value

		// checks if current pointer is NULL
		if (currentPtr == NULL)
		{
			// assigns newPtr to that location in hashtable
			hashTable[keys->at(i) % *modulusValue] = newPtr;
		}

		else 
		{
			// updates current pointer until it is not NULL
			while (currentPtr->getNext() != NULL)
			{
				currentPtr = currentPtr->getNext();
			}
			// assigns newPtr to chain
			currentPtr->setNext(newPtr);
		}
	}

	// loops through searchKeys to find them in hashTable
	for (unsigned int i = 0; i < searchKeys->size(); i++)
	{
		currentPtr = hashTable[searchKeys->at(i) % *modulusValue]; // assigns current pointer value
		char charFound = '*'; // sets starting charFound (if it is not found)
		// loops while current pointer is not NULL
		while (currentPtr != NULL)
		{
			// checks to see if the key matches the search key
			if (currentPtr->getKey() == searchKeys->at(i))
			{
				charFound = currentPtr->getSatellite(); // updates charFound with satellite data
				break; // breaks from loop
			}
			currentPtr = currentPtr->getNext(); // updates current pointer value
		}
		directTable[i] = charFound; // assigns found satellite into directTable or '*' if nothing was found
	}

	return directTable; // returns direct table
}

/**
* Passes a list (stored in a vector) and sorts it in descending order with merge sort (with selection sort)
* @param vector list -- list to be sorted, passed by pointer
* @return void
*/
vector<char> quadProbing(vector<int>* keys, vector<char>* satellite, int* modulusValue, vector<int>* searchKeys)
{
	// vectors to store hash table and direct table
	vector<satKey> hashTable; vector<char> directTable; 
	int sizeOutput = searchKeys->size()+1; // variable to store how many output values
	directTable.resize(sizeOutput-1, '*'); // resizes output and fills with *
	int counter = 0; int current = 0; // sets counter equal to 0
	int modulusV = keys->size()+10;

	hashTable.resize(modulusV, satKey()); // resizes hashtable to be equal to modulus size

	// loops through key values and stores them in hash table
	for (unsigned int i = 0; i < keys->size(); i++)
	{
		// checks to see if hashtable spot is empty
		if (hashTable[keys->at(i) % modulusV].getSatellite() == '*')
		{
			hashTable[keys->at(i) % modulusV].setSatellite(satellite->at(i)); // assigns data to empty location 
			hashTable[keys->at(i) % modulusV].setKey(keys->at(i)); // assigns data to empty location 
		}

		else
		{
			// loops through the hashTable until an empty location is found
			while (hashTable[(keys->at(i) + counter * counter) % modulusV].getSatellite() != '*')
			{
				counter++; // increases counter
			}
			hashTable[(keys->at(i) + counter * counter) % modulusV].setSatellite(satellite->at(i)); // assigns data to empty location
			hashTable[(keys->at(i) + counter * counter) % modulusV].setKey(keys->at(i)); // assigns data to empty location
			counter = 0; // resets counter
		}
	}

	// loops through search keys to try and locate satellite data
	for (unsigned int i = 0; i < searchKeys->size(); i++)
	{
		char charFound = '*'; // sets starting charFound (if it is not found)
		counter = 0; // sets counter
		current = searchKeys->at(i) % modulusV; // sets current

		// loops while space is not empty
		while (hashTable[current].getSatellite() != '*')
		{
			// checks to see if keys are equal

			if (hashTable[current].getKey() == searchKeys->at(i))
			{
				charFound = hashTable[current].getSatellite(); // updates found character
				break; // breaks from loop
			}
			counter++; // updates counter
			current = (searchKeys->at(i) + counter * counter) % modulusV; // updates current value

		}

		directTable[i] = charFound; // assigns directTable value
	}

	return directTable; // returns directTable
}

/**
*  Uses cin to read in the input and modify various variables
*  @param vector keys -- list to be modified, passed by pointer
*  @param vector satellite -- list to be modified, passed by pointer
*  @param vector searchKeys -- list to be modified, passed by pointer
*  @param char modulusValue -- char to store modulus
*  @param char task -- char to store task variable, number '0' or '1' or '2' to specifiy which operation should be performed, passed by pointer
*/
char readInput(vector<int>* keys, vector<char>* satellite, char* task, int* modulusValue, vector<int>* searchKeys)
{
	// input processing variables
	char c;
	int n;
	char q;

	c = cin.peek(); // peek to see if the next value is a -1

	// loop through input until -1 is found
	while (c != '-')
	{
		cin >> n; // read in next value
		keys->push_back(n); // add to vector
		c = cin.peek(); // peek to see next value

		// loop to avoid space/blank characters
		while (isblank(c))
		{
			cin.ignore(1); // ignore cin if c is a space
			c = cin.peek(); // peek to see next value
		}
	}
	
	// clear '-1' from cin values
	c = cin.peek();
	if (c == '-')
		cin >> q;
	c = cin.peek();
	if (c == '1')
		cin >> q;
	c = cin.peek();

	// loop through input until * is found
	while (c != '*')
	{
		cin >> q; // read in next value
		satellite->push_back(q); // add to vector
		c = cin.peek(); // peek to see next value

		// loop to avoid space/blank characters
		while (isblank(c))
		{
			cin.ignore(1); // ignore cin if c is a space
			c = cin.peek(); // peek to see next value
		}
	}

	// clear '*' from cin values
	c = cin.peek();
	if (c == '*')
		cin >> q;

	cin >> *task; 	// read in task value
	cin >> *modulusValue; // read in modulus value

	c = cin.peek();
	// loop through input until -1 is found
	while (c != '-')
	{
		cin >> n; // read in next value
		searchKeys->push_back(n); // add to vector
		c = cin.peek(); // peek to see next value

		// loop to avoid space/blank characters
		while (isblank(c))
		{
			cin.ignore(1); // ignore cin if c is a space
			c = cin.peek(); // peek to see next value
		}
	}

	return 0; // end function
}

/**
*  Uses cout to print a sorted list (stored in a vector)
*  @param vector a -- list to be printed
*  @return void
*/
void print(vector<char> a)
{
	// loops through input vector
	for (unsigned int i = 0; i < a.size(); i++)
		cout << a.at(i) << ' '; // print vector value at i and a space
}

int main()
{
	vector <int> keys, searchKeys; 	// declare list for keys and searchKeys
	vector <char> satellite, directTable; //declare list for satellite
	char task;
	int modulusValue;
	readInput(&keys, &satellite, &task, &modulusValue, &searchKeys); // read input, modify list, and set task
	int sizeOutput = searchKeys.size(); // variable to store how many output values
	directTable.resize(sizeOutput-1, ' '); // resizes output and fills with *

	// perform task 0, bubble sort
	if (task == '0')
	{
		directTable = directAddress(&keys, &satellite, &searchKeys); // implement with direct address table
	}

	// perform task 1, merge sort (with selection sort)
	else if (task == '1')
	{
		directTable = separateChaining(&keys, &satellite, &modulusValue, &searchKeys); // implement with hash table with collisions by separte chaining
	}

	else if (task == '2')
	{
		directTable = quadProbing(&keys, &satellite, &modulusValue, &searchKeys); // implement with hash table with collisions by ppen addressing plus quadratic probing
	}

	print(directTable); // print output

	return 0; // exit
}