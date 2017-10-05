#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <map>
#include <stack>
#include "cell.h"

using namespace std;


#define WIDTH 800
#define HEIGHT 600

//return a random neighbor that hasnt been visited
Cell* getNeighbor(std::map<int, std::array<Cell*, WIDTH/CELLSZ>>& cells,
                  const Cell& cell){

    auto pos = cell.getPosition();
    auto index = cell.getIndex();

    std::vector<Cell*> ng;
    Cell* c;

    //top
    if(pos.y > 0){
        c = cells[pos.y - CELLSZ][index];
        if(!c->isVisited()){
            ng.push_back(c);
        }
    }

    //right
    if(pos.x < WIDTH - CELLSZ){
        c = cells[pos.y][index+1];
        if(!c->isVisited()){
            ng.push_back(c);
        }
    }

    //bottom
    if(pos.y < HEIGHT - CELLSZ){
        c = cells[pos.y+CELLSZ][index];
        if(!c->isVisited()){
            ng.push_back(c);
        }
    }


    //left
    if(pos.x > 0){
        c = cells[pos.y][index-1];
        if(!c->isVisited()){
            ng.push_back(c);
        }
    }

    if(ng.size() == 0){
        return nullptr;
    }

    int n = rand() % ng.size();

    return ng[n];

}


int main(){
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Maze Generator");

    std::map<int, std::array<Cell*, WIDTH/CELLSZ>> cells;
    std::stack<Cell*> visiteds;

    for(int y = 0; y < HEIGHT; y += CELLSZ){
        std::array<Cell*, WIDTH/CELLSZ> arr;
        int index = 0;
        for(int x = 0; x < WIDTH; x += CELLSZ){
            arr[index] = new Cell(sf::Vector2f(x, y), index);
            index++;
        }
        cells.insert(make_pair(y, arr));
    }

    Cell *current = cells[0][0];

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear(BACK_COLOR);
        for(const auto& row : cells){
            for(const auto& cell : row.second){
                window.draw(cell->shape());
                for(const auto& wall : cell->getWalls()){
                    if(wall.draw){
                        window.draw(wall.getVertex(), 2, sf::Lines);
                    }
                }
            }
        }

        current->setCurrent();

        window.draw(current->shape());
        window.display();

        auto* next = getNeighbor(cells, *current);
        if(next == nullptr){
            if(visiteds.size() > 0){
                next = visiteds.top();
                visiteds.pop();
            }else{
                //done
                continue;
            }
        }else{
            //next is on the same row(left or right)
            if(next->getPosition().y == current->getPosition().y){
                if(next->getPosition().x > current->getPosition().x){
                    //next cell is on the right of current cell

                    current->getWalls().at(1).draw = false;
                    next->getWalls().at(3).draw = false;
                }else if(next->getPosition().x < current->getPosition().x){
                    //next cell is on the left of current cell

                    current->getWalls().at(3).draw = false;
                    next->getWalls().at(1).draw = false;
                }
            }else{
                if(next->getPosition().y > current->getPosition().y){
                    //next cell is on the bottom

                    current->getWalls().at(2).draw = false;
                    next->getWalls().at(0).draw = false;
                }else{
                    //next cell is on the top
                    current->getWalls().at(0).draw = false;
                    next->getWalls().at(2).draw = false;
                }
            }
            visiteds.push(current);
        }

        current->visit();
        current = next;
    }



    return 0;
}
