#include "headers/sense.h"

using namespace std;

// OPTIMIZATION: Pass larger variables by reference
void sense(const char color, const vector< vector <char> > &grid, vector< vector <float> > &beliefs,  const float p_hit, const float p_miss) 
{
	const int height = grid.size(),
	width = grid[0].size();

	for (int i=0; i<height; ++i) 
    {
      	vector<float> &beliefRow = beliefs[i];
      	const vector<char> &gridRow = grid[i];
		for (int j=0; j<width; ++j) 
        {
          	beliefRow[j] *= gridRow[j] == color ? p_hit : p_miss;
		}
	}
}

// passing grid and belief by reference
vector< vector <float> > sense_improved(char color, 
	vector< vector <char> > &grid, 
	vector< vector <float> > &beliefs, 
	float p_hit,
	float p_miss) 
{

	int height, width;

	height = grid.size();
	width = grid[0].size();

	for (int i=0; i < height; ++i) {
		for (int j=0; j < width; ++j) {
			// remove the cell variable since not needed
			if (grid[i][j] == color) {
				// update the belief vector instead of creating new variable
				beliefs[i][j] = beliefs[i][j] * p_hit;
			}
			// remove the extra if statement since not needed
			else {
				// update the belief vector instead of creating new variable
				beliefs[i][j] = beliefs[i][j] * p_miss;
			}
		}
	}
	return beliefs;
}
