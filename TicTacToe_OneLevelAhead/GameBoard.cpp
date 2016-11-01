#include "pch.h"
#include "GameBoard.h"

using namespace std;

namespace TicTacToe {
	const int GameBoard::mWinningPatterns[8] = {
		 0b111000000, 0b000111000, 0b000000111, // rows
		 0b100100100, 0b010010010, 0b001001001, // cols
		 0b100010001, 0b001010100               // diagonals
	};

	GameBoard::GameBoard(Game& game) : mGame(game)
	{
		ClearBoard();
	}

	bool GameBoard::AddPieceToBoard(char piece, int x, int y)
	{
		if (mBoard[x][y] == ' ') {
			mBoard[x][y] = piece;
			return true;
		}
		else
			return false;
	}
	void GameBoard::DisplayBoard()
	{
		for (int xi = 0; xi < 3; xi++) {
			for  (int yi = 0; yi < 3; yi++) {
				cout << "|" << mBoard[xi][yi];
			}
			cout << "|" << endl;
			if (xi != 2)
				cout << "--------" << endl;
		}
	}
	void GameBoard::ClearBoard()
	{
		for (int xi = 0; xi < 3; xi++) {
			for (int yi = 0; yi < 3; yi++) {
				mBoard[xi][yi] = ' ';
			}
		}
	}
	bool GameBoard::CheckWin(Player* player)
	{
		int pattern = 0b000000000;  // 9-bit pattern for the 9 cells
		for (int row = 0; row < 3; ++row) {
			for (int col = 0; col < 3; ++col) {
				if (mBoard[row][col] == player->Piece()) {
					pattern |= (1 << (row * 3 + col));
				}
			}
		}
		for (int winningPattern : mWinningPatterns) {
			if ((pattern & winningPattern) == winningPattern) return true;
		}
		return false;
	}

	void GameBoard::DisplayWinner(Player* player1, Player* player2)
	{
		if (CheckWin(player1)) {
			cout << "Player 1 (" << player1->Piece() << ") Wins" << endl;
		}
		else 	if (CheckWin(player2)) {
			cout << "Player 2 (" << player2->Piece() << ")  Wins" << endl;
		}
		else {
			cout << "Its a Draw!" << endl;
		}
	}
	const char GameBoard::At(int x, int y) const
	{
		return mBoard[x][y];
	}
	void GameBoard::RemoveAt(int x, int y)
	{
		mBoard[x][y] = ' ';
	}

	void GameBoard::Copy(const GameBoard board)
	{
		for (int row = 0; row < 3; ++row) {
			for (int col = 0; col < 3; ++col) {
				mBoard[row][col] = board.mBoard[row][col];
			}
		}
	}

	std::vector<pair<int, int>> GameBoard::GetAvailableMoves()
	{
		std::vector<pair<int, int>> availableMoves;

		for (int row = 0; row < 3; ++row) {
			for (int col = 0; col < 3; ++col) {
				if (mBoard[row][col] == ' ') {
					availableMoves.push_back(pair<int, int>(row, col));
				}
			}
		}

		return availableMoves;
	}
}