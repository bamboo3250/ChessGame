#ifndef __PAWN_H__
#define __PAWN_H__
#include "cocos2d.h"
#include "Piece.h"
USING_NS_CC;
using namespace std;

class Pawn: public Piece{

public:
	Pawn();
	static Pawn* create();
	virtual std::vector<Vec2> getAreaOfMove();
	virtual std::vector<Vec2> getAreaOfAttack();
	virtual char* getTypeOfPiece();
};

#endif //__KING_H__