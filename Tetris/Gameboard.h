#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <iomanip>
#include <string>
#include <cassert>
#include "Point.h"

class Gameboard
{
	friend int main();
	friend class TestSuite;

public:
	// CONSTANTS
	static const int MAX_X = 10;		// gameboard x dimension
	static const int MAX_Y = 19;		// gameboard y dimension
	static const int EMPTY_BLOCK = -1;	// contents of an empty block

private:
	// MEMBER VARIABLES -------------------------------------------------

	// the gameboard - a grid of X and Y offsets.  
	//  ([0][0] is top left, [MAX_Y-1][MAX_X-1] is bottom right) 
	int grid[MAX_Y][MAX_X];
	// the gameboard offset to spawn a new tetromino at.
	const Point spawnLoc{ MAX_X / 2, 0 };

public:
	// METHODS -------------------------------------------------
	/// <summary>
	/// The grid
	/// </summary>
	Gameboard();

	/// <summary>
	/// Fills the board with EMPTY_BLOCK(s)
	/// Iterates through each rowIndex and fillRow() with EMPTY_BLOCK
	/// </summary>
	void empty();

	/// <summary>
	/// Prints the grid contents to the console, (for debugging purposes)
	/// Uses std::setw(2) to space out the contents
	/// If the content == EMPTY_BLOCK, a '.' is printed, otherwise prints the content.
	/// </summary>
	void printToConsole() const;

	/// <summary>
	/// Gets the content at a given point
	/// Asserts that the point is valid, by using isValidPoint()
	/// </summary>
	/// <param name="xy">a provided point</param>
	/// <returns>an int, the content from the grid at the provided Point</returns>
	int getContent(const Point xy) const;

	/// <summary>
	/// Gets the content at a provided XY location
	/// </summary>
	/// <param name="x">an int for x (col)</param>
	/// <param name="y">an int for y (row)</param>
	/// <returns>an int, the content from the grid at the specified location</returns>
	int getContent(const int x, const int y) const;

	/// <summary>
	/// Sets the content at a valid point
	/// Invalid points are ignored
	/// </summary>
	/// <param name="xy">a provided point</param>
	/// <param name="content">an int, representing the content to set at this location</param>
	void setContent(Point xy, int content);

	/// <summary>
	/// Sets the content at an x, y position
	/// Ignores invalid points
	/// </summary>
	/// <param name="x">an int representing (col) x</param>
	/// <param name="y">an int representing (row) y</param>
	/// <param name="content">an int representing the content to set at the location based on x and y</param>
	void setContent(int x, int y, int content);

	/// <summary>
	/// Sets the content for a set of points, invalid points are ignored
	/// </summary>
	/// <param name="locations">a vector of points, representing locations</param>
	/// <param name="content">an int representing the content to set</param>
	void setContent(std::vector<Point>& locations, int content);

	/// <summary>
	/// Determines if (valid) points passed in are empty
	/// Invalid points are ignored
	/// </summary>
	/// <param name="locationsToTest"></param>
	/// <returns>true if the content at all valid points is EMPTY_BLOCK, false otherwise</returns>
	bool areAllLocsEmpty(std::vector<Point> locationsToTest) const;

	/// <summary>
	/// Removes all completed rows from the board
	/// Does so using getCompletedRowIndices() and removeRows()
	/// </summary>
	/// <returns>the count of completed rows removed</returns>
	int removeCompletedRows();

	/// <summary>
	/// Gets the spawn location
	/// </summary>
	/// <returns>A point, representing the private spawnLoc</returns>
	Point getSpawnLoc() const;

private:
	/// <summary>
	/// Determines if a given point is a valid grid location
	/// </summary>
	/// <param name="obj"></param>
	/// <returns>true if the point is a valid grid location, false otherwise</returns>
	bool isValidPoint(Point obj) const;

	/// <summary>
	/// Determines if a given XY is a valid grid location
	/// </summary>
	/// <param name="x">an int representing x</param>
	/// <param name="y">an int representing y</param>
	/// <returns>true if the x, y is a valid grid location, false otherwise</returns>
	bool isValidPoint(int x, int y) const;

	/// <summary>
	/// Returns a bool indicating if the given row is full (has no EMPTY_BLOCK)
	/// Asserts if the row index is valid
	/// </summary>
	/// <param name="rowIndex">an int representing the row index we want to test</>
	/// <returns></returns>
	bool isRowCompleted(int rowIndex) const;

	/// <summary>
	/// Fill a given grid row with specified content
	/// </summary>
	/// <param name="rowIndex"an int representing a row index></param>
	/// <param name="content">an int representing content</param>
	void fillRow(const int rowIndex, const int content);

	/// <summary>
	/// Scans the board for completed rows.
	/// Iterate through grid rows and use isRowCompleted(rowIndex)
	/// </summary>
	/// <returns>a vector of completed row indices (ints)</returns>
	std::vector<int> getCompletedRowIndices() const;

	/// <summary>
	/// Copy a source row's contents into a target row
	/// </summary>
	/// <param name="srcRowIndex">an int representing the source row index</param>
	/// <param name="targetRowIndex">an int representing the target row index</param>
	void copyRowIntoRow(const int srcRowIndex, const int targetRowIndex);

	/// <summary>
	/// Given a row index:
	///		1) Assert the row index is valid
	///		2) Starting at rowIndex, copy each row above the removed row a row downwards
	///		3) fillRow() is called on the first row (EMPTY_BLOCKS are placed in it)
	/// </summary>
	/// <param name="rowIndex">an int representing a row index</param>
	void removeRow(const int rowIndex);

	/// <summary>
	/// Given a vector of row indices, remove them
	/// Iterate through the vector, calling removeRow() on each row index.
	/// </summary>
	/// <param name="rowIndex">A vector of integers representing row indices to be removed</param>
	void removeRows(const std::vector<int> rowIndex);
};

#endif /* GAMEBOARD_H */