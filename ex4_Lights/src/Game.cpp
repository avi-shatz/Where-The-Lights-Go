#include <Game.h>

constexpr auto LEVELS = 3;
constexpr auto MIN_LEVEL_SIZE = 5;
constexpr auto ADD_LEVEL_SIZE = 2;  // Addition to the size of each 'level up'
const auto TEXT_COLOR = sf::Color(129, 13, 152);


Game::Game()
	: m_window(sf::VideoMode(WIN_WIDTH, WIN_LENGTH), "Lights Game", sf::Style::Close),
	m_playLevel(true)
{

}

void Game::run()
{
	while (m_window.isOpen())
	{
		for (size_t i = 0; i < LEVELS; i++)
		{
			m_board.create(MIN_LEVEL_SIZE + i * ADD_LEVEL_SIZE);
			m_playLevel = true;
			while (m_playLevel)
			{
				processEvents();
				update();
				render();
			}
			displayMsg("you finished level " + std::to_string(i+1) + " :) ");
		}

		displayMsg("congratulations!  :) you won!!");
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
	m_board.update();

	if (m_board.allConnected())
		m_playLevel = false;
}

// rendering everything to the screan.
void Game::render()
{
	m_window.clear();
	m_board.draw(m_window);
	m_window.display();
}

void Game::displayMsg(std::string s)
{
	auto window = sf::RenderWindow(sf::VideoMode(460, 300), "");

	auto font = sf::Font();
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	sf::Text text(s, font);
	text.setPosition({ 25, 50 });

	sf::Text continue_text("press enter to continue..", font);
	continue_text.setPosition({ 40, 250 });
	continue_text.scale({ float(0.7), float(0.7) });

	text.setFillColor(TEXT_COLOR);
	continue_text.setFillColor(TEXT_COLOR);

	while (window.isOpen())
	{
		//display ui 
		window.clear(sf::Color::White);
		window.draw(text);
		window.draw(continue_text);
		window.display();


		// getting user input from keyboard.
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Enter:
					window.close();
					break;
				}
			}
		}
	}
}
