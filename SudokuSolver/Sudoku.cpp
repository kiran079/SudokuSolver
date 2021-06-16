#include <iostream>
#include <string>
#include "Sudoku.h"

/**
 * Constructor
 */
Sudoku::Sudoku(sf::RenderWindow& window, float l): window(window), box_len(l), line_width(4.f), tl(60.f, 60.f), boxes(nullptr), clicked_box(-1, -1) {
	myfont.loadFromFile("Fonts/arial.ttf");
	initSolveButton();
	initBoxes();
}

/**
 * Destructor to delete boxes
 */
Sudoku::~Sudoku()
{
	for (unsigned int i = 0; i < 9; ++i) {
		delete[] boxes[i];
	}
	delete[] boxes;
}

/**
 * Initilize the solve button
 */
void Sudoku::initSolveButton()
{
	solve_button.setFont(myfont);
	solve_button.setCharacterSize(50);
	solve_button.setOutlineColor(sf::Color::Magenta);
	solve_button.setString("SOLVE");
	solve_button.setPosition(window.getSize().x /2.f, 0.f);
}

/**
 * Initialize the boxes in correct locations
 */
void Sudoku::initBoxes()
{
	boxes = new TextBox*[9];
	for (unsigned int i = 0; i < 9; i++) {
		boxes[i] = new TextBox[9];
		for (unsigned int j = 0; j < 9; j++) {
			sf::Text temp_text;
			temp_text.setFont(myfont);
			temp_text.setCharacterSize(40);
			temp_text.setOutlineColor(sf::Color(150, 150, 150));
			temp_text.setPosition(tl.x + (box_len * j) + (line_width * (j / 3)) + (j - (j / 3)) + (box_len / 2 - 10),
				tl.y + (box_len * i) + (line_width * (i / 3 + 1)) + (i - (i / 3)));
			boxes[i][j].text = temp_text;

			sf::RectangleShape bg(sf::Vector2f(box_len, box_len));
			bg.setPosition(tl.x + (box_len * j) + (line_width * (j / 3 + 1)) + (j - (j / 3)), tl.y + (box_len * i) + (line_width * (i / 3 + 1)) + (i - (i / 3)));
			bg.setFillColor(sf::Color::Blue);
			boxes[i][j].rect = bg;
		}
	}
}

/**
 * Extracts the digits from the board
 * 
 * @return 2d vector of integers filled with digit corresponding to the state of the board
 */
std::vector<std::vector<int>> Sudoku::getBoard(bool fixed)
{
	std::vector<std::vector<int>> board;
	for (unsigned int i = 0; i < 9; i++) {
		std::vector<int> temp;
		board.push_back(temp);
		for (unsigned int j = 0; j < 9; j++) {
			if ((boxes[i][j].fixed && fixed) || (!fixed && boxes[i][j].text.getString() != ""))
				board.at(i).push_back(std::stoi(std::string(boxes[i][j].text.getString())));
			else
				board.at(i).push_back(0);
		}
	}
	return board;
}

/**
 * Sets the board to the given 2d vector of integers
 */
void Sudoku::setBoard(std::vector<std::vector<int>> matrix)
{
	for (unsigned int i = 0; i < 9; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			if (matrix.at(i).at(j) != 0) {
				boxes[i][j].text.setString(std::to_string(matrix.at(i).at(j)));
				boxes[i][j].fixed = true;
				boxes[i][j].rect.setFillColor(sf::Color(0, 0, 139));
			}
		}
	}
}

/**
 * Sets the board to the given string of digits
 */
void Sudoku::setBoard(std::string str)
{
	std::vector<std::vector<int>> ans;
	for (unsigned int i = 0; i < 9; i++) {
		std::vector<int> temp;
		ans.push_back(temp);
		for (unsigned int j = 0; j < 9; j++) {
			int num = str.at(i * 9 + j) - '0';
			if ((num >= 0) && (num <= 9)) {
				ans.at(i).push_back(num);
			}
			else {
				ans.at(i).push_back(0);
			}
		}
	}
	setBoard(ans);
}

void Sudoku::freezeBoard()
{
	for (unsigned int i = 0; i < 9; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			if (boxes[i][j].text.getString() != "") {
				boxes[i][j].fixed = true;
				boxes[i][j].rect.setFillColor(sf::Color(0, 0, 139));
			}
		}
	}
}

