#ifndef __ROOK_H__
#define __ROOK_H__
#include "cocos2d.h"
#include "Piece.h"
USING_NS_CC;
using namespace std;

class Rook: public Piece{

public:
	Rook();
	static Rook* create();
	virtual std::vector<Vec2> getAreaOfMove();
	virtual std::vector<Vec2> getAreaOfAttack();
	virtual char* getTypeOfPiece();
};

#endif //__PIECE_H__