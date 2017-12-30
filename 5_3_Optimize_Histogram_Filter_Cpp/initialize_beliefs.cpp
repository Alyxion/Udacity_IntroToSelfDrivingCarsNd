#include "headers/initialize_beliefs.h"

using namespace std;

// OPTIMIZATION: pass large variables by reference
void initialize_beliefs(const vector< vector <char> > &grid, vector< vector <float> > &outGrid) {

	// OPTIMIZATION: Which of these variables are necessary?
	// OPTIMIZATION: Reserve space in memory for vectors
	float prob_per_cell;

	const int height = grid.size(),
	width = grid[0].size(),
  	area = width*height;

	outGrid.clear();
  	outGrid.reserve(height);
	
  	prob_per_cell = 1.f / ( (float) area) ;
 	vector<float> newRow(width, prob_per_cell);
  
  	// OPTIMIZATION: Is there a way to get the same results 	// without nested for loops?
	for (int i=0; i<height; ++i) {
		outGrid.push_back(newRow);
	}
}

// Not necessary to pass in the grid variable since it is never used
// Could either pass by reference or just pass in the height and width
vector< vector <float> > initialize_beliefs_improved(int height, int width) {

	// not necessary to calculate the area variable first since it is only used once
	float prob_per_cell = 1.0 / float(height * width);

	vector<float> row;
	vector< vector<float> > newGrid;

	// because the vectors are not of variable length, 
	// it is faster to reserve space in memory for the vectors
	row.reserve(width);
	newGrid.reserve(height);

	// avoiding nested for loops since in this case it is not needed
	// each element in the 2D vector has the exact same value
	for (int i = 0; i < width; i++) {
		row.push_back(prob_per_cell);
	}

	for (int i = 0; i < height; i++) {
		newGrid.push_back(row);
	}

	return newGrid;
}
