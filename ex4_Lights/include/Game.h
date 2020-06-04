#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Game : private sf::NonCopyable
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

private:

	sf::RenderWindow m_window;
	Board m_board;
};

