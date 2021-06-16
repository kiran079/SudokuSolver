#include "Solver.h"

/**
 * Constructor to initialize the board
 */
Solver::Solver(std::vector<std::vector<int>> temp)
{
	for (unsigned int i = 0; i < 9; i++) {
		board.push_back(std::vector<int>());
		for (unsigned int j = 0; j < 9; j++) {
			board.at(i).push_back(temp.at(i).at(j));
		}
	}
}

/**
 * Checks if the given digit can be placed in the given square
 * 
 * @param	num		The digit to be placed in a square
 * @param	x		The row of the square
 * @param	y		The column of the square
 * 
 * @return	Bool indicating if the number can be placed in the given square
 */
bool Solver::isPossible(int num, int x, int y)
{
	for (unsigned int i = 0; i < 9; i++) {
		if ((board.at(x).at(i) == num) || (board.at(i).at(y) == num))
			return false;
	}
	int x0 = (x / 3) * 3;
	int y0 = (y / 3) * 3;
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			if (board.at(x0 + i).at(y0 + j) == num)
				return false;
		}
	}
	return true;
}

/**
 * Solves the sudoku board using backtracking
 * 
 * @param	status		Indicates if a solution has been found
 * 
 * @return	Bool indicating if a solution has been found
 */
bool Solver::solve(bool status)
{
	for (unsigned int i = 0; i < 9; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			if (board.at(i).at(j) == 0) {
				for (unsigned int n = 1; n < 10; n++) {
					if (isPossible(n, i, j)) {
						board.at(i).at(j) = n;
						if (solve())
							return true;
						board.at(i).at(j) = 0;
					}
				}
				return false;
			}
		}
	}
	solution.push_back(board);
	return true;
}

/**
 * Access to the solution
 * 
 * @return the slution data member
 */
std::vector<std::vector<std::vector<int>>> Solver::getSolution()
{
	return solution;
}
