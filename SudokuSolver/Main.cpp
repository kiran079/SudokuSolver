#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
#ifdef _DEBUG
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF;  // Check heap alloc and dump mem leaks at exit
	_CrtSetDbgFlag(tmpFlag);
	//assert(!errno);
	//_crtBreakAlloc = 101;
#endif

	sf::RenderWindow window(sf::VideoMode(600, 600), "Not Tetris", sf::Style::Close | sf::Style::Titlebar);
	Game game(window);

	while (game.isRunning()) {
		game.update();
		game.render();
	}

	return 0;
}