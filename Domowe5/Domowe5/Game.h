#include"stdafx.h"

#include"Board.h"


class Game
{

public:
	Board& getPlayer1Board();

	Board& getPlayer2Board();

	void loadTheBoard();

	void player1Turn();
	void player2Turn();
	void letsPlay();

	void drownThem(Board&, Board&);
	bool checkShips(Board&);
	void takeCoordinates(Board&, Board&);

	Game();

private:
	Board player1Board_;
	Board player2Board_;

};

#pragma once
