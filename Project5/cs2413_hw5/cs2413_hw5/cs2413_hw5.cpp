/**
* CS 2413 - Assignment 5: 
* @file cs2413_h5.cpp
* @author Sarah Brown
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> reverseVector(vector<int> vect); // prototype function

/*
* Class definition for a stack
*/
class biStack
{
	private:
		vector<int> stackData; // stores stack data
	public:
		biStack(); // constructor class
		vector<int> getStack(); // returns stack
		bool empty(); // checks if empty
		int size(); // returns size
		void push(int val); // pushes data on to stack
		int pop(); // pops data off of stack
		int peek(); // peeks next thing from stack
		void clear(); // clears stack
};

/*
* Course constructor for biStack
*/
biStack::biStack()
{
	stackData = {}; // sets stack vector to empty
}

/*
* Accessor Function to get stack vector
*/
vector<int> biStack::getStack()
{
	return stackData;
}

/*
* Checks if stack is empty
*/
bool biStack::empty()
{
	return stackData.empty();
}

/*
* Returns size of stack
*/
int biStack::size()
{
	return stackData.size();
}

/*
* Pushes a value onto the stack
*/
void biStack::push(int val)
{
	stackData.push_back(val);
}

/*
* Pops a value from the stack
*/
int biStack::pop()
{
	if (this->empty())
	{
		throw out_of_range("its empty, yeet"); // throws error if stack is empty
	}

	else
	{
		int dataPopped = stackData.back(); // assigns back of vector to variable
		stackData.pop_back(); // removes back of vector
		return dataPopped; // returns data
	}
}

/*
* Peek a value from the stack
*/
int biStack::peek()
{
	if (this->empty())
	{
		throw out_of_range("its empty, yeet"); // throws error if stack is empty
	}

	else
	{
		return stackData.back(); // returns back of vector
	}
}
/*
* Clears stack data
*/
void biStack::clear()
{
	stackData = {};
}

/*
* Class definition for node
*/
class node
{
	private:
		int nodeVal; // stores value of node
		class node* child_left; // stores pointer for left child
		class node* child_right; // stores pointer for right child
	public:
		node(int val); // constructor for node
		void setVal(int val); // sets value of node
		int getVal(); // gets value of node
		void setChildLeft(class node* ptr); // sets pointer for left child
		class node* getChildLeft(); // gets pointer for left child
		void setChildRight(class node* ptr); // sets pointer for right child
		class node* getChildRight(); // gets pointer for right child
};

/*
* Constructor function for node
*/
node::node(int val)
{
	// sets private variables to NULL and intializes node value
	nodeVal = val;
	child_left = NULL;
	child_right = NULL;
}

/*
* Mutator function for nodeVal
*/
void node::setVal(int val)
{
	nodeVal = val;
}

/*
* Accessor function for nodeVal
*/
int node::getVal()
{
	return nodeVal;
}

/*
* Mutator function for childLeft
*/
void node::setChildLeft(class node* ptr)
{
	child_left = ptr;
}

/*
* Accessor function for childLeft
*/
class node* node::getChildLeft()
{
	return child_left;
}

/*
* Mutator function for childRight
*/
void node::setChildRight(class node* ptr)
{
	child_right = ptr;
}

/*
* Accessor function for childRight
*/
class node* node::getChildRight()
{
	return child_right;
}

/*
* Class definition for biTree
*/
class biTree
{
private:
	class node* root; // stores pointer for root node
public: 
	biTree(); // constructor for biTree class
	void setRoot(class node* ptr); // sets root value
	class node* getRoot(); // gets root value
	void constructTree(vector<int> keys, class biStack* stack); // constructs bst
	bool treeSearch(int searchVal); // searches bst
	vector<int> treeInsertNode(int valInsert, class biStack* stack); // inserts node into bst
	vector<int> treeDeleteNode(int searchKey, class biStack* stack); // deletes node from bst
	void deleteTree(class node* ptr); // deletes tree and clears root node
	void treeEnumerate(class node* ptr, class biStack* stack); // enumerates tree

};

/*
* Course constructor for the biTree course
*/
biTree::biTree()
{
	// sets variables to NULL
	root = NULL;
}

/*
* Mutator function for childRight
*/
void biTree::setRoot(class node* ptr)
{
	root = ptr;
}

/*
* Accessor function for childRight
*/
class node* biTree::getRoot()
{
	return root;
}

