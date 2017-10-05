#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>

class Line{
private:
    sf::Vertex points[2];
public:
    bool draw{true};
    sf::Color color;

    Line(const sf::Vector2f& x,
         const sf::Vector2f& y);

    const sf::Vertex* getVertex()const noexcept;
};

#endif // LINE_H
