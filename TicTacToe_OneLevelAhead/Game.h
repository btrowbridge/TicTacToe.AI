#pragma once

#include "pch.h"

namespace TicTacToe {
	class Player;
	class GameBoard;

	class Game
	{
	public:
		Game();
		Game(GameBoard* board, Player* player1, Player* player2);
		
		const Player* GetOtherPlayer(const Player* player) const;
		Player* GetOtherPlayer(const Player* player);

		const GameBoard* GetBoard() const;

		void Initialize();

		void Run();

	private:

		std::shared_ptr<Player> mPlayer1;
		std::shared_ptr<Player> mPlayer2;
		std::shared_ptr<GameBoard> mBoard;

		int mMoveCount;
	};
}