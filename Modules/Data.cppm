module;
#include <iostream>
#include "SFML/Graphics.hpp"
import Cell;
using namespace sf;
export module Data;

namespace data
{
	export std::vector<std::vector<Cell>> generateGrid(Vector2f sizeCell, RenderWindow& win)
	{
		std::vector<std::vector<Cell>> grid;
		int width = win.getSize().x / sizeCell.x;
		int height = win.getSize().y / sizeCell.y;
		for (int i = 0; i < height; i++)
		{
			grid.push_back(std::vector<Cell>());
			for (int j = 0; j < width; j++) 
			{
				grid[i].push_back(Cell(sizeCell.x, sizeCell.y, sizeCell.x * j, sizeCell.y * i , 1));
				if ((i == 0 || i == height - 1) || (j == 0 || j == width - 1)) grid[i][j].setFixed(true);
			}
		}
		return grid;
	}
	export void drawGrid(std::vector<std::vector<Cell>>& grid, RenderWindow& win)
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				grid[i][j].draw(win);
			}
		}
	}
	export void moveWave(std::vector<std::vector<Cell>>& grid)
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++) 
			{
				if (grid[i][j].getFixed()) continue;

				double speedBlock = grid[i][j].getVerticalSpeed();
				double massBlock = grid[i][j].getMass();
				double verticalPos = grid[i][j].getVerticalPosition();
				double verticalPosRight = j + 1 < grid[i].size() ? grid[i][j + 1].getVerticalPosition() : grid[i][j].getVerticalPosition();
				double verticalPosLeft = j - 1 > -1 ? grid[i][j - 1].getVerticalPosition() : grid[i][j].getVerticalPosition();

				double averageHeight = (verticalPosLeft + verticalPosRight) / 2;
				double difference = verticalPos - averageHeight;
				grid[i][j].setVerticalSpeed(speedBlock - 0.1 * difference / massBlock);
			}
		}

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				grid[i][j].move();
			}
		}
	}
	export void clickWave(double x, double y, std::vector<std::vector<Cell>>& grid)
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j].clickOnCell(x, y) && !grid[i][j].getFixed())
				{
					grid[i][j].setVerticalSpeed(10 / grid[i][j].getMass());
					return;
				}
			}
		}
	}
}