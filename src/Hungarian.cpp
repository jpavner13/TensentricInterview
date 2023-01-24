/* 	
	For this algorithm, I used a common c++ wrapper and an equivilent MatLab function as refrence and rewrote and optimized them both for 
	best use in this application. The biggest thing that I was able to do to reduce space and complexity was the fact that we know that the
	distance vector that I created will always be square since the amount of pucks and spaces occupied will always be the same. We also know 
	that the values in the matrix I created will always be positive. The links to the referenced wrappers and MatLab code can be found at:
		http://www.mathworks.com/matlabcentral/fileexchange/6543-functions-for-the-rectangular-assignment-problem and
		https://github.com/mcximing/hungarian-algorithm-cpp
*/

#include <stdlib.h>
#include <cfloat> 
#include <cmath>
#include "Hungarian.h"

HungarianAlgorithm::HungarianAlgorithm(){}
HungarianAlgorithm::~HungarianAlgorithm(){}


/*		This is the driver function for solving a hungarian algorithom (cost matrix) problem. This function takes two inputs: a reference to a 
		2D vector cost matrix, and a reference to a vector to save the cordinates of the most optimal choice. This fucntion cretes an array of all 
		of the points stored into one large matrix. After creating the matrix, it calls the assignmentoptimal() function and returns
		the most optimal cost (distance) of the matrix.
*/
double HungarianAlgorithm::Solve(vector<vector<double>>& distanceVector, vector<int>& choices){
	unsigned int numRows = distanceVector.size();
	unsigned int numCols = distanceVector[0].size();

	double *initialDistanceMatrix = new double[numRows * numCols];
	int *optimalChoices = new int[numRows];
	double cost = 0.0;

	for(unsigned int i = 0; i < numRows; i++){
		for(unsigned int j = 0; j < numCols; j++){
			initialDistanceMatrix[i + numRows * j] = distanceVector[i][j];
		}
	}

	assignmentoptimal(optimalChoices, &cost, initialDistanceMatrix, numRows, numCols);

	choices.clear();
	for(unsigned int r = 0; r < numRows; r++){
		choices.push_back(optimalChoices[r]);
	}

	delete[] initialDistanceMatrix;
	delete[] optimalChoices;
	return cost;
}


/*		This fucntion takes 5 inputs and is the first step in the chain of fucntions. The inputs are a pointer to the vector of optimal choices we 
		initially passes to the class instance, a pointer to the total cost that we initiallized in Solve(), a pointer to the distance matrix we initally
		passed into Solve(), as well as the number of rows and cols in the distance matrix. It starts by creating a working copy of the given distance
		matrix since the origional is a pointer and would be motified if we didn't make a copy. It then allocates memory for needed variables later on.
		From there, it finds the smallest element in each row and subtracts it from each row leaving the smallest element being a 0. It then "covers" all
		columns that contain a 0, and moved on to step2b()
*/
void HungarianAlgorithm::assignmentoptimal(int *optimalChoices, double *cost, double *initialDistanceMatrix, int numRows, int numCols){
	double *distanceMatrix, *distanceMatrixTemp, *distanceMatrixEnd, value, minValue;
	bool *coveredColumns, *coveredRows, *starMatrix, *newStarMatrix, *primeMatrix;
	int numOfElements, minDim, row, col;

	*cost = 0;
	for(row = 0; row < numRows; row++){
		optimalChoices[row] = -1;
	}

	numOfElements = numRows * numCols;
	distanceMatrix = (double *)malloc(numOfElements * sizeof(double));
	distanceMatrixEnd = distanceMatrix + numOfElements;

	for(row = 0; row < numOfElements; row++){
		distanceMatrix[row] = initialDistanceMatrix[row];
	}

	coveredColumns = (bool *)calloc(numCols, sizeof(bool));
	coveredRows = (bool *)calloc(numRows, sizeof(bool));
	starMatrix = (bool *)calloc(numOfElements, sizeof(bool));
	primeMatrix = (bool *)calloc(numOfElements, sizeof(bool));
	newStarMatrix = (bool *)calloc(numOfElements, sizeof(bool)); /* used in step4 */

	minDim = numRows;

	for(row = 0; row < numRows; row++){
		distanceMatrixTemp = distanceMatrix + row;
		minValue = *distanceMatrixTemp;
		distanceMatrixTemp += numRows;
		while(distanceMatrixTemp < distanceMatrixEnd){
			value = *distanceMatrixTemp;
			if(value < minValue){
				minValue = value;
			}
			distanceMatrixTemp += numRows;
		}

		distanceMatrixTemp = distanceMatrix + row;
		while(distanceMatrixTemp < distanceMatrixEnd){
			*distanceMatrixTemp -= minValue;
			distanceMatrixTemp += numRows;
		}
	}

	for(row = 0; row < numRows; row++){
		for(col = 0; col < numCols; col++){
			if(fabs(distanceMatrix[row + numRows * col]) < DBL_EPSILON){
				if(!coveredColumns[col]){
					starMatrix[row + numRows*col] = true;
					coveredColumns[col] = true;
					break;
				}
			}
		}
	}

	step2b(optimalChoices, distanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, numRows, numCols, minDim);

	computeassignmentcost(optimalChoices, cost, initialDistanceMatrix, numRows);

	free(distanceMatrix);
	free(coveredColumns);
	free(coveredRows);
	free(starMatrix);
	free(primeMatrix);
	free(newStarMatrix);

	return;
}


