#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "utilities.h"

constexpr auto POINT_SIZE = 10;
constexpr auto EDGE_WIDTH = POINT_SIZE / 2;
constexpr auto EDGE_LENGTH = POINT_SIZE * 3;
constexpr auto& POINT_COLOR_OFF = sf::Color::Green;
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

    void click(const sf::Vector2f& location);
    void connect(Point* point);
    bool isConnected(const Point* point) const;

    bool isNeighbor(const Point* neighbor) const;

    void setNeighbor(int index, Point* neighbor); 
    Point* getNeighbor(int index);

    void turnOn();
    void turnOff();
    bool isOn();

private:
    bool m_isOn;

    void addEdge(float rotation);
    void rotate();

    NbArray m_nbList; // array of 6 possible neighbor list.
    sf::CircleShape m_point;
    std::vector<sf::RectangleShape> m_edges;
};
