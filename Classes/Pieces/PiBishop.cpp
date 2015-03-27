#include "PiBishop.h"

Bishop::Bishop(){
	limitHeightOfAttack = 3;
	experience = 4321;
	
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

Bishop* Bishop::create(){
	Bishop* p = new Bishop();
	return p;
}

std::vector<Vec2> Bishop::getAreaOfMove(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[4] = {Vec2(1,1),Vec2(1,-1),Vec2(-1,1),Vec2(-1,-1)};
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

std::vector<Vec2> Bishop::getAreaOfAttack(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[4] = {Vec2(1,1),Vec2(1,-1),Vec2(-1,1),Vec2(-1,-1)};
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

char* Bishop::getTypeOfPiece(){
	return "Bishop";
}
