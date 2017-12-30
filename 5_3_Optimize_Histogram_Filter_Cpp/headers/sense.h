#ifndef SENSE_H
#define SENSE_H

#include <vector>
#include <iostream>

void sense(const char color, const std::vector< std::vector <char> > &grid, std::vector< std::vector <float> > &beliefs,  const float p_hit, const float p_miss);
std::vector< std::vector <float> > sense_improved(char color, 
	std::vector< std::vector <char> > &grid, 
	std::vector< std::vector <float> > &beliefs, 
	float p_hit,
	float p_miss);

#endif /* SENSE.H */