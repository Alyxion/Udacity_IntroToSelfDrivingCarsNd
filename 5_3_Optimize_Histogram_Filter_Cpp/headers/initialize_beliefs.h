#ifndef INITIALIZE_BELIEFS_H
#define INITIALIZE_BELIEFS_H

#include <vector>

void initialize_beliefs(const std::vector< std::vector <char> > &grid, std::vector< std::vector <float> > &outGrid);
std::vector< std::vector <float> > initialize_beliefs_improved(int height, int width);

#endif /* INITIALIZE_BELIEFS.H */
