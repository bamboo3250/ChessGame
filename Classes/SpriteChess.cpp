#include "SpriteChess.h"

void SpriteChess::update(float delta){
	Vec2 imgSize = this->getContentSize();
	Vec2 mapPos = piece->getPosition();//MapChess::getMapPos(this->getPosition()-Vec2(0,imgSize.y/2-24));//piece->getPosition();
	this->setZOrder(MapChess::getPieceOrder(mapPos.x, mapPos.y, MapChess::getHeight(mapPos)));
	//this->setZOrder(0);
}

void SpriteChess::setPiece(Piece* p){
	piece = p;
}

SpriteChess* SpriteChess::create(const std::string& filename)
{
    SpriteChess *sprite = new (std::nothrow) SpriteChess();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}