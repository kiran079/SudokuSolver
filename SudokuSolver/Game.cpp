#include <iostream>
#include "Game.h"

/**
 * Constructor
 */
Game::Game(sf::RenderWindow& window): window(window), sudoku(window) {
	window.setKeyRepeatEnabled(false);
}

/**
 * Checks for events and updates the state
 * 
 * Calls appropriate function
 */
void Game::updateEvents() {
	while (window.pollEvent(ev)) {
		switch (ev.type) {
		case (sf::Event::Closed):
			window.close();
			break;
		case (sf::Event::KeyPressed):
			switch (ev.key.code) {
			case(sf::Keyboard::Escape):
				window.close();
				break;
			default:
				sudoku.keyPressed(ev.text);
			}
			break;
		case (sf::Event::MouseButtonPressed):
			switch (ev.mouseButton.button) {
			case(sf::Mouse::Left):
				sudoku.mousePressed(ev.mouseButton.x, ev.mouseButton.y);
				break;
			}
			break;
		}
	}
}

/**
 * Updates the window
 */
void Game::update() {
	updateEvents();
}

/**
 * Display objects on the window
 */
void Game::render() {
	window.clear();
	sudoku.display();
	window.display();
}

/**
 * Indicates if the game is running
 * 
 * @return Bool indicating if the window is open or closed
 */
const bool Game::isRunning() const {
	return this->window.isOpen();
}
