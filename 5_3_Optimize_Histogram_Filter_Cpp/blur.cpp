#include "headers/blur.h"
#include "headers/zeros.h"

using namespace std;

// OPTIMIZATION: Pass large variable by reference
void blur(const vector < vector < float> > &grid, const float blurring, vector < vector <float> > &outGrid) {

	// OPTIMIZATION: window, DX and  DY variables have the 
    // same value each time the function is run.
  	// It's very inefficient to recalculate the vectors
    // every time the function runs. 
    // 
    // The const and/or static operator could be useful.
  	// Define and declare window, DX, and DY using the
    // bracket syntax: vector<int> foo = {1, 2, 3, 4} 
    // instead of calculating these vectors with for loops 
    // and push back
  	
	const int height = grid.size(),
	width = grid[0].size();
  
	for (int i=0; i<height; ++i) 
    {
      	vector<float> &gridRow = outGrid[i];
		for (int j=0; j<width; ++j ) 
        {
          gridRow[j] = 0.f;
        }
    }

	static float center = 1.f - blurring,
	corner = blurring / 12.f,
	adjacent = blurring / 6.f;
  
  	const float window[3][3] = { {corner, adjacent, corner}, {adjacent, center, adjacent}, {corner, adjacent, corner} };

	for (int i=0; i< height; i++ ) 
    {
      	const vector<float> &gridRow = grid[i];
      	const int iplusHeight = i+height;
      
		for (int j=0; j<width; j++ ) 
        {
			const float newVal = gridRow[j];
          	const int jplusWidth = j+width;
          
			for (int ii=-1; ii<=1; ++ii) 
            {
				const int new_i = (iplusHeight + ii) % height;
              	const float *windowRow = window[ii+1];
                vector<float> &newGridRow = outGrid[new_i];
              
				for (int jj=-1; jj<=1; ++jj) 
                {
					const int new_j = (jplusWidth + jj) % width;
					newGridRow[new_j] += newVal * windowRow[jj+1];
				}
			}
		}
	}
}

vector < vector <float> > blur_improved(vector < vector < float> > &grid) {

	static const float GLOBAL_BLURRING = 0.12;

	static const float CENTER = 1.0 - GLOBAL_BLURRING;
	static const float CORNER = GLOBAL_BLURRING / 12.0;
	static const float ADJACENT = GLOBAL_BLURRING / 6.0;

	static const vector <int> DX = {-1, 0, 1};
	static const vector <int> DY = {-1, 0, 1};

	static const vector < vector <float> > GLOBAL_WINDOW = { {CORNER, ADJACENT, CORNER}, {ADJACENT, CENTER, ADJACENT}, {CORNER, ADJACENT, CORNER} };


	vector < vector <float> > window;
	vector < vector <float> > newGrid;
	vector <float> row;
	vector <float> newRow;

	int height = grid.size();
	int width = grid[0].size();

	int i, j, ii, jj, new_i, new_j;
	int dx, dy;

	float multiplier;
	float newVal;

	// initialize new grid to zeros
	newGrid = zeros_improved(height, width);

	// original way
	for (i=0; i< height; i++ ) {
		for (j=0; j<width; j++ ) {
			newVal = grid[i][j];
			for (ii=0; ii<3; ii++) {
				dy = DY[ii];
				for (jj=0; jj<3; jj++) {
					dx = DX[jj];
					new_i = (i + dy + height) % height;
					new_j = (j + dx + width) % width;
					multiplier = GLOBAL_WINDOW[ii][jj];
					newGrid[new_i][new_j] += newVal * multiplier;
				}
			}
		}
	}

	return newGrid;
}