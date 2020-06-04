#include "Board.h"
#include <math.h>       /* sqrt */

Board::Board()
{
}

void Board::create(int size)
{
	m_points.clear();
	createPoints(size);
	createNbList();
	createEdges();
	randomRotation();
}

void Board::draw(sf::RenderWindow& window) const
{
	for (const auto& vec : m_points)
		for (const auto& p : vec)
		{
			p->draw(window);
		}
}

void Board::click(sf::Vector2f location, bool clockWise)
{
	for (auto& vec : m_points)
		for (auto& p : vec)
		{
			p->click(location, clockWise);
		}
}


// turn on the points that connected to the middle.
void Board::update()
{
	std::queue<Point*> q = enqueueMiddlePoint();

	// turn off all points
	for (int i = 0; i < m_points.size(); i++)
		for (int j = 0; j < m_points[i].size(); j++)
			m_points[i][j]->turnOff();

	// turn on the connected points with bfs
	while (!q.empty())
	{
		auto point = q.front();
		point->turnOn();
		auto nb = point->getOffNeighbors();

		for (auto& neighbor : nb)
			if (point->isConnected(neighbor))
			{
				q.push(neighbor);
				neighbor->turnOn();
			}

		q.pop();
	}
}

// returns true if al the points are connected
bool Board::allConnected()
{
	for (int i = 0; i < m_points.size(); i++)
	{
		for (int j = 0; j < m_points[i].size(); j++)
		{
			if(!m_points[i][j]->isOn())
				return false;
		}
	}
	return true;
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

//set neighbor list for every point
void Board::createNbList()
{

	for (int i = 0; i < m_points.size(); i++)
	{
		auto& pVec = m_points[i];
		for (int j = 0; j < pVec.size(); j++)
		{
			auto& p = pVec[j];
			p->addNeighbor(getPByIndex(i, j+1));
			p->addNeighbor(getPByIndex(i, j-1));
			p->addNeighbor(getPByIndex(i+1, j));
			p->addNeighbor(getPByIndex(i-1, j));

			int a = i+1, b = j-1;
			if (i < ceil(m_points.size() / 2)) // if point is in the upper half of the board.
				b = j + 1;
			p->addNeighbor(getPByIndex(a, b));

			a = i-1, b = j-1;
			if (i > ceil(m_points.size() / 2)) // if point is in the lower half of the board.
				b = j + 1;
			p->addNeighbor(getPByIndex(a, b));
		}

	}
}

Point* Board::getPByIndex(int i, int j)
{
	if (i<0 || i >= m_points.size() || j<0 || j >= m_points[i].size())
		return nullptr;

	return m_points[i][j].get();
}

void Board::createEdges()
{
	connectQueue(enqueueMiddlePoint());
}

// returns a queue with the middle Point.
std::queue<Point*> Board::enqueueMiddlePoint()
{
	// find middle point
	int middleLine = ceil(m_points.size() / 2);
	int middle = ceil(m_points[middleLine].size() / 2);
	auto middleP = m_points[middleLine][middle].get();

	std::queue<Point*> q;
	q.push(middleP);
	return q;
}


/* algorithm to connect all the points to the middle point, using 'bfs' algorithm.
	with added randomality in order to get a random 'binary tree' */
void Board::connectQueue(std::queue<Point*> q)
{
	while (!q.empty())
	{
		auto point = q.front();
		point->turnOn();
		auto nb = point->getOffNeighbors();

		if (nb.empty())
		{
			q.pop();
			continue;
		}

		/* getting a number between 1 and 4, 
			but not more than the ammaount of avalable neighbors. */
		int counter = random_generator(1, std::min(int(nb.size()), 4)); 
		
		for (size_t i = counter; i > 0; i--)
		{
			int indx = random_generator(0, (int)nb.size()-1);
			auto& neighbor = nb[indx];
			q.push(neighbor);
			neighbor->turnOn();
			point->connect(neighbor);
			nb.erase(nb.begin() + indx);
		}

		q.pop();
	}
}


//rotate all points randomly.
void Board::randomRotation()
{
	for (int i = 0; i < m_points.size(); i++)
	{
		for (int j = 0; j < m_points[i].size(); j++)
		{
			int rotation = random_generator(0, MAX_EDGES - 1) * ROTATION;
			m_points[i][j]->rotate(rotation);
		}
	}
}
