#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <ostream>
#include <string>

class Point {
	friend class TestSuite;

	private:
		int x;
		int y;

	public:
		/// <summary>
		/// Default constructor for Point class
		/// </summary>
		Point();

		/// <summary>
		/// Constructor for point class that accepts parameters
		/// </summary>
		/// <param name="x">point x</param>
		/// <param name="y">point y</param>
		Point(int x, int y);

		/// <summary>
		/// Getter for x coordinate
		/// </summary>
		/// <returns>an int, representing x coordinate</returns>
		int getX() const;

		/// <summary>
		/// Getter for y coordinate
		/// </summary>
		/// <returns>an int, representing y coordinate</returns>
		int getY() const;

		/// <summary>
		/// Setter for x coordinate
		/// </summary>
		/// <param name="x">an int, representing x coordinate</param>
		void setX(int x);

		/// <summary>
		/// Setter for y coordinate
		/// </summary>
		/// <param name="y">an int, representing y coordinate</param>
		void setY(int y);

		/// <summary>
		/// Sets x and y coordinates
		/// </summary>
		/// <param name="x">an int, representing x coordinate</param>
		/// <param name="y">an int, representing y coordinate</param>
		void setXY(int x, int y);

		/// <summary>
		/// Swaps x and y
		/// </summary>
		void swapXY();

		/// <summary>
		/// Multiply x by some factor
		/// </summary>
		/// <param name="factor">the factor to multiply by</param>
		void multiplyX(int factor);

		/// <summary>
		/// Multiply y by some factor
		/// </summary>
		/// <param name="factor"></param>
		void multiplyY(int factor);

		/// <summary>
		/// Returns a string to represent the state of the point instance.
		/// Used for debugging
		/// </summary>
		/// <returns>a string in the form [x,y] </returns>
		std::string toString() const;
};

#endif	/* POINT_H */