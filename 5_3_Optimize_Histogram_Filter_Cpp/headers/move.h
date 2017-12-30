#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <iostream>

void move(int dy, int dx, std::vector < std::vector <float> > &beliefs, std::vector < std::vector <float> > &outGrid);

std::vector< std::vector <float> > move_improved(int dy, int dx, std::vector < std::vector <float> > &beliefs); 


#endif /* MOVE.H */
