#include "Player.h"
#include "Pieces\PiPawn.h"
#include "Pieces\PiRook.h"
#include "Pieces\PiBishop.h"
#include "Pieces\PiKnight.h"
#include "Pieces\PiKing.h"
#include "Pieces\PiQueen.h"
#include "MapChess.h";

int Player::count = 0;

Player::Player(){
	count++;
	id = count;
	if (id==1)	username = "White Player";
	else username = "Black Player";

	//username = __String::createWithFormat("Player %d", id)->getCString();
}

Player* Player::createPlayer(){
	Player *player = new Player();
	return player;
}

void Player::setSide(int s){
	side = s;
}

int Player::getSide(){
	return side;
}

void Player::addAllPieces(){
	for(int i=0;i<8;i++){
		Pawn* p = Pawn::create();
		if (side==0) addPiece(p,Vec2(6,i));
		else addPiece(p,Vec2(1,i));
	}
	for(int i=0;i<8;i+=7){
		Rook* p = Rook::create();
		if (side==0) addPiece(p,Vec2(7,7-i));
		else addPiece(p,Vec2(0,7-i));
	}
	for(int i=1;i<7;i+=5){
		Knight* p = Knight::create();
		if (side==0) addPiece(p,Vec2(7,7-i));
		else addPiece(p,Vec2(0,7-i));
	}
	for(int i=2;i<6;i+=3){
		Bishop* p = Bishop::create();
		if (side==0) addPiece(p,Vec2(7,7-i));
		else addPiece(p,Vec2(0,7-i));
	}
	Queen* q = Queen::create();
	if (side==0) addPiece(q,Vec2(7,3));
	else addPiece(q,Vec2(0,4));
	King* k = King::create();
	if (side==0) addPiece(k,Vec2(7,4));
	else addPiece(k,Vec2(0,3));

}

void Player::addPiece(Piece *piece, Vec2 pos){
	listOfPieces.push_back(piece);
	piece->setPosition(pos);
	piece->setHeight(MapChess::getHeight(pos));
	MapChess::setOccupied(pos,true);
	piece->setOwner(this);
}

int Player::getNumPieces(){
	return listOfPieces.size();
}

Piece* Player::getPiece(int u){
	return listOfPieces.at(u);
}

CCString Player::getUserName(){
	return username;
}