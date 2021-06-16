#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
/**
 * Stores the text and background rectangle for each box of in a sudoku.
 * The text should be a single digit number.
 */
struct TextBox {
	sf::Text text;
	sf::RectangleShape rect;
	/// indicates if this square is an input or can be changed when finding a solution
	bool fixed = false; 
};

#endif
