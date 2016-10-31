#include	"pch.h"
#include "Player.h"

using namespace std;

namespace TicTacToe {
	Player::Player(const char piece, Game& game) : mPiece(piece), mGame(game)
	{
	}
	const char Player::Piece() const
	{
		return mPiece;
	}

	void Player::MakeMove(GameBoard * board)
	{
		int colSelection = -1;
		int rowSelection = -1;
		bool isInvalid = true;

		do {
			try {
				cout << Piece() << " Player's Turn" << endl;
				cout << "Please input empty location column Number : 1-3" << endl;
				if (!(cin >> colSelection)) {
					throw new exception();
				}

				cout << "Please input empty location row Number: 1-3" << endl;
				if (!(cin >> rowSelection)) {
					throw new exception();
				}

				isInvalid = (colSelection > 4 || colSelection < 1 || rowSelection > 4 || rowSelection < 1
					|| !board->AddPieceToBoard(Piece(), rowSelection,colSelection ));
			}
			catch (...) {
				while (cin.fail()) {
					cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
		} while (isInvalid);
	}
}