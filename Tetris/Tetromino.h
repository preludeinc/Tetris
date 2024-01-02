#ifndef TETROMINO_H
#define TETROMINO_H

#include "Point.h"
#include <vector>


enum class TetColor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE };
enum class TetShape { S, Z, L, J, O, I, T, COUNT };


class Tetromino {
	friend class TestSuite;

	private:
		TetColor color;
		TetShape shape;

	protected:
		std::vector<Point> blockLocs;
		
	public:
		// Tetromino constructor
		Tetromino();

		/// <summary>
		/// Gets the shape's colour.
		/// </summary>
		/// <returns>the colour of the tetromino object</returns>
		TetColor getColor() const;

		/// <summary>
		/// Gets the shape's shape.
		/// </summary>
		/// <returns>returns the shape of the tetromino object</returns>
		TetShape getShape() const;

		/// <summary>
		/// Gets the current blockLocs vector, based on the current shape.
		/// </summary>
		/// <returns>the current blockLocs vector</returns>
		std::vector<Point> getBlockLocs() const;

		/// <summary>
		/// Returns a random TetShape.
		/// rand() is used to return a random TetShape from enum class.
		/// </summary>
		/// <returns></returns>
		static TetShape getRandomShape();

		/// <summary>
		/// Sets the shape, the blockLocs for the shape, and its colour.
		/// </summary>
		/// <param name="shape">the shape to be set</param>
		void setShape(TetShape shape);

		/// <summary>
		/// Rotates the shape 90 degrees around [0,0] clockwise
		/// Iterates through blockLocs
		/// </summary>
		void rotateClockwise();

		/// <summary>
		/// Prints a grid to help display the current shape
		/// If the point exists in the blockLocks list, prints an 'x' rather than a '.'
		/// </summary>
		void printToConsole() const;
};

#endif; /* TETROMINO_H */