/*		This funtion will set the values of the optimal choice vector origionally passes into the function to the found indexes of the best choices to 
		minimise movement distance of the pucks. It itterates through each row and column and sets the optimalChoice vecotr to the best values in each
		which are marked by a "true" in the star matrix from step4().
*/
void HungarianAlgorithm::buildassignmentvector(int *optimalChoices, bool *starMatrix, int numRows, int numCols){
	int row, col;

	for(row = 0; row < numRows; row++){
		for(col = 0; col < numCols; col++){
			if(starMatrix[row + numRows * col]){
				#ifdef ONE_INDEXING
					optimalChoices[row] = col + 1;
				#else
					optimalChoices[row] = col;
				#endif
					break;
			}
		}
	}
}


/*		This function itterates through the optimalChoices matrix and sums all of the distances in the distance vector to find the total minimmun distance
		that can be traveled by the pucks to move them to their best locations. This is the value that will be returned from the class instance to main.cpp
*/
void HungarianAlgorithm::computeassignmentcost(int *optimalChoices, double *cost, double *distanceMatrix, int numRows){
	int row, col;

	for(row = 0; row < numRows; row++){
		col = optimalChoices[row];
		if(col >= 0){
			*cost += distanceMatrix[row + numRows * col];
		}
	}
}


/*		This step will itterate through each column and cover (or draw a "line") over each column containing a 0. It will then save this line into the 
		coveredColumns[] matrix and jump back to step2b wich will repeat this process but for rows.
*/
void HungarianAlgorithm::step2a(int *optimalChoices, double *distanceMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int numRows, int numCols, int minDim){
	bool *starMatrixTemp, *columnEnd;
	int col;

	for(col = 0; col < numCols; col++){
		starMatrixTemp = starMatrix + numRows * col;
		columnEnd = starMatrixTemp + numRows;
		while(starMatrixTemp < columnEnd){
			if(*starMatrixTemp++){
				coveredColumns[col] = true;
				break;
			}
		}
	}

	step2b(optimalChoices, distanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, numRows, numCols, minDim);
}


/*		This function determines if our algoritm is complete. We know it is complete if the number of "lines" it takes to cover all of the 0's in our matrix
		is equal to the number of elements we need to select. In this case it is the number of Pucks in the given scenerio. It staets by counting the number
		of lines currently covering our matrix and sees if it is equal to the number of Pucks. if it is, the algorithm is done and it calls buildassignmentvector(), 
		if not it jumps to step3()
*/
void HungarianAlgorithm::step2b(int *optimalChoices, double *distanceMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int numRows, int numCols, int minDim){
	int col, nOfCoveredColumns;

	nOfCoveredColumns = 0;
	for(col = 0; col < numCols; col++){
		if(coveredColumns[col]){
			nOfCoveredColumns++;
		}
	}

	if(nOfCoveredColumns == minDim){
		buildassignmentvector(optimalChoices, starMatrix, numRows, numCols);
	} else {
		step3(optimalChoices, distanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, numRows, numCols, minDim);
	}

}


