#include "Point.h"

Point::Point(const sf::Vector2f& location) : m_point(POINT_SIZE), m_isOn(false)
{
    m_point.setOrigin(m_point.getRadius(), m_point.getRadius());
    m_point.setPosition(location);
    m_point.setFillColor(POINT_COLOR_OFF);
}

void Point::draw(sf::RenderTarget& target) const
{
    target.draw(m_point);
    for (const auto& e : m_edges)
    {
        target.draw(e);
    }
}

void Point::click(const sf::Vector2f& location, bool clockWise)
{
    if (m_point.getGlobalBounds().contains(location))
    {
        auto rotation = clockWise ? ROTATION : -ROTATION;
        rotate(rotation);
    }
}

void Point::connect(Point* point)
{
    if (!isNeighbor(point))
        throw std::logic_error("try to connect 2 non neighbor points");

     if (isConnected(point))
        throw std::logic_error("try to connect connected points");

     
     // add edge to each point
     addEdge(0);
     auto& e1 = m_edges.back();

     point->addEdge(0);
     auto& e2 = point->m_edges.back();

     // rotate edges until the points are connected
     for (size_t i = 0; i < MAX_EDGES; i++)
     {
         for (size_t j = 0; j < MAX_EDGES; j++)
         {

             if (e1.getGlobalBounds().intersects(e2.getGlobalBounds()))
                 return; //end function if conection succses 

             e2.rotate(ROTATION);
         }

         e1.rotate(ROTATION);
     }

     
}

bool Point::isConnected(const Point* point) const
{
    if (!isNeighbor(point))
        throw std::logic_error("asked if 2 non neighbor points connected");

    for (auto& e1 : m_edges)
    {
        for (auto& e2 : point->m_edges)
        {
            if (e1.getGlobalBounds().intersects(e2.getGlobalBounds()))
                return true;
        }
    }

    return false;
}

bool Point::isNeighbor(const Point* neighbor) const
{
    if (neighbor == nullptr)
        throw std::logic_error("asked if nullptr is a neighbor");

    for (const auto& nb : m_nbList)
    {
        if(nb == neighbor)
            return true;
    }
    return false;
}

void Point::addNeighbor(Point* neighbor)
{
   m_nbList.push_back(neighbor);
}

std::vector<Point*> Point::getNeighborList()
{
    return m_nbList;
}

std::vector<Point*> Point::getOffNeighbors()
{
    std::vector<Point*> lst;
    std::copy_if(m_nbList.begin(), m_nbList.end(),
        std::back_inserter(lst), [](Point* val) { return val && !val->isOn(); });

    return  std::move(lst);
}


void Point::turnOn()
{
    m_point.setFillColor(POINT_COLOR_ON);
    m_isOn = true;
}

void Point::turnOff()
{
    m_point.setFillColor(POINT_COLOR_OFF);
    m_isOn = false;
}

bool Point::isOn()
{
    return m_isOn;
}


void Point::addEdge(float rotation)
{
    m_edges.emplace_back(sf::Vector2f{ EDGE_WIDTH, EDGE_LENGTH });
    auto& e = m_edges.back();
    e.setFillColor(EDGE_COLOR);
    e.setOrigin(e.getSize().x / 2, -m_point.getRadius());
    e.setPosition(m_point.getPosition());
    e.setRotation(rotation + 90);  // add 90 degreas to the rotation for horizontal edges.
}

void Point::rotate(float rotation)
{
    for (auto& e : m_edges)
    {
        e.rotate(rotation);
    }
}