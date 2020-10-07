#include <iostream>
using namespace std;

int main()
{
	// declare variables
	int task, numArrayItems;
	int rowVal, colVal, val;
	int outRowSize, outColSize;

	// read in task number and number of non-zero entries 
	cin >> task >> numArrayItems;

	// create arrays and initalize them with 0s for X and Z and with data from Fig 2 for Y
	int arrayX[5][8] = {0};
	int arrayY[5][8] = { 
		{1, 0, 0, 9, 0, 5, 0, 0},
		{0, 0, 0, 0, 2, 0, 0, 3},
		{0, 4, 0, 0, 0, 0, 8, 0},
		{0, 0, 2, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 7, 0, 0, 0}
	};
	int arrayZ[8][8] = {0};


	// read in efficient rep and create sparse matrix X
	for (int i = 0; i < numArrayItems; i++) 
	{
		cin >> rowVal >> colVal >> val;

		arrayX[rowVal][colVal] = val;
	}

	// perform task 1, transpose matrix X
	if (task == 1) 
	{
		// loop through each entry of matrix X
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				// add i,j entry of matrix X to j,i spot of Matrix Z
				arrayZ[j][i] = arrayX[i][j];
			}
		}

		// define row/col size of output matrix Z based on task number
		outRowSize = 8;
		outColSize = 5;
	}

	// perform task 2, add matrix X and matrix Y
	if (task == 2)
	{
		// loop through each entry of matrix X and Y
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				// add matrix X and matrix Y and store the result in matrix Z
				arrayZ[i][j] = arrayX[i][j] + arrayY[i][j];
			}
		}

		// define row/col size of output matrix Z based on task number
		outRowSize = 5;
		outColSize = 8;
	}

	// perform task 3, matrix multiplication
	if (task == 3)
	{
		// create a new matrix Xtranspose
		int arrayXtranspose[8][5] = {0};

		// loop through each entry of matrix X to transpose it and store the result in arrayXtranspose
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				arrayXtranspose[j][i] = arrayX[i][j];
			}
		}
		
		// loop through each square in the 8x8 output matrix and compute the result for that square
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				// create a temp variable to hold the sum
				int sum = 0;
				for (int k = 0; k < 5; k++)
				{
					// compute the sum of the multiplication of each part of row/column for matrix multi
					sum += arrayXtranspose[i][k] * arrayY[k][j];
				}
				arrayZ[i][j] = sum; // store sum in its spot

			}
		}

		// define row/col size of output matrix Z based on task number
		outRowSize = 8;
		outColSize = 8;
	}

	// output Z matrix efficient rep
	for (int i = 0; i < outRowSize; i++)
	{
		for (int j = 0; j < outColSize; j++)
		{
			int val = arrayZ[i][j];
			if (val != 0) // outputs non zero values of matrix Z
			{
				cout << i << " " << j << " " << val << " ";
			}
		}
	}

	return 0;
}