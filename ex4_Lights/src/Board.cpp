#include "Board.h"
#include <math.h>       /* sqrt */

Board::Board()
{
}

void Board::create(int size)
{
	createPoints(size);
	createNbList();
	m_points[0][0]->connect(m_points[1][1].get());
}

void Board::draw(sf::RenderWindow& window) const
{
	for (const auto& vec : m_points)
		for (const auto& p : vec)
		{
			p->draw(window);
		}
}

void Board::click(sf::Vector2f location)
{
	for (auto& vec : m_points)
		for (auto& p : vec)
		{
			p->click(location);
		}
}

void Board::createPoints(const int size)
{
	auto mdlS = sf::Vector2f{WIN_WIDTH, WIN_LENGTH}/2.f; // midlle screen location.
	float lineSp = float(sqrt(3)/2) * SPACE;// space between lines.
	auto location = mdlS - sf::Vector2f{((size-1) / 2.f)* SPACE, 0};//location of the starting point for each line.
	auto oppositeLine = location; // location of the opposite line

	m_points.push_back(createLine(location, size)); // create middle line.

	for (int i = size-1; i >= MIN_LINE_SIZE ; i--)
	{
		location += sf::Vector2f{ (float)SPACE / 2, lineSp };
		oppositeLine += sf::Vector2f{ (float)SPACE / 2, -lineSp };

		m_points.push_back(createLine(location , i)); // add one line under the middle.
		m_points.insert(m_points.cbegin(), createLine(oppositeLine, i)); // add one line above the middle.
	}                               
}

//creating a line of @param(size) points, starting at @param(location).
PointsVec Board::createLine(sf::Vector2f location, int size)
{
	PointsVec vec;
	for (int i = 0; i < size; i++)
	{
		vec.emplace_back( std::make_unique<Point>(location + sf::Vector2f{ (float)i * SPACE, 0 }));
	}
	return std::move(vec);
}

void Board::createNbList()
{

	for (int i = 0; i < m_points.size(); i++)
	{
		auto& pVec = m_points[i];
		for (int j = 0; j < pVec.size(); j++)
		{
			auto& p = pVec[j];
			p->setNeighbor(0, getPByIndex(i, j+1));
			p->setNeighbor(1, getPByIndex(i, j-1));
			p->setNeighbor(2, getPByIndex(i+1, j));
			p->setNeighbor(3, getPByIndex(i-1, j));

			int a = i+1, b = j-1;
			if (i < int(m_points.size() / 2) + 1) // if point is in the upper half of the board.
				b = j + 1;
			p->setNeighbor(4, getPByIndex(a, b));


			a = i-1, b = j-1;
			if (i > int(m_points.size() / 2) + int(1)) // if point is in the lower half of the board.
				b = j + 1;
			p->setNeighbor(5, getPByIndex(a, b));
		}

	}
}

Point* Board::getPByIndex(int i, int j)
{
	if (i<0 || i >= m_points.size() || j<0 || j >= m_points[i].size())
		return nullptr;

	return m_points[i][j].get();
}
