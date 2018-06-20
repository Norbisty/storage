#include"stdafx.h"

#include<string>
#include<vector>
#include<map>

using namespace std;

class Ship
{

public:
	string& getType();
	void setType(string);

	vector<vector<int>>& getCoordinates();
	void setCoordinates(int, int, int);

	bool isDrowned();
	bool isHit();
	void shootIt(Ship, int, int);

	Ship();
	Ship(int, int);
	Ship(int, int, int, int);
	Ship(int, int, int, int, int, int);
	Ship(int, int, int, int, int, int, int, int);

	friend ostream& operator<<(ostream& o, Ship& s);

private:
	string type_;
	vector<vector<int>> coordinates_;
};

#pragma once
