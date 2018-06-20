#include"stdafx.h"

#include<fstream>
#include<string>
#include<iostream>
#include<Windows.h>

#include"Game.h"
#include"Windows.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

Board& Game::getPlayer1Board()
{
	return player1Board_;
}



Board& Game::getPlayer2Board()
{
	return player2Board_;
}



void Game::loadTheBoard()
{
	int					a;
	vector<vector<int>> position;
	fstream				plik;
	string				nazwa_pliku = "Player1.txt";

	position.resize(10);
	for (int i = 0; i < 10; i++)
		position[i].resize(10);
	
	plik.open(nazwa_pliku.c_str());
	if (plik.is_open()) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				plik >> position[i][j];
		}
	}
	else {
		cout << "Nie mozna otworzyc pliku" << endl;
		return;
	}
	plik.close();
	player1Board_ = Board(position);

	nazwa_pliku = "Player2.txt";
	plik.open(nazwa_pliku.c_str());
	if (plik.is_open()) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				plik >> position[i][j];
		}
	}
	else {
		cout << "Nie mozna otworzyc pliku" << endl;
		return;
	}
	plik.close();
	player2Board_ = Board(position);
}



void Game::player1Turn()
{
	cout << "\t\t\t\t\t"<<player1Board_.getName()<<"'s turn\n\n" << endl;
	cout << player1Board_ << endl;
	cout << "Enemy ships:" << endl;
	for (auto it = player2Board_.getShips().begin(); it != player2Board_.getShips().end(); it++)
		cout << *it;
	cout << "Your ships:" << endl;
	for (auto it = player1Board_.getShips().begin(); it != player1Board_.getShips().end(); it++)
		cout << *it;
	takeCoordinates(player1Board_, player2Board_);
	system("cls");
	cout << "\t\t\t\t\t" << player1Board_.getName() << "'s turn\n\n" << endl;
	cout << player1Board_ << endl;
	cout << "Enemy ships:" << endl;
	for (auto it = player2Board_.getShips().begin(); it != player2Board_.getShips().end(); it++)
		cout << *it;
	cout << "Your ships:" << endl;
	for (auto it = player1Board_.getShips().begin(); it != player1Board_.getShips().end(); it++)
		cout << *it;
	Sleep(3000);
	system("cls");
	if (player1Board_.getHit() == 0)
		cout << "Swap places with your enemy" << endl;
	else
		cout << "You can shoot again" << endl;
	Sleep(3000);
	system("cls");
}



void Game::player2Turn()
{
	cout << "\t\t\t\t\t"<<player2Board_.getName()<<"'s turn\n\n" << endl;
	cout << player2Board_ << endl;
	cout << "Enemy ships:" << endl;
	for (auto it = player1Board_.getShips().begin(); it != player1Board_.getShips().end(); it++)
		cout << *it;
	cout << "Your ships:" << endl;
	for (auto it = player2Board_.getShips().begin(); it != player2Board_.getShips().end(); it++)
		cout << *it;
	takeCoordinates(player2Board_, player1Board_);
	system("cls");
	cout << "\t\t\t\t\t" << player2Board_.getName() << "'s turn\n\n" << endl;
	cout << player2Board_ << endl;
	cout << "Enemy ships:" << endl;
	for (auto it = player1Board_.getShips().begin(); it != player1Board_.getShips().end(); it++)
		cout << *it;
	cout << "Your ships:" << endl;
	for (auto it = player2Board_.getShips().begin(); it != player2Board_.getShips().end(); it++)
		cout << *it;
	Sleep(3000);
	system("cls");
	if (player2Board_.getHit() == 0)
		cout << "Swap places with your enemy" << endl;
	else
		cout << "You can shoot again" << endl;
	Sleep(3000);
	system("cls");
}



