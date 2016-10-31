#include "pch.h"
#include "Game.h"

using namespace std;

namespace TicTacToe {
	Game::Game() : mBoard(), mPlayer1(), mPlayer2(), mMoveCount(0)
	{
	}

	const Player * Game::GetOtherPlayer(const Player * player) const
	{
		return (player == mPlayer1.get()) ? mPlayer2.get() : mPlayer1.get();
	}
	Player * Game::GetOtherPlayer(const Player * player)
	{
		return (player == mPlayer1.get()) ? mPlayer2.get() : mPlayer1.get();
	}

	const GameBoard * Game::GetBoard() const
	{
		return mBoard.get();
	}

	void Game::Initialize()
	{
		mPlayer1 = make_shared<Player>('X', *this);
		mPlayer2 = make_shared<AIPlayer>('O', *this);
		mBoard = make_shared<GameBoard>(*this);
	}
	void Game::Run()
	{
		Player * playerTurn = mPlayer1.get();
		bool playingGame = true;

		while (playingGame) {
			mBoard->ClearBoard();
			mMoveCount = 0;
			while ((mMoveCount < 9))
			{
				mBoard->DisplayBoard();

				playerTurn->MakeMove(mBoard.get());
				mMoveCount++;

				if (mBoard->CheckWin(playerTurn) || mMoveCount == 9) {
					mBoard->DisplayBoard();
					mBoard->DisplayWinner(mPlayer1.get(), mPlayer2.get());
					break;
				}
				playerTurn = GetOtherPlayer(playerTurn);
			}
			char result = 'N';
			try {
				cout << "Play Again? Y/N" << endl;
				if (!(cin >> result)) {
					throw new exception();
				}
			}
			catch (...) {
				while (cin.fail()) {
					cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				break;
			}
			playingGame = (result == 'Y' || result == 'y');
		}
	}
}