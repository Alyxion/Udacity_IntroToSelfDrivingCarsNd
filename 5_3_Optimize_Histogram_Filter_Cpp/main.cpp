#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>

#include "headers/initialize_beliefs.h"
#include "headers/sense.h"
#include "headers/blur.h"
#include "headers/normalize.h"
#include "headers/move.h"
#include "headers/print.h"

using namespace std;

int main() {

	// number of iterations 
	int iterations = 10000;

	std::clock_t start;
	double duration;

	vector < vector <char> > grid { {'r', 'g', 'r', 'r', 'r'}, {'g', 'r', 'r', 'g', 'r'}, {'r', 'g', 'r', 'r', 'r'} };
	vector< vector <float> > beliefs;

  	int height = grid.size();
	int width = grid[0].size();

	cout << "number of iterations: " << iterations << " " << "\n";

	// test initialize_beliefs
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
		initialize_beliefs(grid, beliefs);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Alyxion current   - duration milliseconds initialize beliefs " << 1000 * duration << '\n';

  	// test initialize_beliefs
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
		beliefs = initialize_beliefs_improved(height, width);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Udacity reference - duration milliseconds initialize beliefs " << 1000 * duration << '\n';

	// test sense
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
		sense('g', grid, beliefs, .7, .2);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Alyxion current   - duration milliseconds sense " << 1000 * duration << '\n';

	// test sense
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
		beliefs = sense_improved('g', grid, beliefs, .7, .2);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Udacity reference - duration milliseconds sense " << 1000 * duration << '\n';

	// test blur
	start = std::clock();
	for (int i = 0; i < iterations; i++) 
    {
      	auto original = beliefs;
		blur(original, .12, beliefs);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Alyxion current   - duration milliseconds blur " << 1000 * duration << '\n';

	// test blur
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
		beliefs = blur_improved(beliefs);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Udacity reference - duration milliseconds blur " << 1000 * duration << '\n';

	// test normalize
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
		normalize(beliefs);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Alyxion current   - duration milliseconds normalize " << 1000 * duration << '\n';

	// test normalize
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
		beliefs = normalize_improved(beliefs);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Udacity reference - duration milliseconds normalize " << 1000 * duration << '\n';

  // test move
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
      	auto org = beliefs;
		move(3, 2, org, beliefs);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Alyxion current   - duration milliseconds move " << 1000 * duration << '\n';

	// test move
	start = std::clock();
	for (int i = 0; i < iterations; i++) {
		beliefs = move_improved(3, 2, beliefs);
	}
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "Udacity reference - duration milliseconds move " << 1000 * duration << '\n';
  
  	std::cout << std::endl << "Executing unit tests, verifying results"<< std::endl;
  
  	initialize_beliefs(grid, beliefs);
  	auto compBeliefs = initialize_beliefs_improved(height, width);  
    if(beliefs==compBeliefs) { std::cout << "- Beliefs: Match" << std::endl; } else { std::cout << "- Beliefs: Fail" << std::endl; }
  
  	sense('g', grid, beliefs, .7, .2);
  	compBeliefs = sense_improved('g', grid, compBeliefs, .7, .2);
    if(beliefs==compBeliefs) { std::cout << "- Sense: Match" << std::endl; } else { std::cout << "- Sense: Fail" << std::endl; }

 	std::vector< std::vector<float> > original = beliefs;
	blur(original, .12, beliefs);
  	compBeliefs = blur_improved(compBeliefs);
  
	if(beliefs==compBeliefs) { std::cout << "- Blur: Match" << std::endl; } else { std::cout << "- Blur: Fail" << std::endl; }

	normalize(beliefs);

	compBeliefs = normalize_improved(compBeliefs);

	if(beliefs==compBeliefs) { std::cout << "- Normalize: Match" << std::endl; } else { std::cout << "- Normalize: Fail" << std::endl; }

  auto org = beliefs;
  move(3, 2, org, beliefs);
  
  		compBeliefs = move_improved(3, 2, compBeliefs);

	if(beliefs==compBeliefs) { std::cout << "- Move: Match" << std::endl; } else { std::cout << "- Move: Fail" << std::endl; }
}