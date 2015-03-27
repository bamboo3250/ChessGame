#ifndef __SPRITE_CHESS_H__
#define __SPRITE_CHESS_H__

#include "cocos2d.h"
#include "MapChess.h"
#include "Pieces\Piece.h"
USING_NS_CC;

class Piece;
class SpriteChess: public Sprite{
private: 
	Piece* piece;

public:
	virtual void update(float delta) override;
	static SpriteChess* SpriteChess::create(const std::string& filename);
	void setPiece(Piece* p);
};

#endif //__SPRITE_CHESS_H__