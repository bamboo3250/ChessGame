#ifndef __SKILL_H__
#define __SKILL_H__
#include <cocos2d.h>
#include <MapChess.h>
#include "Pieces\Piece.h"
USING_NS_CC;

class Piece;

class Skill{
private:
	int level;
	int baseManaCost;
	int manaCost;
	int manaCostGrowth;
	int baseCd;
	int cd;
	int cdGrowth;
	int basePow;
	int pow;
	int powGrowth;
	
public:
	void refresh();
	virtual std::vector<Vec2> getAreaOfEffect(Piece* user);
	virtual void applyEffect(Piece* user, Piece* target);

};

#endif //__SKILL_H__