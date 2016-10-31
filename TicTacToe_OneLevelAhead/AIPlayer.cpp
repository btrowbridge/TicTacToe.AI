#include "pch.h"


using namespace std;

namespace TicTacToe {
	const int mMaxDepth = 2;
	AIPlayer::AIPlayer(const char piece, Game* game) : Player(piece,game), mOtherPlayer(mGame->GetOtherPlayer(this)), mCopyBoard()
	{
	}
	void AIPlayer::MakeMove(GameBoard * board)
	{
		MinimaxResult result = { 0 };
		do {
			UpdateCopyBoard(board);
			result = Minimax(mMaxDepth, mPiece);
			
		} while (!board->AddPieceToBoard(mPiece,result.Row,result.Col));
		
	}

	void AIPlayer::UpdateCopyBoard(const GameBoard* board)
	{
		mCopyBoard = make_unique<GameBoard>(board);
	}

	AIPlayer::MinimaxResult AIPlayer::Minimax(int depth, char player){
		// Generate possible next moves in a List of int[2] of {row, col}.
		std::vector<pair<int, int>> nextMoves = mCopyBoard->GetAvailableMoves();

		// mPiece is maximizing; while mOtherPlayer->Piece() is minimizing
		MinimaxResult result = { 0 };

		result.Score = (player == mPiece) ? INT_MIN : INT_MAX;

		int currentScore;

		if (nextMoves.empty() || depth == 0) {
			// Gameover or depth reached, Evaluate score
			result.Score = Evaluate();
		}
		else {
			for (auto move : nextMoves) {
				// Try this move for the current "player"
				mCopyBoard->AddPieceToBoard(mPiece, move.first, move.second);
				if (player == mPiece) {  // mPiece (computer) is maximizing player
					currentScore = Minimax(depth - 1, mOtherPlayer->Piece()).Score;
					if (currentScore > result.Score) {
						result.Score = currentScore;
						result.Row = move.first;
						result.Col = move.second;
					}
				}
				else {  // mOtherPlayer->Piece() is minimizing player
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

	int AIPlayer::Evaluate() {
      int score = 0;
      // Evaluate score for each of the 8 lines (3 rows, 3 columns, 2 diagonals)
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

	int AIPlayer::EvaluateLine(int row1, int col1, int row2, int col2, int row3, int col3)
	{
		int score = 0;
 
      // First cell
      if (mCopyBoard->At(row1,col1) == mPiece) {
         score = 1;
      } else if (mCopyBoard->At(row1,col1) == mOtherPlayer->Piece()) {
         score = -1;
      }
 
      // Second cell
      if (mCopyBoard->At(row2,col2) == mPiece) {
         if (score == 1) {   // cell1 is mPiece
            score = 10;
         } else if (score == -1) {  // cell1 is mOtherPlayer->Piece()
            return 0;
         } else {  // cell1 is empty
            score = 1;
         }
      } else if (mCopyBoard->At(row2,col2) == mOtherPlayer->Piece()) {
         if (score == -1) { // cell1 is mOtherPlayer->Piece()
            score = -10;
         } else if (score == 1) { // cell1 is mPiece
            return 0;
         } else {  // cell1 is empty
            score = -1;
         }
      }
 
      // Third cell
      if (mCopyBoard->At(row3,col3) == mPiece) {
         if (score > 0) {  // cell1 and/or cell2 is mPiece
            score *= 10;
         } else if (score < 0) {  // cell1 and/or cell2 is mOtherPlayer->Piece()
            return 0;
         } else {  // cell1 and cell2 are empty
            score = 1;
         }
      } else if (mCopyBoard->At(row3,col3) == mOtherPlayer->Piece()) {
         if (score < 0) {  // cell1 and/or cell2 is mOtherPlayer->Piece()
            score *= 10;
         } else if (score > 1) {  // cell1 and/or cell2 is mPiece
            return 0;
         } else {  // cell1 and cell2 are empty
            score = -1;
         }
      }
      return score;
	}

}