#pragma once
#include "utilities.h"
#include "Point.h"

constexpr auto WIN_WIDTH = 900;
constexpr auto WIN_LENGTH = 900;
constexpr auto MIN_LINE_SIZE = 3;  // size of the smalest line of points.
constexpr auto SPACE = 2*POINT_SIZE +2*EDGE_LENGTH -1; //space between two points. (-1 for collison between edges)

using PointsVec = std::vector<std::unique_ptr< Point>>;
using PointsTbl = std::vector<PointsVec>;

class Board
{
public:
	Board();
	void create(int size);
	void draw(sf::RenderWindow& window) const;
	void click(sf::Vector2f location);

private:

	void createPoints(int size);
	PointsVec createLine(sf::Vector2f location, int size);
	void createNbList();
	Point* getPByIndex(int i, int j); 
	void createEdges();

private:
	
	PointsTbl m_points;
};