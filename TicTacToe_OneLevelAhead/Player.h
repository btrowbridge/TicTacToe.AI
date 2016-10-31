#pragma once
#include "GameBoard.h"

namespace TicTacToe {
	class GameBoard;

	class Player
	{
	public:
		Player(const char piece, Game* game);

		const char Piece() const;
		virtual void MakeMove(GameBoard* board);

	protected:
		const char mPiece;
		Game* mGame
	};
}