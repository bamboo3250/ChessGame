#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "cocos2d.h"
#include "Piece.h"
USING_NS_CC;
using namespace std;

class Knight: public Piece{

public:
	Knight();
	static Knight* create();
	virtual std::vector<Vec2> getAreaOfMove();
	virtual std::vector<Vec2> getAreaOfAttack();
	virtual char* getTypeOfPiece();
};

#endif //__BISHOP_H__