/**
	debugging_helpers.cpp
	
	Purpose: helper functions for debugging when working
	with grids of floats and chars.
*/

#include <vector>
#include <iostream>
using namespace std;

/**
    Displays a grid of beliefs. Does not return.

    @param grid - a two dimensional grid (vector of 
    	   vectors of floats) which will usually 
    	   represent a robot's beliefs.
*/
void show_grid(vector < vector <float> > grid) {
	float p;
	vector<float> row;
	for (size_t i = 0; i < grid.size(); i++)
	{
		row = grid[i];
		for (size_t j=0; j< row.size(); j++)
		{
			p = row[j];	
			cout << p << ' ';
		}
		cout << endl;
	}
}

/**
    Displays a grid map of the world
*/
void show_grid(vector < vector <char> > map) {
	char p;
	vector<char> row;
	for (size_t i = 0; i < map.size(); i++)
	{
		row = map[i];
		for (size_t j=0; j< row.size(); j++)
		{
			p = row[j];	
			cout << p << ' ';
		}
		cout << endl;
	}
}

