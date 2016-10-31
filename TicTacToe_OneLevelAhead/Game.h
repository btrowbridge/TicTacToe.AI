#pragma once
#include <memory>

namespace TicTacToe {
	class Player;
	class GameBoard;
	class AIPlayer;

	class Game
	{
	public:
		Game();

		const Player* GetOtherPlayer(const Player* player) const;
		Player* GetOtherPlayer(const Player* player);
		~Game() = default;

		const GameBoard* GetBoard() const;

		void Initialize();

		void Run();

	private:

		std::shared_ptr<Player> mPlayer1;
		std::shared_ptr<AIPlayer> mPlayer2;
		std::shared_ptr<GameBoard> mBoard;

		int mMoveCount;
	};
}