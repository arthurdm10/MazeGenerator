#include "line.h"

Line::Line(const sf::Vector2f &x, const sf::Vector2f &y){

    this->points[0] = sf::Vertex(x);
    this->points[1] = sf::Vertex(y);
}

const sf::Vertex* Line::getVertex()const noexcept{
    return this->points;
}
