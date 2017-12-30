#include "headers/move.h"
#include "headers/zeros.h"

using namespace std;

// OPTIMIZATION: Pass large variable by reference
void move(int dy, int dx, 
	vector < vector <float> > &beliefs, vector < vector <float> > &outGrid) 
{
	int height = beliefs.size(),
	width = beliefs[0].size();

	int i, j, new_i, new_j;

	for (int i=0; i<height; ++i) 
    {
		for (int j=0; j<width; ++j) 
      	{
			new_i = (i + dy + height) % height;
			new_j = (j + dx + width)  % width;
			outGrid[new_i][new_j] = beliefs[i][j];
		}
	}
}

vector< vector <float> > move_improved(int dy, int dx, vector < vector <float> > &beliefs) 
{
	int height, width;
	height = beliefs.size();
	width = beliefs[0].size();

	vector < vector <float> >  newGrid = zeros_improved(height, width);

	int i, j, new_i, new_j;

	for (i=0; i<height; ++i) {
		for (j=0; j<width; ++j) {
			new_i = (i + dy + height) % height;
			new_j = (j + dx + width)  % width;
			newGrid[new_i][new_j] = beliefs[i][j];
		}
	}
	return newGrid;
}
