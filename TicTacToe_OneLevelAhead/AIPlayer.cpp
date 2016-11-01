#include "pch.h"
#include "AIPlayer.h"

using namespace std;

namespace TicTacToe {

	const int AIPlayer::mMaxDepth = 9;
	const int AIPlayer::mDefaultAlpha = INT_MIN;
	const int AIPlayer::mDefaultBeta = INT_MAX;

	AIPlayer::AIPlayer(const char piece, Game& game) : Player(piece, game), mOtherPlayer(), mCopyBoard(make_shared<GameBoard>(game))
	{
	}
	void AIPlayer::MakeMove(GameBoard * board)
	{	

		mOtherPlayer = mGame.GetOtherPlayer(this);
		MinimaxResult result = { 0 };		
		UpdateCopyBoard(*board);

		cout << "Thinking..." << endl;
		result = MinimaxWithAlphaBeta(mMaxDepth, mPiece, mDefaultAlpha, mDefaultBeta);

		board->AddPieceToBoard(mPiece, result.Row, result.Col);
		cout << "Computer choses (" << result.Col + 1 << "," << result.Row + 1 << ") with a minimax score of " << result.Score + 1 << endl;

	}

	void AIPlayer::UpdateCopyBoard(const GameBoard board)
	{
		mCopyBoard->Copy(board);		
	}

	AIPlayer::MinimaxResult AIPlayer::Minimax(int depth, char player) {
		// Generate possible next moves in a vector of pairs
		std::vector<std::pair<int, int>> nextMoves = mCopyBoard->GetAvailableMoves();

		// mPiece is maximizing while mOtherPlayer->Piece() is minimizing
		MinimaxResult result = { 0 };
		result.Row = -1;
		result.Col = -1;
		result.Score = (player == mPiece) ? INT_MIN : INT_MAX;

		int currentScore;

		if (nextMoves.empty() || depth == 0) {
			// Gameover or depth reached, Evaluate score
			result.Score = Evaluate();
			return result;
		}
		else {
			for (auto move : nextMoves) {
				// Try this move 
				mCopyBoard->AddPieceToBoard(player, move.first + 1, move.second + 1);

				if (player == mPiece) {  // max player
					currentScore = Minimax(depth - 1, mOtherPlayer->Piece()).Score;
					if (currentScore > result.Score) {
						result.Score = currentScore;
						result.Row = move.first;
						result.Col = move.second;
					}
				}
				else {  // min player
					currentScore = Minimax(depth - 1, mPiece).Score;
					if (currentScore < result.Score) {
						result.Score = currentScore;
						result.Row = move.first;
						result.Col = move.second;
					}
				}
				// Undo move
				mCopyBoard->RemoveAt(move.first, move.second);
			}
			
		}
		return result;
	}

	AIPlayer::MinimaxResult AIPlayer::MinimaxWithAlphaBeta(int depth, char player, int alpha, int beta)
	{
		// Generate possible next moves in a vector of pairs
		std::vector<std::pair<int, int>> nextMoves = mCopyBoard->GetAvailableMoves();

		// mPiece is maximizing; while mOtherPlayer->Piece() is minimizing
		MinimaxResult result = { 0 };
		result.Row = -1;
		result.Col = -1;
		result.Score = (player == mPiece) ? INT_MIN : INT_MAX;

		int currentScore;

		if (nextMoves.empty() || depth == 0) {
			// Gameover or depth reached, Evaluate score
			result.Score = Evaluate();
			return result;
		}
		else {
			for (auto move : nextMoves) {
				//Try move
				mCopyBoard->AddPieceToBoard(player, move.first, move.second);
				if (player == mPiece) {  // max player
					currentScore = MinimaxWithAlphaBeta(depth - 1, mOtherPlayer->Piece(), alpha, beta).Score;
					if (currentScore > alpha) {
						alpha = currentScore;
						result.Row = move.first;
						result.Col = move.second;
					}
				}
				else {  // min player
					currentScore = MinimaxWithAlphaBeta(depth - 1, mPiece, alpha, beta).Score;
					if (currentScore < beta) {
						beta = currentScore;
						result.Row = move.first;
						result.Col = move.second;
					}
				}
				// Undo move
				mCopyBoard->RemoveAt(move.first, move.second);

				if (alpha >= beta) break; //break point
			}

		}
		result.Score = (player == mPiece) ? alpha : beta;
		return result;
	}


	int AIPlayer::Evaluate() {
		int score = 0;
		// Evaluate score for each line
		score += EvaluateLine(0, 0, 0, 1, 0, 2);  // row 0
		score += EvaluateLine(1, 0, 1, 1, 1, 2);  // row 1
		score += EvaluateLine(2, 0, 2, 1, 2, 2);  // row 2
		score += EvaluateLine(0, 0, 1, 0, 2, 0);  // col 0
		score += EvaluateLine(0, 1, 1, 1, 2, 1);  // col 1
		score += EvaluateLine(0, 2, 1, 2, 2, 2);  // col 2
		score += EvaluateLine(0, 0, 1, 1, 2, 2);  // diagonal
		score += EvaluateLine(0, 2, 1, 1, 2, 0);  // alternate diagonal
		return score;
	}

	//Evaluates a line and gives negative values for opponent being located there.
	int AIPlayer::EvaluateLine(int row1, int col1, int row2, int col2, int row3, int col3)
	{
		int score = 0;

		// First cell
		if (mCopyBoard->At(row1, col1) == mPiece) {
			score = 1;
		}
		else if (mCopyBoard->At(row1, col1) == mOtherPlayer->Piece()) {
			score = -1;
		}

		// Second cell
		if (mCopyBoard->At(row2, col2) == mPiece) {
			if (score == 1) {   // cell1 is mPiece
				score = 10;
			}
			else if (score == -1) {  // cell1 is mOtherPlayer->Piece()
				return 0;
			}
			else {  // cell1 is empty
				score = 1;
			}
		}
		else if (mCopyBoard->At(row2, col2) == mOtherPlayer->Piece()) {
			if (score == -1) { // cell1 is mOtherPlayer->Piece()
				score = -10;
			}
			else if (score == 1) { // cell1 is mPiece
				return 0;
			}
			else {  // cell1 is empty
				score = -1;
			}
		}

		// Third cell
		if (mCopyBoard->At(row3, col3) == mPiece) {
			if (score > 0) {  // cell1 and/or cell2 is mPiece
				score *= 10;
			}
			else if (score < 0) {  // cell1 and/or cell2 is mOtherPlayer->Piece()
				return 0;
			}
			else {  // cell1 and cell2 are empty
				score = 1;
			}
		}
		else if (mCopyBoard->At(row3, col3) == mOtherPlayer->Piece()) {
			if (score < 0) {  // cell1 and/or cell2 is mOtherPlayer->Piece()
				score *= 10;
			}
			else if (score > 1) {  // cell1 and/or cell2 is mPiece
				return 0;
			}
			else {  // cell1 and cell2 are empty
				score = -1;
			}
		}
		return score;
	}
}