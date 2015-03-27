#include "PiRook.h"

Rook::Rook(){
	limitHeightOfAttack = 3;
	experience = 1234;
	
	baseAtk = 700;
	atkGrowth = 20;
	
	baseDef = 900;
	defGrowth = 50;
	
	baseMaxHP = 1000;
	maxHPGrowth = 50;
	
	baseMana = 500;
	manaGrowth = 10;

	this->refresh();
	currentHP = maxHP;
	currentMana = maxMana;
	id = count++;
}

Rook* Rook::create(){
	Rook* p = new Rook();
	return p;
}

std::vector<Vec2> Rook::getAreaOfMove(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[4] = {Vec2(0,1),Vec2(1,0),Vec2(-1,0),Vec2(0,-1)};
	for(int k=0;k<4;k++){
		Vec2 p = curPos;
		p += h[k];
		while ((0<=p.x) && (p.x<MapChess::getRow()) && (0<=p.y) && (p.y<MapChess::getCol()) 
			&& (MapChess::getHeight(p-h[k]) >= MapChess::getHeight(p)) && (!MapChess::getOccupied(p))){
			res.push_back(p);
			p += h[k];
		}
	}
	return res;
}

std::vector<Vec2> Rook::getAreaOfAttack(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[4] = {Vec2(0,1),Vec2(1,0),Vec2(-1,0),Vec2(0,-1)};
	for(int k=0;k<4;k++){
		Vec2 p = curPos;
		p += h[k];
		if ((0<=p.x) && (p.x<MapChess::getRow()) && (0<=p.y) && (p.y<MapChess::getCol()) 
			&& (abs(MapChess::getHeight(p-h[k]) - MapChess::getHeight(curPos))<=limitHeightOfAttack)){
			res.push_back(p);
			p += h[k];
		}
	}
	return res;
}

char* Rook::getTypeOfPiece(){
	return "Rook";
}