#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "utilities.h"

constexpr auto POINT_SIZE = 10;
constexpr auto EDGE_WIDTH = POINT_SIZE / 2;
constexpr auto EDGE_LENGTH = POINT_SIZE * 3;
constexpr auto& POINT_COLOR_OFF = sf::Color::Blue;
constexpr auto& POINT_COLOR_ON = sf::Color::Yellow;
constexpr auto& EDGE_COLOR = sf::Color::Red;
constexpr auto MAX_EDGES = 6;
constexpr auto ROTATION = 360.f / MAX_EDGES;

class Point;
using NbArray = std::array<Point*, MAX_EDGES>;

class Point
{
public:
    Point(const sf::Vector2f& location);

    void draw(sf::RenderTarget& target) const;

    void click(const sf::Vector2f& location, bool clockWise);
    void connect(Point* point);
    bool isConnected(const Point* point) const;

    bool isNeighbor(const Point* neighbor) const;

    void addNeighbor(Point* neighbor);
    std::vector<Point*> getNeighborList();
    std::vector<Point*> getOffNeighbors();

    void turnOn();
    void turnOff();
    bool isOn();
    void rotate(float rotation);
private:
    void addEdge(float rotation);

    bool m_isOn;
    std::vector<Point*> m_nbList; // list of 6 possible neighbor list (could have a nullptr neighbor).
    sf::CircleShape m_point;
    std::vector<sf::RectangleShape> m_edges;
};
