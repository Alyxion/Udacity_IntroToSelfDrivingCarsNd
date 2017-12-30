#include "headers/zeros.h"

using namespace std;

vector < vector <float> > zeros(int height, int width) {
	// OPTIMIZATION: Reserve space in memory for vectors
	vector < vector <float> > newGrid;
	vector <float> newRow = vector<float>(width, 0.f);

  	newGrid.reserve(height);

  	// OPTIMIZATION: nested for loop not needed
    // because every row in the matrix is exactly the same
	for (int i=0; i<height; i++) 
    {
		newGrid.push_back(newRow);
	}
	return newGrid;
}

vector < vector <float> > zeros_improved(int height, int width) {
	int i;
	vector < vector <float> > newGrid;
	newGrid.reserve(height);

	vector <float> newRow;
	newRow.assign(width, 0);

	for (i=0; i<height; i++) {
		newGrid.push_back(newRow);
	}

	return newGrid;
}