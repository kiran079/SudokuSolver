#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Sudoku.h"

/**
 * Implementation of game with update and render
 */
class Game
{
private:
	sf::RenderWindow& window;	// window to display on
	sf::Event ev;	// event tracker
	Sudoku sudoku;	// sudoku board
public:
	Game(sf::RenderWindow& window);

	void updateEvents();
	void update();
	void render();
	const bool isRunning() const;
};


#endif