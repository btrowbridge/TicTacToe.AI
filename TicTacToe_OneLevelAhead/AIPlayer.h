#pragma once
#include "Player.h"
#include <memory>
namespace TicTacToe {
	class GameBoard;
	class Game;

	class AIPlayer :
		public Player
	{
	public:
		AIPlayer(const char piece, Game& mGame);

		void MakeMove(GameBoard* board) override;
	private:
		static const int mMaxDepth;
		static const int mDefaultAlpha;
		static const int mDefaultBeta;

		struct MinimaxResult {
			int Score;
			int Row;
			int Col;
		};


		MinimaxResult Minimax(int depth, char player);
		MinimaxResult MinimaxWithAlphaBeta(int depth, char player, int alpha, int beta);

		int Evaluate();
		int EvaluateLine(int row1, int col1, int row2, int col2, int row3, int col3);

		void UpdateCopyBoard(const  GameBoard board);
		std::shared_ptr<GameBoard> mCopyBoard;

		Player* mOtherPlayer;
	};
}