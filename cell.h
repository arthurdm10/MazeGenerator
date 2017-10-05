#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include "line.h"
#include <vector>


#define BACK_COLOR sf::Color(47,47,47)
#define CELLSZ 20

class Cell{
private:
    std::vector<Line> lines;
    sf::RectangleShape backShape;
    bool visited;
    int index;

    sf::Vector2f pos;
public:
    Cell(const sf::Vector2f& pos, const int& _index);

    Cell(const Cell& other);

    const int& getIndex() const noexcept;

    void visit() noexcept;

    const sf::RectangleShape& shape() const noexcept;

    const bool& isVisited() const noexcept;

    const sf::Vector2f& getPosition() const noexcept;

    std::vector<Line>& getWalls() noexcept;

    //just to change the shape color...
    void setCurrent() noexcept;

};

#endif // CELL_H
