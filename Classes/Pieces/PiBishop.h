#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "cocos2d.h"
#include "Piece.h"
USING_NS_CC;
using namespace std;

class Bishop: public Piece{

public:
	Bishop();
	static  Bishop* create();
	virtual std::vector<Vec2> getAreaOfMove();
	virtual std::vector<Vec2> getAreaOfAttack();
	virtual char* getTypeOfPiece();
};

#endif //__BISHOP_H__