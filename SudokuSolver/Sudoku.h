#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "TextBox.h"
#include "Solver.h"

/**
 * Implementation of a sudoku board
 * 
 * Stores the board as a 2d dynamic array of TextBox and
 * track the mouse presses on the boxes
 */

class Sudoku
{
private:
	sf::RenderWindow& window;	// the window to display on
	float box_len;	// length of each box
	float line_width;	// width of each line
	sf::Vector2i tl;	// coordinate of top left of the sudoku
	sf::Font myfont;	// font of the digits
	sf::Text solve_button;	// solve button
	TextBox** boxes;	// 2d dynamic array of TextBox
	sf::Vector2i clicked_box;	// stores the location of the currently clicked box
public:
	Sudoku(sf::RenderWindow& window, float l = 50.f);
	~Sudoku();
	void initSolveButton();
	void initBoxes();
	std::vector<std::vector<int>> getBoard(bool fixed = false);
	void setBoard(std::vector<std::vector<int>>);
	void setBoard(std::string str);
	void freezeBoard();
	void fillBoard(std::vector<std::vector<int>>);

	void displayText();
	void displaySolveButton();
	void display();
	void mousePressed(int x, int y);
	void keyPressed(sf::Event::TextEvent code);
	void solve();
};

#endif
