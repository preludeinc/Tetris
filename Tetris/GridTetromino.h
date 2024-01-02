// The GridTetromino extends the basic Tetromino
// Functionality added:
//  - The concept of the tetromino's location on the gameboard/grid. (gridLoc)
//  - The ability to change a tetromino's location
//  - The ability to retrieve a vector of tetromino block locations mapped to the gridLoc.

#ifndef GRIDTETROMINO_H
#define GRIDTETROMINO_H

#include "Tetromino.h"

/// <summary>
/// This class extends (inherits from) the Tetromino's class.
/// </summary>
class GridTetromino: public Tetromino
{	
private:
	Point gridLoc;	// the [x,y] location of this tetromino on the grid/gameboard. 
					// This loc changes each time the tetromino moves.
public:
	// constructor, initialize gridLoc to 0,0
	GridTetromino();

	/// <summary>
	/// A getter for the tetromino's location
	/// </summary>
	/// <returns>a Point (the private member variable gridLoc)</returns>
	Point getGridLoc() const;

	/// <summary>
	/// A setter for the tetromino's location.
	/// </summary>
	/// <param name="x">int x</param>
	/// <param name="y">int y</param>
	void setGridLoc(int x, int y);	

	/// <summary>
	/// A setter for the tetromino's location.
	/// </summary>
	/// <param name="newGridLoc">a Point (the new gridLoc)</param>
	void setGridLoc(Point newGridLoc);		

	/// <summary>
	/// Transposes the gridLoc of the shape.
	/// </summary>
	/// <param name="xOffSet">the x offset (distance) to move</param>
	/// <param name="yOffSet">the y offset (distance) to move</param>
	void move(int xOffset, int yOffset);	

	/// <summary>
	/// Builds and returns a vector of Points to represent the inherited blockLocs vector mapped to the
	/// gridLoc of this object instance.
	/// If the Point [x, y] exists in the vector, and the gridLoc is [5, 6] the mapped Point returned is [5+x, 6+y]
	/// </summary>
	/// <returns>a vector of point objects</returns>
	std::vector<Point> getBlockLocsMappedToGrid() const;

};

#endif /* GRIDTETROMINO_H */