#include"stdafx.h"

#include<iostream>
#include<string>

#include"Board.h"

using namespace std;

vector<Ship>& Board::getShips()
{
	return ships_;
}



void Board::setShips(vector<Ship> ships)
{
	ships_ = ships;
}



vector<vector<int>>& Board::getShoots_board()
{
	return shoots_board_;
}



void Board::setShoots_board(int i, int j, int a)
{
	shoots_board_[i][j] = a;
}



vector<vector<bool>>& Board::getChecked()
{
	return checked_;
}



void Board::setChecked(vector<vector<bool>> checked)
{
	checked_ = checked;
}



string& Board::getName()
{
	return name_;
}



void Board::setName(string name)
{
	name_ = name;
}



bool Board::getHit()
{
	return hit_;
}



void Board::setHit(bool hit)
{
	hit_ = hit;
}



int Board::shoot(int i, int j)
{
	bool drowned = 1;

	for (auto it = ships_.begin(); it != ships_.end(); it++) {
		if (it->getCoordinates()[i][j] == 1) {
			it->setCoordinates(i, j, 2);
			for (int a = 0; a < 12; a++) {
				for (int b = 0; b < 12; b++) {
					if (it->getCoordinates()[a][b] == 1) {
						drowned = 0;
					}
				}
			}
			if (drowned) {
				return 2;
			}
			return 1;
		}
	}

	return 0;
}



void Board::locateShip(vector<vector<int>> array)
{
	int shipsNo = 0;

	ships_.resize(10);
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			if (array[i][j] == 1 && checked_[i][j] == 0) {
				if (lookFurther(array, i, j, 1) > 4) {
					cout << "Wrong ship location. Check files with the boards and try again" << endl;
					system("PAUSE");
					exit(0);
				}
				if (lookFurther(array, i, j, 1) == 4) {
					if (array[i][j + 1] == 1) {
						ships_[shipsNo] = Ship(i, j, i, j + 1, i, j + 2, i, j + 3);
						shipsNo++;
					}
					else if (array[i + 1][j] == 1) {
						ships_[shipsNo] = Ship(i, j, i + 1, j, i + 2, j, i + 3, j);
						shipsNo++;
					}
				}
				if (lookFurther(array, i, j, 1) == 3) {
					if (array[i][j + 1] == 1) {
						ships_[shipsNo] = Ship(i, j, i, j + 1, i, j + 2);
						shipsNo++;
					}
					else if (array[i + 1][j] == 1) {
						ships_[shipsNo] = Ship(i, j, i + 1, j, i + 2, j);
						shipsNo++;
					}
				}
				if (lookFurther(array, i, j, 1) == 2) {
					if (array[i][j + 1] == 1) {
						ships_[shipsNo] = Ship(i, j, i, j + 1);
						shipsNo++;
					}
					else if (array[i + 1][j] == 1) {
						ships_[shipsNo] = Ship(i, j, i + 1, j);
						shipsNo++;
					}
				}
				if (lookFurther(array, i, j, 1) == 1) {
					ships_[shipsNo] = Ship(i, j);
					shipsNo++;
				}
			}
		}
	}
	if (shipsNo != 10){
		cout << "The number of ships must be 10" << endl;
		system("PAUSE");
		exit(0);
	}
}



int Board::lookFurther(vector<vector<int>> array, int i, int j, int a)
{
	bool isCrossed = array[i - 1][j - 1] == 1 || array[i - 1][j + 1] == 1 || array[i + 1][j - 1] == 1 || array[i + 1][j + 1] == 1;
	if (isCrossed){
		cout << "Wrong ships location. Check the files with boards and try again" << endl;
		system("PAUSE");
		exit(0);
	}
	if (array[i][j + 1] == 1) {
		a++;
		a = lookFurther(array, i, j + 1, a);
	}
	if (array[i + 1][j] == 1) {
		a++;
		a = lookFurther(array, i + 1, j, a);
	}
	checked_[i][j] = 1;
	return a;
}



Board::Board()
{
	shoots_board_.resize(12);
	for (int i = 0; i < 12; i++)
		shoots_board_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			shoots_board_[i][j] = 0;
		}
	}
	checked_.resize(12);
	for (int i = 0; i < 12; i++)
		checked_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			checked_[i][j] = 0;
		}
	}
}



Board::Board(vector<vector<int>> position)
{
	bool				isEdge;
	vector<vector<int>>	big;

	shoots_board_.resize(12);
	for (int i = 0; i < 12; i++)
		shoots_board_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			shoots_board_[i][j] = 0;
		}
	}
	checked_.resize(12);
	for (int i = 0; i < 12; i++)
		checked_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			checked_[i][j] = 0;
		}
	}

	big.resize(12);
	for (int i = 0; i < 12; i++)
		big[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			isEdge = i == 0 || i == 11 || j == 0 || j == 11;
			if (isEdge)
				big[i][j] = 0;
			else
				big[i][j] = position[i - 1][j - 1];
		}
	}
	
	locateShip(big);

}



ostream& operator<<(ostream& o, Board& b)
{
	string a = "\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ\n\n";

	for (int i = 1; i < 11; i++) {
		if (i == 1)
			a += "1";
		if (i == 2)
			a += "2";
		if (i == 3)
			a += "3";
		if (i == 4)
			a += "4";
		if (i == 5)
			a += "5";
		if (i == 6)
			a += "6";
		if (i == 7)
			a += "7";
		if (i == 8)
			a += "8";
		if (i == 9)
			a += "9";
		if (i == 10)
			a += "10";
		a += "\t";
		for (int j = 1; j < 11; j++) {
			if (b.shoots_board_[i][j] == 0)
				a += "~";
			else if (b.shoots_board_[i][j] == 1)
				a += "X";
			else if (b.shoots_board_[i][j] == 2)
				a += "o";
			else if (b.shoots_board_[i][j] == 3)
				a += "#";
			a += "\t";
		}
		a += "\n\n";
	}
	return o << a << endl;
}