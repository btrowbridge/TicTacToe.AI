#pragma once
#include "pch.h"

using namespace std;

namespace TicTacToe {
	class GameBoard;
	class Player;

	class AIPlayer :
		public TicTacToe::Player
	{
	public:
		AIPlayer(const char piece, Game* mGame);

		void MakeMove(GameBoard* board) override;
	private:
		static const int mMaxDepth;

		int* Minimax(int depth, char player);
		int Evaluate();
		int EvaluateLine(int row1, int col1, int row2, int col2, int row3, int col3);
		
		void UpdateCopyBoard(const GameBoard* board );
		std::shared_ptr<GameBoard> mCopyBoard;

		Player* mOtherPlayer;
		
	};
}