/**
	localizer.cpp

	Purpose: implements a 2-dimensional histogram filter
	for a robot living on a colored cyclical grid by 
	correctly implementing the "initialize_beliefs", 
	"sense", and "move" functions.

	This file is incomplete! Your job is to make these
	functions work. Feel free to look at localizer.py 
	for working implementations which are written in python.
*/

#include "helpers.cpp"
#include <stdlib.h>
#include "debugging_helpers.cpp"

using namespace std;

/**
    Initializes a grid of beliefs to a uniform distribution.

    @param grid - a two dimensional grid map (vector of vectors 
    	   of chars) representing the robot's world. For example:
    	   
    	   g g g
    	   g r g
    	   g g g
		   
		   would be a 3x3 world where every cell is green except 
		   for the center, which is red.

    @return - a normalized two dimensional grid of floats. For 
           a 2x2 grid, for example, this would be:

           0.25 0.25
           0.25 0.25
*/
vector<vector<float> > initialize_beliefs(vector<vector<char> > grid)
{
	vector<vector<float> > newGrid;

    const size_t rowCount = grid.size(),
		colCount = grid[0].size();

	if (rowCount == 0 || colCount == 0)
	{
		throw std::invalid_argument("Passed matrix data is zero sized");
	}
    
    const float probability = 1.f/(rowCount*colCount);
    
    vector<float> newRow;
    
	for(size_t i=0; i<rowCount; ++i)
    {
        for(size_t j=0; j<colCount; ++j)
        {
            newRow.push_back(probability);
        }
        
        newGrid.push_back(newRow);
        newRow.clear();
    }
        
	return newGrid;
}

/**
    Implements robot sensing by updating beliefs based on the
    color of a sensor measurement 

	@param color - the color the robot has sensed at its location

	@param grid - the current map of the world, stored as a grid
		   (vector of vectors of chars) where each char represents a 
		   color. For example:

		   g g g
    	   g r g
    	   g g g

   	@param beliefs - a two dimensional grid of floats representing
   		   the robot's beliefs for each cell before sensing. For 
   		   example, a robot which has almost certainly localized 
   		   itself in a 2D world might have the following beliefs:

   		   0.01 0.98
   		   0.00 0.01

    @param p_hit - the RELATIVE probability that any "sense" is 
    	   correct. The ratio of p_hit / p_miss indicates how many
    	   times MORE likely it is to have a correct "sense" than
    	   an incorrect one.

   	@param p_miss - the RELATIVE probability that any "sense" is 
    	   incorrect. The ratio of p_hit / p_miss indicates how many
    	   times MORE likely it is to have a correct "sense" than
    	   an incorrect one.

    @return - a normalized two dimensional grid of floats 
    	   representing the updated beliefs for the robot. 
*/
vector<vector<float> > sense(char color, 
	vector<vector<char> > grid, 
	vector<vector<float> > beliefs, 
	float p_hit,
	float p_miss) 
{
	vector<vector<float> > newGrid;

    const size_t rowCount = beliefs.size(),
		colCount = beliefs[0].size();
    
	if (rowCount == 0 || colCount == 0)
	{
		throw std::invalid_argument("Passed matrix data is zero sized");
	}
	
	vector<float> newRow;
    
    for(size_t i=0; i<rowCount; ++i)
    {
        const vector<char> &gridRow = grid[i];
		const vector<float> &beliefRow = beliefs[i];

		if (beliefRow.size() != colCount)
		{
			throw std::invalid_argument("Belief row size mismatches first row size");
		}
		if (gridRow.size() != colCount)
		{
			throw std::invalid_argument("Grid row size mismatches first row size");
		}

        for(size_t j=0; j<colCount; ++j)
        {
            const float match = gridRow[j]==color ? 1.f : 0.f;
            const float newVal = (match*p_hit+p_miss*(1.f-match))*beliefRow[j];
            newRow.push_back(newVal);
        }
            
        newGrid.push_back(newRow);
        newRow.clear();
    }
            
    return normalize(newGrid);
}


/**
    Implements robot motion by updating beliefs based on the
    intended dx and dy of the robot. 

    For example, if a localized robot with the following beliefs

    0.00  0.00  0.00
    0.00  1.00  0.00
    0.00  0.00  0.00 

    and dx and dy are both 1 and blurring is 0 (noiseless motion),
    than after calling this function the returned beliefs would be

    0.00  0.00  0.00
    0.00  0.00  0.00
    0.00  0.00  1.00 

	@param dy - the intended change in y position of the robot

	@param dx - the intended change in x position of the robot

   	@param beliefs - a two dimensional grid of floats representing
   		   the robot's beliefs for each cell before sensing. For 
   		   example, a robot which has almost certainly localized 
   		   itself in a 2D world might have the following beliefs:

   		   0.01 0.98
   		   0.00 0.01

    @param blurring - A number representing how noisy robot motion
           is. If blurring = 0.0 then motion is noiseless.

    @return - a normalized two dimensional grid of floats 
    	   representing the updated beliefs for the robot. 
*/
vector<vector<float> > move(int dy, int dx, 
	vector<vector<float> > beliefs,
	float blurring) 
{
    const size_t rowCount = beliefs.size(),
		colCount = beliefs[0].size();

	if (rowCount == 0 || colCount == 0)
	{
		throw std::invalid_argument("Passed matrix data is zero sized");
	}
    
    vector<vector<float> > newGrid(rowCount, vector<float>(colCount, 0.f));

    for(size_t i=0; i<rowCount; ++i)
    {
        for(size_t j=0; j<colCount; ++j)
        {
            const size_t new_i = ((i + dy ) + rowCount) % rowCount,
				new_j = ((j + dx ) + colCount) % colCount;
            newGrid[int(new_i)][int(new_j)] = beliefs[i][j];
        }
    }
            
	return blur(newGrid, blurring);
}
