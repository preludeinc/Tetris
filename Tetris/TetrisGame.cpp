#include "TetrisGame.h"

	// initializing static constants 
	const int TetrisGame::BLOCK_WIDTH{ 32 };
	const int TetrisGame::BLOCK_HEIGHT{ 32 };
	const double TetrisGame::MAX_SECONDS_PER_TICK{ 0.75 };
	const double TetrisGame::MIN_SECONDS_PER_TICK { 0.20 };

	void TetrisGame::draw() {
		drawGameboard();
		drawTetromino(currentShape, gameboardOffset);
		drawTetromino(nextShape, nextShapeOffset);
		window.draw(scoreText);
	}

	void TetrisGame::onKeyPressed(sf::Event& event) {
		switch (event.key.code)
		{
			case sf::Keyboard::Up: attemptRotate(currentShape); break;
			case sf::Keyboard::Left: attemptMove(currentShape, -1, 0); break;
			case sf::Keyboard::Right: attemptMove(currentShape, 1, 0); break;
			case sf::Keyboard::Down: attemptMove(currentShape, 0, 1); break;
			case sf::Keyboard::Space: drop(currentShape); lock(currentShape); break;
		}
	}

	void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
		// once a shape has been placed
		if (shapePlacedSinceLastGameLoop) {
			if (spawnNextShape())
			{
				pickNextShape();
				int completedRows = board.removeCompletedRows();
				// 100 points for each completed row
				score += (completedRows * 100);
				updateScoreDisplay();
				determineSecondsPerTick();
			}
			else  {
				reset();
			}
			shapePlacedSinceLastGameLoop = false;
		}
		secondsSinceLastTick += secondsSinceLastLoop;
		if (secondsSinceLastTick > TetrisGame::secondsPerTick)
		{
			tick();
			secondsSinceLastTick -= TetrisGame::secondsPerTick;
		}
		
	}

	void TetrisGame::tick() {
		if (attemptMove(currentShape, 0, 1)) {}
		// if tick fails, the shape is locked
		else {
			lock(currentShape);	
		}
	}

	void TetrisGame::reset() {
		score = 0;
		updateScoreDisplay();
		determineSecondsPerTick();
		board.empty();
		pickNextShape();
		// if the board is full, it is reset 
		if (!spawnNextShape())
		{
			reset();
		}
		else {
			spawnNextShape();
		}
		pickNextShape();
	}

	void TetrisGame::pickNextShape() {
		nextShape.setShape(Tetromino::getRandomShape());
	}

	bool TetrisGame::spawnNextShape() {
		currentShape = nextShape;
		currentShape.setGridLoc(board.getSpawnLoc());
		return isPositionLegal(currentShape);
	}

	bool TetrisGame::attemptRotate(GridTetromino& shape) { 
		// create a local copy of the tetromino, then rotate it
		GridTetromino temp = currentShape;
		temp.rotateClockwise();	

		// if position is legal, rotate the original
		if (isPositionLegal(temp))
		{
			currentShape.rotateClockwise();
			return true;
		}
		return false;
	}

	bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) { 
		// create a local copy, rotate it
		GridTetromino temp = currentShape;
		temp.move(x, y);
		// if legal position, rotate the original
		if (isPositionLegal(temp)) 
		{
			currentShape.move(x, y);
			return true;
		}
		return false;
	}

	void TetrisGame::drop(GridTetromino& shape) {
		// keep moving down while it's vertically possible
		while (attemptMove(shape, 0, 1)) {};
	}

	void TetrisGame::lock(const GridTetromino& shape) {
		std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
		for (auto& pt : mappedLocs)
		{
			board.setContent(pt, static_cast<int>(shape.getColor()));
		}
		shapePlacedSinceLastGameLoop = true;		// shape is placed
	}

	void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor colour) {
		float xPixelOffset = static_cast<float>(xOffset * BLOCK_WIDTH);
		float yPixelOffset = static_cast<float>(yOffset * BLOCK_HEIGHT);
		// casts Tetcolor to an int, is multiplied by the width of the block to determine its position
		int xTilePixelOffset = static_cast<int>(colour) * BLOCK_WIDTH;
		blockSprite.setTextureRect(sf::IntRect(xTilePixelOffset, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
		blockSprite.setPosition(topLeft.getX() + xPixelOffset, topLeft.getY() + yPixelOffset);
		window.draw(blockSprite);
	}

	void TetrisGame::drawGameboard() {
		for (int x { 0 }; x < Gameboard::MAX_X; x++)
		{
			for (int y { 0 }; y < Gameboard::MAX_Y; y++)
			{
				// if the grid at this point is not empty
				if (board.getContent(x, y) != Gameboard::EMPTY_BLOCK)
				{
					// draw a block
					drawBlock(gameboardOffset, x, y, static_cast<TetColor>(board.getContent(x, y)));
				}
			}
		}
	}

	void TetrisGame::drawTetromino(GridTetromino& tetromino, const Point& topLeft) {
		std::vector<Point> mappedPoints = tetromino.getBlockLocsMappedToGrid();
		for (auto& mappedLoc : mappedPoints)
		{
			drawBlock(topLeft, mappedLoc.getX(), mappedLoc.getY(), tetromino.getColor());
		}
	}

	void TetrisGame::updateScoreDisplay() {
		std::string scoreString = "score: " + std::to_string(score);
		scoreText.setString(scoreString);
	}

	bool TetrisGame::isPositionLegal(const GridTetromino& shape) const { 
		std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
		// if locations are empty and shape is within the grid
		return (board.areAllLocsEmpty(mappedLocs) && isWithinBorders(shape));
	};

	bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
		std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
		// ignores points at the top
		for (auto& pt : mappedLocs)
		{
			if (pt.getX() < 0 ||
				pt.getX() >= Gameboard::MAX_X ||
				pt.getY() >= Gameboard::MAX_Y )
			{
				return false;
			}
		}
		return true;
	}

	void TetrisGame::determineSecondsPerTick() {
		// speed increases once player is improving score-wise
		switch (score)
		{
			case 200: secondsSinceLastTick = { 0.75 }; break;
			case 300: secondsSinceLastTick = { 0.65 }; break;
			case 400: secondsSinceLastTick = { 0.55 }; break;
			case 500: secondsSinceLastTick = { 0.45 }; break;
			case 600: secondsSinceLastTick = { 0.35 }; break;
		}
	}


