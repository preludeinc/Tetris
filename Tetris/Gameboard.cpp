#include "Gameboard.h"

Gameboard::Gameboard() {
	Gameboard::empty();
};

void Gameboard::empty() {

	// iterate through each rowIndex and fillRow() with EMPTY_BLOCK
	for (int y{ 0 }; y < MAX_Y; y++)
	{
		fillRow(y, EMPTY_BLOCK);
	}
};

void Gameboard::printToConsole() const {
	std::cout << '\n';

	for (int y{ 0 }; y < MAX_Y; y++)
	{
		for (int x{ 0 }; x < MAX_X; x++)
		{
			if (grid[y][x] == EMPTY_BLOCK)
			{
				std::cout << '.' << std::setw(2);
			}
			else {
				std::cout << std::to_string(Gameboard::getContent(x, y)) << std::setw(2);
			}
		}
		std::cout << '\n';
	}
};

int Gameboard::getContent(const Point xy) const {
	if (!isValidPoint(xy)) {
		std::cout << "stop";
	}
	assert(isValidPoint(xy));
	return grid[xy.getY()][xy.getX()];
};

int Gameboard::getContent(const int x, const int y) const {
	assert(isValidPoint(x, y));
	return grid[y][x];
};

void Gameboard::setContent(Point xy, int content) {

	if (isValidPoint(xy.getX(), xy.getY()))
	{
		grid[xy.getY()][xy.getX()] = content;
	}
};

void Gameboard::setContent(int x, int y, int content) {
	if (isValidPoint(x, y))
	{
		grid[y][x] = content;
	}
};

void Gameboard::setContent(std::vector<Point>& locations, const int content) {
	for (Point& xYCoords : locations)
	{
		// test for validity is performed here
		setContent(xYCoords, content);
	}
};

bool Gameboard::areAllLocsEmpty(std::vector<Point> locationsToTest) const {
	for (Point& xy : locationsToTest)
	{
		if (isValidPoint(xy))
		{
			if (getContent(xy) != EMPTY_BLOCK)
			{
				return false;
			}
		}
	}
	return true;
};

int Gameboard::removeCompletedRows() {
	std::vector<int> completedRows = getCompletedRowIndices(); 

	for (int i{ 0 }; i < completedRows.size(); i++)
	{
		removeRows(completedRows);
	}
	return completedRows.size();
};

Point Gameboard::getSpawnLoc() const {
	return spawnLoc;
};

bool Gameboard::isValidPoint(Point pointObj) const {
	return isValidPoint(pointObj.getX(), pointObj.getY());
};

bool Gameboard::isValidPoint(int x, int y) const {
	// does the point fall within the range of ([0][0] - top left to [MAX_Y - 1][MAX_X-1] - bottom right?)
	return ((x >= 0) && (x < MAX_X) && (y >= 0) && (y < MAX_Y));
};

bool Gameboard::isRowCompleted(int rowIndex) const {
	assert(rowIndex >= 0 && rowIndex < MAX_Y);
	for (int x{ 0 }; x < MAX_X; x++)
	{
		if (grid[rowIndex][x] == EMPTY_BLOCK)
		{
			return false;
		}
	}
	return true;
};

void Gameboard::fillRow(const int rowIndex, const int content)
{
	for (int x{ 0 }; x < MAX_X; x++)
	{
		grid[rowIndex][x] = content;
	}
};

std::vector<int> Gameboard::getCompletedRowIndices() const {
	std::vector<int> completedRows;
	for (int y{ 0 }; y < MAX_Y; y++)
	{
		if (isRowCompleted(y))
		{
			completedRows.push_back(y);
		}
	}
	return completedRows;
};

void Gameboard::copyRowIntoRow(const int srcRowIndex, const int targetRowIndex) {
	for (int x { 0 }; x < MAX_X; x++)
	{
		grid[targetRowIndex][x] = grid[srcRowIndex][x];
	}
};

void Gameboard::removeRow(const int rowIndex) {
	for (int y { rowIndex - 1 }; y >= 0; y--)
	{
		copyRowIntoRow(y, y + 1);
	}
	fillRow(0, EMPTY_BLOCK);
};

void Gameboard::removeRows(const std::vector<int> rowIndex) {
	for (const int index : rowIndex)
	{
		removeRow(index);
	}
};