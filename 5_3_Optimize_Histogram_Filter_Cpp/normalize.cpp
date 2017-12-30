#include "headers/normalize.h"
using namespace std;

// OPTIMIZATION: Pass variable by reference
void normalize(vector< vector <float> > &grid) 
{
	float total = 0.0;
    const int height = grid.size(),
    width = grid[0].size();
  
	for (int i = 0; i < height; ++i)
	{
		const vector<float> &row = grid[i];
		for (int j=0; j<width; ++j)
		{
			total += row[j];
		}
	}

//  	float scale = total!=0.f ? 1.f/total : 1.f;
  
 	for (int i = 0; i < height; ++i)
	{
		vector<float> &row = grid[i];
		for (int j=0; j< width; ++j)
		{
			row[j] /= total;
		}
	} 

}

// pass grid variable by reference
vector< vector<float> > normalize_improved(vector< vector <float> > &grid) {

	float total = 0.0;
	int rows = grid.size();
	int cols = grid[0].size();
	int i, j;

	// calculate total probability
	for (i = 0; i < rows; ++i)
	{
		for (j = 0; j< cols; ++j)
		{
			total += grid[i][j];
		}
	}

	for (i = 0; i < rows; ++i) {
		for (j=0; j< cols; ++j) {
			grid[i][j] = grid[i][j] / total;
		}
	}

	return grid;
}
