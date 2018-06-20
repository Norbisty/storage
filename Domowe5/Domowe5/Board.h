#include"stdafx.h"

#include<vector>
#include<map>
#include<string>

#include"Ship.h"

using namespace std;

class Board
{

public:
	vector<Ship>& getShips();
	void setShips(vector<Ship>);

	vector<vector<int>>& getShoots_board();
	void setShoots_board(int, int, int);

	vector<vector<bool>>& getChecked();
	void setChecked(vector<vector<bool>>);

	string& getName();
	void setName(string);

	bool getHit();
	void setHit(bool);

	int shoot(int, int);
	void locateShip(vector<vector<int>>);
	int lookFurther(vector<vector<int>> array, int i, int j, int a);

	friend ostream& operator<<(ostream&, Board&);

	Board();
	Board(vector<vector<int>>);

private:
	vector<Ship> ships_;
	vector<vector<int>> shoots_board_;
	vector<vector<bool>> checked_;
	string name_;
	bool hit_;
};

#pragma once
