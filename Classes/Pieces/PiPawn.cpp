#include "PiPawn.h"

Pawn::Pawn(){
	limitHeightOfAttack = 3;
	experience = 6666;
	
	baseAtk = 1200;
	atkGrowth = 50;
	
	baseDef = 600;
	defGrowth = 20;
	
	baseMaxHP = 800;
	maxHPGrowth = 25;
	
	baseMana = 500;
	manaGrowth = 30;

	this->refresh();
	currentHP = maxHP;
	currentMana = maxMana;
	firstStep = true;
	id = count++;
}

Pawn* Pawn::create(){
	Pawn* p = new Pawn();
	return p;
}

std::vector<Vec2> Pawn::getAreaOfMove(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h = Vec2(1,0);
	
	Vec2 p = curPos;
	if (this->getOwner()->getSide()==0) h = Vec2::ZERO - h;
	p += h;

	if ((0<=p.x) && (p.x<MapChess::getRow()) && (0<=p.y) && (p.y<MapChess::getCol()) && (!MapChess::getOccupied(p))) res.push_back(p);
	
	p += h;
	if ((0<=p.x) && (p.x<MapChess::getRow()) && (0<=p.y) && (p.y<MapChess::getCol()) 
		&& (MapChess::getHeight(p-h) >= MapChess::getHeight(p)) 
		&& firstStep && (!MapChess::getOccupied(p-h))  && (!MapChess::getOccupied(p))) res.push_back(p);
	return res;
}

std::vector<Vec2> Pawn::getAreaOfAttack(){
	Vec2 curPos = this->getPosition();
	std::vector<Vec2> res;
	Vec2 h[2] = {Vec2(1,1),Vec2(1,-1)};
	for(int k=0;k<2;k++){
		Vec2 p = curPos;
		if (this->getOwner()->getSide()==0) 
			p -= h[k];
		else 
			p += h[k];
		if ((0<=p.x) && (p.x<MapChess::getRow()) && (0<=p.y) && (p.y<MapChess::getCol()) 
			&& (abs(MapChess::getHeight(p-h[k]) - MapChess::getHeight(curPos))<=limitHeightOfAttack)){
			res.push_back(p);
			p += h[k];
		}
	}
	return res;
}

char* Pawn::getTypeOfPiece(){
	return "Pawn";
}