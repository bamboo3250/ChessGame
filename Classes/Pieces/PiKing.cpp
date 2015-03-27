#include "PiKing.h"

King::King(){
	limitHeightOfAttack = 3;
	experience = 3333;
	
	baseAtk = 800;
	atkGrowth = 30;
	
	baseDef = 800;
	defGrowth = 30;
	
	baseMaxHP = 900;
	maxHPGrowth = 45;
	
	baseMana = 1000;
	manaGrowth = 50;

	this->refresh();
	currentHP = maxHP;
	currentMana = maxMana;
	id = count++;
}

King* King::create(){
	King* p = new King();
	return p;
}

std::vector<Vec2> King::getAreaOfMove(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[8] = {Vec2(1,1),Vec2(1,-1),Vec2(-1,1),Vec2(-1,-1),Vec2(0,1),Vec2(1,0),Vec2(-1,0),Vec2(0,-1)};
	for(int k=0;k<8;k++){
		Vec2 p = curPos;
		p += h[k];
		if ((0<=p.x) && (p.x<MapChess::getRow()) && (0<=p.y) && (p.y<MapChess::getCol() && (!MapChess::getOccupied(p))) 
			&& (MapChess::getHeight(p-h[k]) >= MapChess::getHeight(p))){
			res.push_back(p);
		}
	}
	return res;
}

std::vector<Vec2> King::getAreaOfAttack(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[8] = {Vec2(1,1),Vec2(1,-1),Vec2(-1,1),Vec2(-1,-1),Vec2(0,1),Vec2(1,0),Vec2(-1,0),Vec2(0,-1)};
	for(int k=0;k<8;k++){
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

char* King::getTypeOfPiece(){
	return "King";
}