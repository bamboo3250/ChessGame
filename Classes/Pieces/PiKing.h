#ifndef __KING_H__
#define __KING_H__
#include "cocos2d.h"
#include "Piece.h"
USING_NS_CC;
using namespace std;

class King: public Piece{

public:
	King();
	static King* create();
	virtual std::vector<Vec2> getAreaOfMove();
	virtual std::vector<Vec2> getAreaOfAttack();
	virtual char* getTypeOfPiece();
};

#endif //__KING_H__