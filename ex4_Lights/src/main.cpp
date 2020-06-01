#include <SFML/Graphics.hpp>

#include <vector>

constexpr auto pointSize = 10;
constexpr auto edgeWidth = pointSize / 2;
constexpr auto edgeLength = pointSize * 3;
constexpr auto& pointColor = sf::Color::Green;
constexpr auto& edgeColor = sf::Color::Red;
constexpr auto maxEdges = 6;
constexpr auto rotation = 360.f / maxEdges;

class Point
{
public:
    Point(sf::Vector2f location) : m_point(pointSize)
    {
        m_point.setOrigin(m_point.getRadius(), m_point.getRadius());
        m_point.setPosition(location);
        m_point.setFillColor(pointColor);
        const auto edgeCount = rand() % maxEdges;
        for (auto i = 0; i < edgeCount; ++i)
        {
            m_edges.push_back(sf::RectangleShape({ edgeWidth, edgeLength }));
            auto& e = m_edges.back();
            e.setFillColor(edgeColor);
            e.setOrigin(e.getSize().x / 2, -m_point.getRadius());
            e.setPosition(m_point.getPosition());
            e.setRotation(rotation * i);
        }
    }

    void draw(sf::RenderTarget& target) const
    {
        target.draw(m_point);
        for (const auto& e : m_edges)
        {
            target.draw(e);
        }
    }

    void click(sf::Vector2f location)
    {
        if (m_point.getGlobalBounds().contains(location))
        {
            rotate();
        }
    }

private:
    void rotate()
    {
        for (auto& e : m_edges)
        {
            e.rotate(rotation);
        }
    }

    sf::CircleShape m_point;
    std::vector<sf::RectangleShape> m_edges;
};

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode(1000, 1000), "Example");

    auto points = std::vector<Point>();

    while (window.isOpen())
    {
        window.clear();
        for (const auto& p : points)
        {
            p.draw(window);
        }
        window.display();

        if (auto event = sf::Event{}; window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                const auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    points.emplace_back(location);
                    break;
                case sf::Mouse::Button::Right:
                    for (auto& p : points)
                    {
                        p.click(location);
                    }
                    break;
                }
            }
        }
    }
}
