#ifndef BLUR_H
#define BLUR_H

#include <vector>

void blur(const std::vector < std::vector < float> > &grid, const float blurring, std::vector < std::vector <float> > &outGrid);
std::vector < std::vector <float> > blur_improved(std::vector < std::vector < float> > &grid);

#endif /* BLUR.H */