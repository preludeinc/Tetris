#include "GridTetromino.h"

GridTetromino::GridTetromino()
{
	gridLoc = Point(0, 0);
};

Point GridTetromino::getGridLoc() const
{
	return gridLoc;
}

void GridTetromino::setGridLoc(int x, int y)
{
	gridLoc.setX(x);
	gridLoc.setY(y);
}

void GridTetromino::setGridLoc(Point newGridLoc)
{
	setGridLoc(newGridLoc.getX(), newGridLoc.getY());
}

void GridTetromino::move(int xOffset, int yOffset)
{
	setGridLoc(gridLoc.getX() + xOffset, gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const
{
	std::vector<Point> mappedLocs;
	
	// blockLocs + gridLoc
	for (auto& pt : blockLocs)
	{
		mappedLocs.push_back(Point(gridLoc.getX() + pt.getX(), gridLoc.getY() + pt.getY()));
	}
	return mappedLocs;
}

