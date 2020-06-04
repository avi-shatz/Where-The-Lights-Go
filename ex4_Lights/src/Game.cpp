#include <Game.h>


Game::Game()
	: m_window(sf::VideoMode(WIN_WIDTH, WIN_LENGTH), "Lights Game", sf::Style::Close)
{
	
}

void Game::run()
{
	m_board.create(5);
	while (m_window.isOpen())
	{
			processEvents();
			update();
			render();
	}
}

void Game::processEvents()
{
	if (auto event = sf::Event{}; m_window.waitEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::MouseButtonPressed:
			const auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Button::Left:
				m_board.click(location);
				break;
			}
		}
	}
}

//update game logic resulted from player's actions.
void Game::update()
{
	
}

// rendering everything to the screan.
void Game::render()
{
	m_window.clear();
	m_board.draw(m_window);
	m_window.display();
}
