#include "cell.h"


Cell::Cell(const sf::Vector2f &pos, const int &_index) :
    backShape(sf::Vector2f(CELLSZ, CELLSZ)),
    pos(pos),
    index(_index){

    this->backShape.setPosition(pos);
    this->backShape.setFillColor(BACK_COLOR);

    this->visited = false;

    //top
    lines.push_back(Line(pos,
                         sf::Vector2f(pos.x + CELLSZ, pos.y)));

    //right
    lines.push_back(Line(sf::Vector2f(pos.x + CELLSZ, pos.y),
                         sf::Vector2f(pos.x + CELLSZ, pos.y + CELLSZ)));

    //bottom
    lines.push_back(Line(sf::Vector2f(pos.x + CELLSZ, pos.y + CELLSZ),
                         sf::Vector2f(pos.x, pos.y + CELLSZ)));

    //left
    lines.push_back(Line(pos, sf::Vector2f(pos.x, pos.y + CELLSZ)));

}

Cell::Cell(const Cell &other){
    this->visited = other.visited;
    this->lines = other.lines;
    this->pos = other.pos;
    this->backShape = other.backShape;
}

const int &Cell::getIndex() const noexcept{
    return this->index;
}

void Cell::visit() noexcept{
    this->visited = true;
    this->backShape.setFillColor(sf::Color(20,10,255));
}

const sf::RectangleShape &Cell::shape() const noexcept{
    return this->backShape;
}

const bool &Cell::isVisited() const noexcept{
    return this->visited;
}

const sf::Vector2f &Cell::getPosition() const noexcept{
    return this->pos;
}

std::vector<Line> &Cell::getWalls() noexcept{
    return this->lines;
}

void Cell::setCurrent() noexcept{
    this->backShape.setFillColor(sf::Color::Red);
}
