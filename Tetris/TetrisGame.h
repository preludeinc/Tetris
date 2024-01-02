// This class encapsulates the tetris game and its drawing routines, gameplay, & control logic.
// This class was designed so with the idea of potentially instantiating 2 of them
// and have them run side by side (player vs player).
// So, anything you would need for an individual tetris game has been included here.
// Anything you might use between games (like the background, or the sprite used for 
// rendering a tetromino block) was left in main.cpp
// 
// This class is responsible for:
//   - setting up the board,
//	 - drawing game elements to the screen
//   - spawning tetrominoes,
//   - handling user input,
//   - moving and placing tetrominoes 
//
//  [expected .cpp size: ~ 275 lines]

#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "Gameboard.h"
#include "GridTetromino.h"
#include <SFML/Graphics.hpp>


class TetrisGame
{
public:
	// STATIC CONSTANTS
	static const int BLOCK_WIDTH;					// pixel width of a tetris block, init to 32
	static const int BLOCK_HEIGHT;					// pixel height of a tetris block, init to 32
	static const double MAX_SECONDS_PER_TICK;		// the slowest "tick" rate (in seconds), init to 0.75
	static const double MIN_SECONDS_PER_TICK;		// the fastest "tick" rate (in seconds), init to 0.20

private:	
	// MEMBER VARIABLES

	// State members ---------------------------------------------
	int score;										// the current game score.
    Gameboard board;								// the gameboard (grid) to represent where all the blocks are.
    GridTetromino nextShape;						// the tetromino shape that is "on deck".
    GridTetromino currentShape;						// the tetromino that is currently falling.
	
	// Graphics members ------------------------------------------
	sf::Sprite& blockSprite;						// the sprite used for all the blocks.
	sf::RenderWindow& window;						// the window that we are drawing on.
	const Point gameboardOffset{ 0, 0 };			// pixel XY offset of the gameboard on the screen
	const Point nextShapeOffset{ 0, 0 };			// pixel XY offset to the nextShape

	sf::Font scoreFont;								// SFML font for displaying the score.
	sf::Text scoreText;								// SFML text object for displaying the score
									
	// Time members ----------------------------------------------
	// Note: a "tick" is the amount of time it takes a block to fall one line.
	double secondsPerTick = MAX_SECONDS_PER_TICK;	// the seconds per tick (changes depending on score)	

	double secondsSinceLastTick{ 0.0 };				// update this every game loop until it is >= secsPerTick,
													// we then know to trigger a tick.  Reduce this var (by a tick) & repeat.
	bool shapePlacedSinceLastGameLoop{ false };		// Tracks whether we have placed (locked) a shape on
													// the gameboard in the current gameloop	
public:
	// MEMBER FUNCTIONS

	/// <summary>
	/// Constructor
	/// Private member variable names are initialized to parameters which match
	/// reset() the game
	/// load font from file: fonts/RedOctober.tff
	/// setsup score text
	/// </summary>
	/// <param name="window">sf::RenderWindow window</param>
	/// <param name="blockSprite">sf::Sprite blockSprite</param>
	/// <param name="gameboardOffset">st::Point gameboardOffset</param>
	/// <param name="nextShapeOffset">const Point nextShapeOffset</param>
	TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset)
		: window{ window }, blockSprite{ blockSprite }, gameboardOffset{ gameboardOffset }, nextShapeOffset{ nextShapeOffset }
	{
		if (!scoreFont.loadFromFile("fonts/RedOctober.ttf"))
		{
			assert(false && "Missing font: RedOctober.ttf");
		};
		scoreText.setFont(scoreFont);
		scoreText.setCharacterSize(18);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(425, 325);
		reset();
	}

	/// <summary>
	/// Draw anything to do with the game,
	/// including: the board, currentShape, nextShape, and score
	/// Called every game loop.
	/// </summary>
	void draw();								

	/// <summary>
	/// Event and game loop processing
	/// handles keypress events (up, left, right, down, space)
	/// </summary>
	/// <param name="event">sf::Event event</param>
	void onKeyPressed(sf::Event& event);

	/// <summary>
	/// Called every game loop to handle ticks and tetromino placement (locking)
	/// If a new shape is spawned, picks a new shape, removes completed rows,
	/// sets and updates the score. If it fails the game is reset.
	/// </summary>
	/// <param name="secondsSinceLastLoop">a float representing seconds since the game last operated</param>
	void processGameLoop(float secondsSinceLastLoop);

	/// <summary>
	/// A tick() forces the currentShape to move (if there is no tick, 
	/// the currentShape floats in position forever).
	/// This calls attemptMove() on the currentShape. 
	/// If not successful, the currentShape is lock() [-ed] so it can't move further.
	/// </summary>
	void tick();

