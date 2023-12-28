module;
#include <iostream>
#include "SFML/Graphics.hpp"
#include <ppl.h>

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
		for (int i = 0; i < grid.size() * 0.3; i++)
		{
			grid[i][40].setFixed(true);
		}
		for (int i = grid.size() * 0.4; i < grid.size() * 0.6; i++)
		{
			grid[i][40].setFixed(true);
		}
		for (int i = grid.size() * 0.7; i < grid.size(); i++)
		{
			grid[i][40].setFixed(true);
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
		double dampingFactor = 0.999;
		Concurrency::parallel_for(0, (int)grid.size(), [&](int i)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j].getFixed()) continue;

				double speedCell = grid[i][j].getVerticalSpeed();
				double massCell = grid[i][j].getMass();
				double verticalPos = grid[i][j].getVerticalPosition();
				double verticalPosRight = j + 1 < grid[i].size() ? grid[i][j + 1].getVerticalPosition() : grid[i][j].getVerticalPosition();
				double verticalPosLeft = j - 1 > -1 ? grid[i][j - 1].getVerticalPosition() : grid[i][j].getVerticalPosition();

				double averageHeight = (verticalPosLeft + verticalPosRight) / 2;
				double difference = verticalPos - averageHeight;
				grid[i][j].setVerticalSpeed(speedCell - 0.1 * difference / massCell);
			}
		});
		Concurrency::parallel_for(0, (int)grid.size(), [&](int i)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j].getFixed()) continue;

				double speedCell = grid[i][j].getVerticalSpeed();
				double massCell = grid[i][j].getMass();
				double verticalPos = grid[i][j].getVerticalPosition();
				double verticalPosRight = i + 1 < grid[i].size() ? grid[i + 1][j].getVerticalPosition() : grid[i][j].getVerticalPosition();
				double verticalPosLeft = i - 1 > -1 ? grid[i - 1][j].getVerticalPosition() : grid[i][j].getVerticalPosition();

				double averageHeight = (verticalPosLeft + verticalPosRight) / 2;
				double difference = verticalPos - averageHeight;
				grid[i][j].setVerticalSpeed(speedCell - 0.1 * difference / massCell);
			}
		});
		Concurrency::parallel_for(0, (int)grid.size(), [&](int i)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				grid[i][j].setVerticalSpeed(grid[i][j].getVerticalSpeed() * dampingFactor);
				grid[i][j].move();
			}
		});
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