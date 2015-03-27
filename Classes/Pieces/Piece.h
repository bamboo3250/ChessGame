#ifndef __PIECE_H__
#define __PIECE_H__
#include "cocos2d.h"
#include "MapChess.h"
#include "Skills\Skill.h"
#include "Player.h"
#include "vector"
#include "SpriteChess.h"
USING_NS_CC;
using namespace std;

class Player;
class MapChess;
class Skill;
class SpriteChess;

class Piece{
protected:
	static int expToLevel[101];
	static int count;
	static bool computeExpToLevel;
	SpriteChess *image;
	int id;
	int experience, level;
	int maxHP, currentHP, baseMaxHP, maxHPGrowth;
	int maxMana, currentMana, baseMana, manaGrowth;
	int baseAtk, atk, atkGrowth;
	int baseDef, def, defGrowth;
	int limitHeightOfAttack;
	std::vector<Skill* > listOfSkill;
	Vec2 position;
	int height;
	Player* owner;
	bool firstStep;

public:
	static void generateExpToLevel();
	void refresh();
	int getExp();
	int getLevel(int e);
	int getLevel();
	int getMaxHP();
	int getCurrentHP();
	double getPercentHP();
	int getMaxMana();
	int getCurrentMana();
	int getAtk();
	int getDef();
	Vec2 getPosition();
	void setPosition(Vec2 pos);
	int getHeight();
	void setHeight(int h);
	Player* getOwner();
	void setOwner(Player *p);
	virtual std::vector<Vec2> getAreaOfMove() = 0;
	virtual std::vector<Vec2> getAreaOfAttack() = 0;
	virtual char* getTypeOfPiece() = 0;
	void attack(Piece *target);
	int defend(int incomingAtk);
	void moveTo(Vec2 des,float waitTime);
	void addSprite(SpriteChess* img);
	vector<Vec2> BFS(Vec2 start, Vec2 des);
	void refreshOrder(Vec2 pos, int h);
	void die();
	bool isDied();
	void returnToPosWithImage(Vec2 pos);
	void setFirstStep(bool b);
	int getDamage(Piece* target);
};
#endif //__PIECE_H__