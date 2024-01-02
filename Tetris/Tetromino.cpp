#include "Tetromino.h"

// Initializes TetShape and Color to the first value in their respective enums
Tetromino::Tetromino()
{
	setShape(TetShape::S);
	color = { TetColor::RED };
}

TetColor Tetromino::getColor() const { return color; } 

TetShape Tetromino::getShape() const { return shape; }

std::vector<Point> Tetromino::getBlockLocs() const { return blockLocs; }

TetShape Tetromino::getRandomShape() {
	// TetShape::COUNT is cast to an int, calculates a rand #, result is cast to a TetShape
	return static_cast<TetShape>(rand() % static_cast<int>(TetShape::COUNT));
}

void Tetromino::setShape(TetShape shape)
{
	this->shape = shape;

	switch (this->shape)
	{
		case TetShape::S:
			color = { TetColor::RED };
			blockLocs = { Point(0, 0), Point(-1, 0), Point(0, 1), Point(1, 1) };
			break;

		case TetShape::Z:
			color = { TetColor::GREEN };
			blockLocs = { Point(0, 0), Point(-1, 1), Point(1, 0), Point(0, 1) };
			break;

		case TetShape::L:
			color = TetColor::ORANGE;
			blockLocs = { Point(0, 0), Point(0, 1), Point(0, -1), Point(1, -1) };
			break;

		case TetShape::J:
			color = TetColor::BLUE_DARK;
			blockLocs = { Point(0, 0), Point(0, -1), Point(-1, -1), Point(0, 1) };
			break;

		case TetShape::O:
			color = TetColor::YELLOW;
			blockLocs = { Point(0, 0), Point(0, 1), Point(1, 0), Point(1, 1) };
			break;

		case TetShape::I:
			color = TetColor::BLUE_LIGHT;
			blockLocs = { Point(0, 0), Point(0, -1), Point(0, 1), Point(0, 2) };
			break;

		case TetShape::T: 
			color = TetColor::PURPLE;
			blockLocs = { Point(0, 0), Point(0, -1), Point(-1, 0), Point(1, 0) };
			break;
	}
}

void Tetromino::rotateClockwise()
{
	// square shape is not rotated
	if (getShape() != TetShape::O)
	{
		for (auto& xYCoords : blockLocs)
		{
			xYCoords.multiplyX(-1);
			xYCoords.swapXY();
		}
	}
}

void Tetromino::printToConsole() const
{
	// rows - x coordinates, from -3 to 3
	for (int col { 3 }; col > -4; col--)
	{
		// columns - y coordinates, from 3 to -3
		for (int row { -3 }; row < 4; row++)
		{
			bool notTetromino = true;

			for (auto& xYCoords : blockLocs)
			{
				// if the coordinates match the grid's values, print an x
				if ((xYCoords.getX() == row) && (xYCoords.getY() == col))
				{
					std::cout << "x";
					notTetromino = false;
				}
			}
			// otherwise, print a .
			if (notTetromino)
			{
				std::cout << ".";
			}
		} 
		std::cout << '\n';
	}
}