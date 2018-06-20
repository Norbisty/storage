#include"stdafx.h"

#include<iostream>

#include"Ship.h"

using namespace std;

string& Ship::getType()
{
	return type_;
}



void Ship::setType(string type)
{
	type_ = type;
}



vector<vector<int>>& Ship::getCoordinates()
{
	return coordinates_;
}



void Ship::setCoordinates(int i, int j, int a)
{
	coordinates_[i][j] = a;
}



bool Ship::isDrowned()
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (coordinates_[i][j] == 1)
				return false;
		}
	}
	return true;
}



bool Ship::isHit()
{
	int b = 0;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (coordinates_[i][j] == 2)
				return true;
		}
	}
	return false;
}



void Ship::shootIt(Ship a, int i, int j)
{
	a.coordinates_[i][j] = 2;
}




Ship::Ship()
{
	type_ = "Szalupa ratunkowa";
	coordinates_.resize(12);
	for (int i = 0; i < 12; i++)
		coordinates_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++)
			coordinates_[i][j] = 0;
	}
}



Ship::Ship(int a, int b)
{
	type_ = "One-masted ship";
	coordinates_.resize(12);
	for (int i = 0; i < 12; i++)
		coordinates_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++)
			coordinates_[i][j] = 0;
	}
	coordinates_[a][b] = 1;
}



Ship::Ship(int a, int b, int c, int d)
{
	type_ = "Two-masted ship";
	coordinates_.resize(12);
	for (int i = 0; i < 12; i++)
		coordinates_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++)
			coordinates_[i][j] = 0;
	}
	coordinates_[a][b] = 1;
	coordinates_[c][d] = 1;
}



Ship::Ship(int a, int b, int c, int d, int e, int f)
{
	type_ = "Three-masted ship";
	coordinates_.resize(12);
	for (int i = 0; i < 12; i++)
		coordinates_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++)
			coordinates_[i][j] = 0;
	}
	coordinates_[a][b] = 1;
	coordinates_[c][d] = 1;
	coordinates_[e][f] = 1;
}



Ship::Ship(int a, int b, int c, int d, int e, int f, int g, int h)
{
	type_ = "Four-masted ship";
	coordinates_.resize(12);
	for (int i = 0; i < 12; i++)
		coordinates_[i].resize(12);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++)
			coordinates_[i][j] = 0;
	}
	coordinates_[a][b] = 1;
	coordinates_[c][d] = 1;
	coordinates_[e][f] = 1;
	coordinates_[g][h] = 1;
}

int shipNo = 1;

ostream& operator<<(ostream& o, Ship& s)
{
	string a = "";
	bool isTooBig;

	a += "Ship ";
	switch (shipNo){
	case 1 :
		a += "1";
		break;
	case 2 :
		a += "2";
		break;
	case 3 :
		a += "3";
		break;
	case 4 :
		a += "4";
		break;
	case 5 :
		a += "5";
		break;
	case 6 :
		a += "6";
		break;
	case 7 :
		a += "7";
		break;
	case 8 :
		a += "8";
		break;
	case 9 :
		a += "9";
		break;
	case 10 :
		a += "10";
		break;
	}
	a += ": ";
	a += s.type_;
	isTooBig = (s.type_ == "Three-masted ship" || s.type_ == "Four-masted ship") || (shipNo == 10 && (s.type_ == "One-masted ship" || s.type_ == "Two-masted ship"));
	if (isTooBig)
		a += "\t";
	else
		a += "\t\t";
	if (s.isHit())
		a += "Hit";
	else
		a += "Untouched";
	if (s.isDrowned())
		a += " and drowned";
	a += "\n";
	shipNo += 1;
	if (shipNo == 11)
		shipNo = 1;
	return o << a;
}