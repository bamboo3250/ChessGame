#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include "MapChess.h"
#include "Pieces\Piece.h"
USING_NS_CC;

class Piece;

class Player{
private:
	static int count;
	int id;
	cocos2d::CCString username;
	int side;
	std::vector<Piece* > listOfPieces;
public:
	Player();
	static Player* createPlayer();
	void setSide(int s);
	int getSide();
	void addAllPieces();
	void addPiece(Piece* piece, Vec2 pos);
	int getNumPieces();
	Piece* getPiece(int u);
	CCString getUserName();
};

#endif //__PLAYER_H__