void Game::letsPlay()
{
	string a, b;
	
	cout << "Welcome sailors. Give me your names, so I can forget them." << endl;
	cout << "Player 1's name: ";
	cin >> a;
	player1Board_.setName(a);
	cout << "Player 2's name: ";
	cin >> b;
	player2Board_.setName(b);
	cout << "Let's get started! " << player1Board_.getName() <<	", you're up. Let's give "<<
		player2Board_.getName()<<" a few seconds to leave us alone." << endl;
	Sleep(5000);
	system("cls");
	while (true) {
		do {
			player1Turn();
			if (checkShips(player2Board_) == 0) {
				cout << "Bravo! You won! Who's the best sailor in the world? You are, " <<
					player1Board_.getName() << "!" << endl;
				return;
			}
		} while (player1Board_.getHit() == 1);

		do {
			player2Turn();
			if (checkShips(player1Board_) == 0) {
				cout << "Bravo! You won! Who's the best sailor in the world? You are, " <<
					player2Board_.getName() << "!" << endl;
				return;
			}
		} while (player2Board_.getHit() == 1);
	}
}



bool Game::checkShips(Board& player)
{
	for (auto it = player.getShips().begin(); it != player.getShips().end(); it++) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if (it->getCoordinates()[i][j] == 1)
					return 1;
			}
		}
	}
	return 0;
}



void Game::takeCoordinates(Board& me, Board& enemy)
{
	string	a;
	int		b, c, result;
	bool	isGood;
	
	do {
		cout << "Give the column's letter" << endl;
		do {
			cin >> a;
			isGood = a == "a" || a == "A" || a == "b" || a == "B" || a == "c" || a == "C" || a == "d" ||
				a == "D" || a == "e" || a == "E" || a == "f" || a == "F" || a == "g" || a == "G" ||
				a == "h" || a == "H" || a == "i" || a == "I" || a == "j" || a == "J";
			if (!isGood)
				cout << "There's no such column, choose again." << endl;
		} while (!isGood);
		cout << "Give the werse's number" << endl;
		do {
			cin >> b;
			isGood = b == 1 || b == 2 || b == 3 || b == 4 || b == 5 || b == 6 || b == 7 || b == 8 ||
				b == 9 || b == 10;
			if (!isGood)
				cout << "There's no such werse, choose again." << endl;
		} while (!isGood);

		if (a == "a" || a == "A")
			c = 1;
		if (a == "b" || a == "B")
			c = 2;
		if (a == "c" || a == "C")
			c = 3;
		if (a == "d" || a == "D")
			c = 4;
		if (a == "e" || a == "E")
			c = 5;
		if (a == "f" || a == "F")
			c = 6;
		if (a == "g" || a == "G")
			c = 7;
		if (a == "h" || a == "H")
			c = 8;
		if (a == "i" || a == "I")
			c = 9;
		if (a == "j" || a == "J")
			c = 10;

		if (me.getShoots_board()[b][c] != 0) {
			cout << "You have already shot this place. You drink too much rum, or what?" << endl;
			PlaySound(TEXT("Hangover.wav"), NULL, SND_FILENAME);
		}
	} while (me.getShoots_board()[b][c] != 0);
	result = enemy.shoot(b, c);
	if (result == 0) {
		me.setShoots_board(b, c, 2);
		me.setHit(0);
		cout << "Miss! Better luck next time." << endl;
		PlaySound(TEXT("Pudlo.wav"), NULL, SND_FILENAME);
	}
	else if (result == 1) {
		me.setShoots_board(b, c, 1);
		me.setHit(1);
		cout << "Good job, you hit it!" << endl;
		PlaySound(TEXT("Trafiony.wav"), NULL, SND_FILENAME);
	}
	else if (result == 2) {
		me.setShoots_board(b, c, 3);
		me.setHit(1);
		cout << "Woah! You got it! The ship drowned!" << endl;
		PlaySound(TEXT("Zatopiony.wav"), NULL, SND_FILENAME);
	}
	drownThem(me, enemy);
}



void Game::drownThem(Board& me, Board& enemy)
{
	int drowned;

	for (auto it = enemy.getShips().begin(); it != enemy.getShips().end(); it++) {
		drowned = 1;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if (it->getCoordinates()[i][j] == 1)
					drowned = 0;
			}
		}
		if (drowned == 1) {
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 12; j++) {
					if (it->getCoordinates()[i][j] == 2)
						me.setShoots_board(i, j, 3);
				}
			}
		}
	}
}



Game::Game()
{
	loadTheBoard();
}