/*
*  Function to construct binary search tree
*  @param vector keys -- list of input keys used to construct a binary search tree
*  @param biStack* stack -- pointer ref for stack
*  @return void
*/
void biTree::constructTree(vector<int> keys, class biStack* stack)
{
	for (unsigned int i = 0; i < keys.size(); i++)
	{
		treeInsertNode(keys[i], stack);
	}
}

/*
* Function to search binary search tree for a specific key
* @param int searchVal -- key that is being searched for
* @return bool -- true if key is found
*/
bool biTree::treeSearch(int searchVal)
{
	// creates pointer to keep track of position in tree
	node* curNode = NULL;
	curNode = this->getRoot(); 
	bool searchKeyFound = false;

	// loops through tree looking for spot to insert new node
	while (curNode != NULL)
	{
		// checks if current node value equals search key
		if (searchVal == curNode->getVal())
		{
			searchKeyFound = true;
			curNode = NULL;
		}

		// if search key is less than current node value, move to left branches
		else if (searchVal < curNode->getVal())
		{
			if (curNode->getChildLeft() == NULL)
			{
				curNode = NULL;
			}

			else
			{
				curNode = curNode->getChildLeft();
			}
		}

		// if search key is greater than current node value, move to right branches
		else
		{
			// if NULL spot to right, insert new node
			if (curNode->getChildRight() == NULL)
			{
				curNode = NULL;
			}

			// if not NULL, move current node to left child
			else
			{
				curNode = curNode->getChildRight();
			}
		}
	}

	return searchKeyFound;
}

/*
* Function to insert tree node
* @param int valInsert -- value to be inserted as a new node
* @param biStack* stack -- pointer ref for stack
* @return vector output -- returns new binary search key or -1 if search key already in tree
*/
vector<int> biTree::treeInsertNode(int valInsert, class biStack* stack)
{
	vector<int> insertOutput;
	node* newNode = new node(valInsert);
	node* curNode = NULL;

	// if root null
	if (this->getRoot() == NULL)
	{
		this->setRoot(newNode);
	}

	else
	{
		curNode = this->getRoot(); // creates pointer to keep track of position in tree

		// checks to see if value to insert already exists in tree, if it does returns vector with -1
		if (treeSearch(valInsert))
		{
			insertOutput = { -1 }; // adds -1 to output vector
			return insertOutput; // returns vector
		}

		// loops through tree looking for spot to insert new node
		while (curNode != NULL)
		{
			// if value to insert is less than the current node value, inserts/moves current node to the left
			if (newNode->getVal() < curNode->getVal())
			{
				// if NULL spot to left, insert new node
				if (curNode->getChildLeft() == NULL)
				{
					curNode->setChildLeft(newNode);
					curNode = NULL;
				}

				// if not NULL, move current node to left child
				else
				{
					curNode = curNode->getChildLeft();
				}
			}

			else
			{
				// if NULL spot to right, insert new node
				if (curNode->getChildRight() == NULL)
				{
					curNode->setChildRight(newNode);
					curNode = NULL;
				}

				// if not NULL, move current node to left child
				else
				{
					curNode = curNode->getChildRight();
				}
			}
		}
	}
	stack->clear(); // clear stack before enumerating tree
	treeEnumerate(this->getRoot(), stack); // sets output vector to be equal to tree transversal
	insertOutput = stack->getStack(); // get vector from stack
	stack->clear(); // clear stack before enumerating tree
	return insertOutput;
}

/*
* Function to delete a node containing a specific search key
* @param int searchKey -- value to be found and deleted
* @param biStack* stack -- pointer ref for stack
* @return vector<int> output -- new binary tree after deletetion or -1 if searchkey not in tree
*/
vector<int> biTree::treeDeleteNode(int searchKey, class biStack* stack)
{
	// creates vectors to store binary search tree info
	vector<int> enumeratedPreDelete, enumeratedPostDelete, deletedTreeOutput;

	// checks to see if search key is in tree and if it isn't returns -1
	if (!this->treeSearch(searchKey))
	{
		deletedTreeOutput = { -1 }; // adds -1 to output vector
		return deletedTreeOutput; // returns output vector
	}

	else
	{
		this->treeEnumerate(this->getRoot(), stack); // enumerates current binary search tree as a vector
		enumeratedPreDelete = stack->getStack();
		this->deleteTree(this->getRoot()); // deletes tree after tree stored in vector form

		// loops through vector and adds all values to a new vector except for search key
		for (unsigned int i = 0; i < enumeratedPreDelete.size(); i++)
		{
			if (enumeratedPreDelete[i] != searchKey) // checks if current value equals search key
			{
				enumeratedPostDelete.push_back(enumeratedPreDelete[i]); // only adds non search key
			}
		}

		stack->clear(); // clears stack before constructing new tree
		this->constructTree(reverseVector(enumeratedPostDelete), stack); // constructs new tree
		stack->clear(); // clears stack to enumerate postDelete data
		this->treeEnumerate(this->getRoot(), stack); // enumerates new tree
		deletedTreeOutput = stack->getStack();
	}
	return deletedTreeOutput; // outputs new tree enumeration
}

