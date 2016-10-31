#pragma once
#include <vector>

namespace TicTacToe {
	class Game;
	class Player;

	class GameBoard
	{
	public:
		GameBoard(Game& game);

		bool AddPieceToBoard(char piece, int x, int y);

		void DisplayBoard();
		void ClearBoard();

		bool CheckWin(Player* player);
		void DisplayWinner(Player* player1, Player* player2);

		const char At(int x, int y) const;

		void RemoveAt(int x, int y);

		void Copy(const GameBoard board);

		std::vector<std::pair<int, int>> GetAvailableMoves();

	private:

		char mBoard[3][3];
		const static int mWinningPatterns[8];
		Game& mGame;
	};
}
