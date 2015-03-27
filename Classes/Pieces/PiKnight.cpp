#include "PiKnight.h"

Knight::Knight(){
	limitHeightOfAttack = 5;
	experience = 5555;
	
	baseAtk = 1000;
	atkGrowth = 50;
	
	baseDef = 800;
	defGrowth = 30;
	
	baseMaxHP = 800;
	maxHPGrowth = 40;
	
	baseMana = 600;
	manaGrowth = 40;

	this->refresh();
	currentHP = maxHP;
	currentMana = maxMana;
	id = count++;
}

Knight* Knight::create(){
	Knight* p = new Knight();
	return p;
}

std::vector<Vec2> Knight::getAreaOfMove(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[8] = {Vec2(2,1),Vec2(1,2),Vec2(-2,1),Vec2(1,-2),
				Vec2(2,-1),Vec2(-1,2),Vec2(-2,-1),Vec2(-1,-2)};
	for(int k=0;k<8;k++){
		Vec2 p = curPos+h[k];
		if ((0<=p.x) && (p.x<MapChess::getRow()) && (0<=p.y) && (p.y<MapChess::getCol()) && (!MapChess::getOccupied(p))) res.push_back(p);
	}
	return res;
}

std::vector<Vec2> Knight::getAreaOfAttack(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[8] = {Vec2(2,1),Vec2(1,2),Vec2(-2,1),Vec2(1,-2),
				Vec2(2,-1),Vec2(-1,2),Vec2(-2,-1),Vec2(-1,-2)};
	for(int k=0;k<8;k++){
		Vec2 p = curPos;
		p += h[k];
		if ((0<=p.x) && (p.x<MapChess::getRow()) && (0<=p.y) && (p.y<MapChess::getCol()) 
			&& (abs(MapChess::getHeight(p-h[k]) - MapChess::getHeight(curPos))<=limitHeightOfAttack)) res.push_back(p);
	}
	return res;
}

char* Knight::getTypeOfPiece(){
	return "Knight";
}