/*		This function will take in the distance matrix and search through each row and if any of the 0's in the row are not covered, it will cover them and edit
		the coveredRow matrix with the new line covering the row. This repeats until all of the 0's are coverd. Once all of the 0's are coverd, it will jump to step4().
*/
void HungarianAlgorithm::step3(int *optimalChoices, double *distanceMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int numRows, int numCols, int minDim){
	bool zerosFound;
	int row, col, starCol;

	zerosFound = true;
	while(zerosFound){
		zerosFound = false;

		for(col = 0; col < numCols; col++){
			if(!coveredColumns[col]){
				for(row = 0; row < numRows; row++){
					if((!coveredRows[row]) && (fabs(distanceMatrix[row + numRows * col]) < DBL_EPSILON)){
						primeMatrix[row + numRows * col] = true;

						for(starCol = 0; starCol < numCols; starCol++){
							if(starMatrix[row + numRows * starCol]){
								break;
							}
						}

						if(starCol == numCols){
							step4(optimalChoices, distanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, numRows, numCols, minDim, row, col);
							return;
						} else {
							coveredRows[row] = true;
							coveredColumns[starCol] = false;
							zerosFound = true;
							break;
						}
					}
				}
			}
		}
	}

	step5(optimalChoices, distanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, numRows, numCols, minDim);
}


/*		This fucntion locates the most optimal selection from each row and column. It first generates a working copy of the starMatrix witch will hold the locations
		of the most optimal choices to minimose distances. From there it takes the inital starMatrix and finds the most optimal row and column location and compares 
		it to another optimal row and column distance. If the new one that it found is less than the one in the previous starMatrix, it will save the new location to
		the primeMatrix. It then resets the covering lines and deletes all prime locations to repeat the steps leading up to this point by calling step2a()
*/
void HungarianAlgorithm::step4(int *optimalChoices, double *distanceMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int numRows, int numCols, int minDim, int row, int col){
	int n, starRow, starCol, primeRow, primeCol;
	int numOfElements = numRows * numCols;

	for(n = 0; n < numOfElements; n++){
		newStarMatrix[n] = starMatrix[n];
	}

	newStarMatrix[row + numRows * col] = true;

	starCol = col;
	for(starRow = 0; starRow < numRows; starRow++){
		if(starMatrix[starRow + numRows * starCol]){
			break;
		}
	}

	while (starRow < numRows){
		newStarMatrix[starRow + numRows * starCol] = false;

		primeRow = starRow;
		for(primeCol = 0; primeCol < numCols; primeCol++){
			if(primeMatrix[primeRow + numRows * primeCol]){
				break;
			}
		}

		newStarMatrix[primeRow + numRows * primeCol] = true;

		starCol = primeCol;
		for(starRow = 0; starRow < numRows; starRow++){
			if(starMatrix[starRow + numRows * starCol]){
				break;
			}
		}
	}

	for(n = 0; n < numOfElements; n++){
		primeMatrix[n] = false;
		starMatrix[n] = newStarMatrix[n];
	}

	for(n = 0; n < numRows; n++){
		coveredRows[n] = false;
	}

	step2a(optimalChoices, distanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, numRows, numCols, minDim);
}


/*		This function is called if the number of lines or covered rows and columns are less than the number of Pucks in the given situation. It will 
		find the smallest uncovered element, add it's value to each covered row, then subtract it from each uncovered column. This will create more 0's
		in optimal locations and thus more lines to cover rows and columns and we will get closer to solving for most optimal locations. It first iterates
		through the distance matrix and finds the smallest value, then itterates through rows and columns and either adds or subtracts the h value from them
		depending on if they are covered or not.
*/
void HungarianAlgorithm::step5(int *optimalChoices, double *distanceMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int numRows, int numCols, int minDim){
	double h, value;
	int row, col;

	h = DBL_MAX;
	for(row = 0; row < numRows; row++){
		if(!coveredRows[row]){
			for(col = 0; col < numCols; col++){
				if(!coveredColumns[col]){
					value = distanceMatrix[row + numRows*col];
					if(value < h){
						h = value;
					}
				}
			}
		}
	}

	for(row = 0; row < numRows; row++){
		if(coveredRows[row]){
			for(col = 0; col < numCols; col++){
				distanceMatrix[row + numRows * col] += h;
			}
		}
	}

	for(col = 0; col < numCols; col++){
		if(!coveredColumns[col]){
			for(row = 0; row < numRows; row++){
				distanceMatrix[row + numRows * col] -= h;
			}
		}
	}

	step3(optimalChoices, distanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, numRows, numCols, minDim);
}