/*
* Function to delete a tree
* @param node* ptr -- pointer for root of tree to be deleted
* @return void
*/
void biTree::deleteTree(class node* ptr)
{
	if (ptr->getChildLeft() != NULL)
	{
		deleteTree(ptr->getChildLeft());
	}

	if (ptr->getChildRight() != NULL)
	{
		deleteTree(ptr->getChildRight());
	}
	this->setRoot(NULL);
	delete(ptr);
}

/*
* Function to enumerate binary search tree
* @param ptr -- pointer to current node
* @param biStack* stack -- pointer ref for stack
* @return void
*/
void biTree::treeEnumerate(class node* ptr, class biStack* stack)
{
	// uses recursion and a stack to enumerate binary search tree
	if (ptr->getChildLeft() != NULL)
	{
		treeEnumerate(ptr->getChildLeft(), stack); // moves to left branch
	}

	if (ptr->getChildRight() != NULL)
	{
		treeEnumerate(ptr->getChildRight(), stack); // moves to right branch
	}
	stack->push(ptr->getVal()); // adds to stack
}

/**
* Reads in input with cin and creates  
* @param vector list -- list to be sorted, passed by pointer
* @return void
*/
void readInput(vector<int>* keys, char* task, int* keyX)
{
	// input processing variables
	char c;
	int n;
	char q;

	c = cin.peek(); // peek to see if the next value is a s

	// loop through input until -1 is found
	while (c != 's' && c != 'S')
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
	if (c == 's' || c == 'S')
		cin >> q;

	cin >> *task; 	// read in task value
	cin >> *keyX; // read in modulus value
}

/**
*  Uses cout to print a sorted list (stored in a vector)
*  @param vector<int> -- list to be printed
*  @return void
*/
void print(vector<int> a)
{
	// loops through input vector
	for (unsigned int i = 0; i < a.size(); i++)
		cout << a.at(i) << ' '; // print vector value at i and a space
}

/**
*  Reverses a vector for use with enumeration (since gradescope compilier doesn't like reverse())
*  @param vector<int> vect -- vector to be reversed
*  @return vector<int> -- reversed vector
*/
vector<int> reverseVector(vector<int> vect)
{
	vector<int> reversedVect;
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		reversedVect.push_back(vect.at(vect.size()-1 - i));
	}
	return reversedVect;
}


int main()
{
	vector<int> keys, binarySearchTree; // declare vector for keys and the binary search tree
	char task; // stores task number
	int keyX; // stores key
	readInput(&keys, &task, &keyX); // read input, modify list, and set task
	biTree* constructedBiTree = new biTree(); // creates a new biTree
	biStack* constructedBiStack = new biStack(); // creates a new biStack
	constructedBiTree->constructTree(keys, constructedBiStack); // constructs tree with keys input
	
	// perform task 1, search key
	if (task == '1')
	{
		// checks to see if search key is in binary search tree
		if (constructedBiTree->treeSearch(keyX))
		{
			constructedBiTree->treeEnumerate(constructedBiTree->getRoot(), constructedBiStack); // enumerates tree if it contains key
			binarySearchTree = constructedBiStack->getStack();
		}

		else
		{
			binarySearchTree.push_back(-1); // if it does not contain the key, sets output vector to -1
		}
	}

	// perform task 2, insert key
	else if (task == '2')
	{
		binarySearchTree = constructedBiTree->treeInsertNode(keyX, constructedBiStack); // attempts to insert keyX into binary search tree
	}

	// perform task 3, delete key
	else if (task == '3')
	{
		binarySearchTree = constructedBiTree->treeDeleteNode(keyX, constructedBiStack); // attempts to delete keyX from binary search tree
	}

	print(binarySearchTree); // print output 
	return 0; // exit
}