/**
 * fills the current board with teh given 2d vector of integers
 * without changing the squares currently filled
 */
void Sudoku::fillBoard(std::vector<std::vector<int>> matrix)
{
	for (unsigned int i = 0; i < 9; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			if (matrix.at(i).at(j) != 0) {
				boxes[i][j].text.setString(std::to_string(matrix.at(i).at(j)));
			}
		}
	}
}

/**
 * Display the text and its background
 */
void Sudoku::displayText()
{
	for (unsigned int i = 0; i < 9; ++i) {
		for (unsigned int j = 0; j < 9; ++j) {
			window.draw(boxes[i][j].rect);
			window.draw(boxes[i][j].text);
		}
	}
}

/**
 * Display the solve button
 */
void Sudoku::displaySolveButton()
{
	window.draw(solve_button);
}

/**
 * Display the entire suduko board
 */
void Sudoku::display()
{
	int x = tl.x;
	int y = tl.y;
	float total_len = 9 * box_len + 4 * line_width + 6;
	float offset = 0;

	for (unsigned int i = 0; i <= 9; ++i) {
		if (i % 3 == 0) {
			sf::RectangleShape line1(sf::Vector2f(total_len, line_width));
			line1.setPosition(x, y + offset);
			sf::RectangleShape line2(sf::Vector2f(line_width, total_len));
			line2.setPosition(x + offset, y);
			window.draw(line1);
			window.draw(line2);
			offset += line_width;
		} else {
			sf::RectangleShape line1(sf::Vector2f(total_len, 1));
			line1.setPosition(x, y + offset);
			sf::RectangleShape line2(sf::Vector2f(1, total_len));
			line2.setPosition(x + offset, y);
			window.draw(line1);
			window.draw(line2);
			offset += 1;
		}
		offset += box_len;
	}
	displayText();
	displaySolveButton();
}

/**
 * Checks where the mouse is pressed and does the appropriate action
 * 
 * @param	x	the x coordinate of the location of mouse
 * @param	y	the y coordinate of the location of mouse
 */
void Sudoku::mousePressed(int x, int y)
{
	if (solve_button.getGlobalBounds().contains(x, y)) {
		freezeBoard();
		solve_button.setFillColor(sf::Color::Blue);
		solve();
	}
	bool clicked = false;
	for (unsigned int i = 0; i < 9; i++) {
		for (unsigned int j = 0; j < 9; j++) {
			if (!boxes[i][j].fixed) {
				if (boxes[i][j].rect.getGlobalBounds().contains(x, y)) {
					clicked = true;
					if (sf::Vector2i(i, j) == clicked_box) {
						clicked_box.x = -1;
						clicked_box.y = -1;
						boxes[i][j].rect.setFillColor(sf::Color::Blue);
					}
					else {
						clicked_box.x = i;
						clicked_box.y = j;
						boxes[i][j].rect.setFillColor(sf::Color::Cyan);
					}
				}
				else {
					boxes[i][j].rect.setFillColor(sf::Color::Blue);
				}
			}
		}
	}
	if (!clicked) {
		clicked_box.x = -1; clicked_box.y = -1;
	}

}

/**
 * Checks the keyboard input and does appropriate action
 * 
 * @param	code	the TextEvent of the key pressed event
 */
void Sudoku::keyPressed(sf::Event::TextEvent code)
{
	if (clicked_box.x != -1) {
		if (code.unicode == 59) {
			boxes[clicked_box.x][clicked_box.y].text.setString("");
		}
		else if (clicked_box.x != -1 && (code.unicode >= 27) && (code.unicode <= 35)) {
			boxes[clicked_box.x][clicked_box.y].text.setString(static_cast<char>(code.unicode + 22));
		}
	}

}

/**
 * Solves the current state of sudoku board and updates the board
 * if a solution exist.
 */
void Sudoku::solve()
{
	Solver solver(getBoard());
	solver.solve();
	if (solver.getSolution().size() > 0) {
		fillBoard(solver.getSolution().at(0));
		solve_button.setString("SOLVED!");
		solve_button.setFillColor(sf::Color::Green);
	}
	else {
		solve_button.setString("NO SOLUTION :(");
		solve_button.setFillColor(sf::Color::Red);
	}
}
