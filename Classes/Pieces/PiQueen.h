#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "cocos2d.h"
#include "Piece.h"
USING_NS_CC;
using namespace std;

class Queen: public Piece{

public:
	Queen();
	static Queen* create();
	virtual std::vector<Vec2> getAreaOfMove();
	virtual std::vector<Vec2> getAreaOfAttack();
	virtual char* getTypeOfPiece();
};

#endif //__QUEEN_H__