private:
	/// <summary>
	/// Resets everything for a new game (using existing functions)
	///		- the score is set to 0, and updateScoreDisplay() is used to update display
	///		- determineSecondsPerTick() is used to determine the tick rate
	///		- the gameboard is cleared
	///		- next shape is picked and spawned
	///		- next shape is picked again (for the "on-deck" shape)
	/// </summary>
	void reset();

	/// <summary>
	/// Assign nextShape. setShape is set to a new random shape.
	/// </summary>
	void pickNextShape();

	/// <summary>
	/// Copies the nextShape into the currentShape (through assignment)
	/// Position the currentShape to its spawn location.
	/// </summary>
	/// <returns>true or false based on isPositionLegal()</returns>
	bool spawnNextShape();																	

	/// <summary>
	/// Test if a rotation is legal on the tetromino, and if so, rotate it.
	/// To accomplish this:
	///		1) create a (local) temporary copy of the tetromino
	///		2) rotate it (temp.rotateClockwise())
	///		3) test if temp rotation is legal (isPositionLegal()),
	///			if so - rotate the original tetromino
	/// </summary>
	/// <returns>true / false to indicate successful movement</returns>
	bool attemptRotate(GridTetromino& shape);
   
	/// <summary>
	/// Test if a move is legal on the tetromino, if so, move it.
	/// This is done by:
	///		1) creating a (local) temporary copy of the tetromino
	///		2) moving it (temp.move())
	///		3) testing it to see if temp move was legal (isPositionLegal())
	///		if so - move the original.
	/// </summary>
	/// <param name="shape">GridTetromino shape</param>
	/// <param name="x">int x</param>
	/// <param name="y">int y</param>
	/// <returns>true/false to indicate successful movement</returns>
	bool attemptMove(GridTetromino& shape, int x, int y);												

	/// <summary>
	/// Drops the tetromino vertically as far as it can go.
	/// attemptMove() is used
	/// <param name="shape">GridTetromino shape</param>
	/// </summary>
	void drop(GridTetromino& shape);

	/// <summary>
	/// Copies contents (color) of the tetromino's mapped blockLocs to the grid 
	///		1) get the tetromino's mapped locs via tetromino.getBlockLocsMappedToGrid()
	///		2) use the board's setContent() method to set the content at the mapped locations
	///		3) record the fact that we placed a shape by setting shapePlacedSinceLastGameLoop to true
	/// </summary>
	/// <param name="shape">GridTetromino shape</param>
	void lock(const GridTetromino& shape);
	
	// Graphics methods ==============================================

	/// <summary>
	/// Draw a tetris block sprite on the canvas:
	/// 1) The block position is specified in terms of 2 offsets:
	///		a) the top left (of the gameboard in pixels)
	///		b) an x & y offset on the gameboard - in blocks (not pixels)
	///		   the ints are multipled by BLOCK_WIDTH and BLOCK_HEIGHT to get the pixel offset
	/// 2) set the block colour using blockSprite.setTextureRect()
	/// 3) set the block location using blockSprite.setPosition()
	/// 4) draw the block using window.draw()
	/// </summary>
	/// <param name="topLeft">Point topLeft</param>
	/// <param name="xOffset">int xOffset</param>
	/// <param name="yOffset">int yOffset</param>
	/// <param name="color">TetColor colour</param>
	void drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor colour);
										
	/// <summary>
	/// Draw the gameboard blocks on the window.
	/// Iterate through each row & col,
	/// using drawBlock() to draw a block if it isn't empty.
	/// </summary>
	void drawGameboard();

	/// <summary>
	/// Draw a tetromino on the window
	///		Iterate through each mapped loc and drawBlock() for each
	///		The topLeft determines a 'base point' from which to calculate block offsets
	///			If the Tetromino is on the gameboard: use gameboardOffset
	/// </summary>
	/// <param name="tetromino">GridTetromino tetromino</param>
	/// <param name="topLeft">Point topLeft</param>
	void drawTetromino(GridTetromino& tetromino, const Point& topLeft);

	/// <summary>
	/// Update the score display
	/// Form a string "score: ##" to display the current score
	/// scoreText.setString() is used to display it
	/// </summary>
	void updateScoreDisplay();

	// State & gameplay/logic methods ================================

	/// <summary>
	/// Determine if a Tetromino can legally be placed at its current position on the gameboard
	///		areLocsEmpty() is used and passed to the shape's mapped locs.
	/// </summary>
	/// <param name="shape">GridTetromino shape</param>
	/// <returns>true if the shape is within boarders and the shape's mapped board locs are empty, false otherwise</returns>
	bool isPositionLegal(const GridTetromino& shape) const;

	/// <summary>
	/// Determine if the shape is within the left, right, and bottom gameboard borders.
	///		The upper border is ignored so that shapes can drop in from the top of the gameboard.
	/// </summary>
	/// <param name="shape"></param>
	/// <returns>true, if the shape is within the left, right, and lower border of the grid, false otherwise</returns>
	bool isWithinBorders(const GridTetromino& shape) const;

	/// <summary>
	/// Sets secsPerTick
	///		MAX_SECS_PER_TICK is used
	/// </summary>
	void determineSecondsPerTick();
};

#endif /* TETRISGAME_H */

