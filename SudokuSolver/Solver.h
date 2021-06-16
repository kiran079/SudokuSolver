#ifndef SOLVER_H
#define SOLVER_H
#include <vector>

/**
 * Implementation of a sudoku solver
 * 
 * Uses a backtracking algorithm to find one solution.
*/
class Solver
{
private:
	std::vector<std::vector<int>> board; // stores the state of sudoku board
	std::vector<std::vector<std::vector<int>>> solution; // stores the solution state
public:
	Solver(std::vector<std::vector<int>> temp);
	bool isPossible(int num, int x, int y);
	bool solve(bool status = false);
	std::vector<std::vector<std::vector<int>>> getSolution();
};

#endif
