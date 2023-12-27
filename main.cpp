#include <iostream>
#include <SFML/Graphics.hpp>
import Cell;
import Data;
using namespace sf;

int main() 
{
    Vector2f sizeCell = Vector2f(10.0f, 10.0f);

    RenderWindow win(VideoMode(1920, 1080), "LightInterference", sf::Style::Default); 
    win.setVerticalSyncEnabled(true);

    std::vector<std::vector<Cell>> grid = data::generateGrid(sizeCell, win);

    Clock logic;
    Time timePerFrame = seconds(1.0f / 60.0f);
    Time accumulate = Time::Zero;

    while (win.isOpen())
    {
        Event event;
        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                win.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Button::Left)
            {
                sf::Vector2f mousePosition = win.mapPixelToCoords(sf::Mouse::getPosition(win));
                data::clickWave(mousePosition.x, mousePosition.y, grid);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
            {
                grid.clear();
                grid = data::generateGrid(sizeCell, win);
            }
        }
        accumulate += logic.restart();
        while (accumulate >= timePerFrame) 
        {
            accumulate -= timePerFrame;
            data::moveWave(grid);
        }
        win.clear(Color::Black);

        data::drawGrid(grid, win);

        win.display();
    }
}