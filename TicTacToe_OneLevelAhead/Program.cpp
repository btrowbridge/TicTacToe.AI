#pragma once

/*
Fall 2016 CAP4630 Artificial Intelligence
Assignment 3
Purpose: a tic tac toe game with ai
*/

#include "pch.h"
#include "Game.h"
#include <memory>

using namespace std;
using namespace TicTacToe;


int main(int argn, char* argv) {
	UNREFERENCED_PARAMETER(argn);
	UNREFERENCED_PARAMETER(argv);

	auto game = make_unique<Game>();

	game->Initialize();

	game->Run();
}