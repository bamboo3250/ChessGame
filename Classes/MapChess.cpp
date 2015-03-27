#include "cocos2d.h"
#include "MapChess.h"
#include <bamboo3250-function.h>
#include "SpriteChess.h"
USING_NS_CC;

int MapChess::height[20][20];
int MapChess::type[20][20];
bool MapChess::occupied[20][20];

Vec2 MapChess::focus;
Layer* MapChess::map;
int MapChess::row;
int MapChess::col;
Player *(MapChess::player1), *(MapChess::player2);
std::vector<Vec2> MapChess::areaOfEffect;
Piece* MapChess::preFocusedPiece;
Piece* MapChess::focusedPiece;
Piece* MapChess::actionPiece;
Piece* MapChess::actingPiece;
int MapChess::turn;
int MapChess::phrase;
LabelTTF* MapChess::labelDamage;

void MapChess::setMapPosition(Vec2 p){
	map->setPosition(p);
}

void MapChess::resetMap(){
	row = 8;
	col = 8;
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++) {
			height[i][j] = 0;
			type[i][j] = (i+j)%2;
			occupied[i][j] = false;
		}
	focus = Vec2(-1,-1);
	map = Layer::create();
	//MapChess::setZOrder(1);
	map->setTag(123);
	map->setScale(1);

	labelDamage = LabelTTF::create("","Arial",40);
	labelDamage->setPosition(Vec2::ZERO);
	labelDamage->setDimensions(Size(130,50));
	labelDamage->setColor(Color3B::RED);
	labelDamage->setOpacity(0);
	map->addChild(labelDamage,1000000001,1000000001);
	setPreFocusedPiece(NULL);
	turn = 0;
	phrase = 0;
}

void MapChess::refressMap(){
	map->removeAllChildren();
	MapChess::drawMap();

	setPreFocusedPiece(NULL);
	labelDamage = LabelTTF::create("","Arial",40);
	labelDamage->setPosition(Vec2::ZERO);
	labelDamage->setDimensions(Size(130,50));
	labelDamage->setColor(Color3B::RED);
	labelDamage->setOpacity(0);
	map->addChild(labelDamage,1000000001,1000000001);
}

int MapChess::getRow(){
	return row;
}

int MapChess::getCol(){
	return col;
}

void MapChess::setRow(int r){
	MapChess::row = r;
}

void MapChess::setCol(int c){
	MapChess::col = c;
}

Layer* MapChess::getMap(){
	return map;
}

Vec2 MapChess::getFocus(){
	return focus;
}

void MapChess::setFocus(Vec2 p){
	focus = p;
}

void MapChess::removeFocus(){
	map->removeChildByTag(999999999);
}

void MapChess::drawFocus(){
	if (focus.x>-1) MapChess::drawTile(999999999,MapChess::getPos(focus), (focus.x + focus.y)*100+getHeight(focus)*3+1,999999999);
}

void MapChess::drawAreaOfEffect(std::vector<Vec2> AreaOfEffect){
	for(int i=0;i<AreaOfEffect.size();i++){
		Vec2 pos = AreaOfEffect.at(i);
		MapChess::drawTile(999999998,MapChess::getPos(pos), (pos.x + pos.y)*100 + getHeight(pos)*3 +1,999999998);
	}
}

void MapChess::removeAreaOfEffect(){
	int count;
	do{	
		count = map->getChildrenCount();
		map->removeChildByTag(999999998);
	} while (count > map->getChildrenCount());
}

void MapChess::drawActing(){
	if (MapChess::getActingPiece()!=NULL){
		Vec2 pos = MapChess::getActingPiece()->getPosition();
		MapChess::drawTile(999999997,MapChess::getPos(pos), (pos.x + pos.y)*100+getHeight(focus)*3+2,999999997);
	}
}

void MapChess::removeActing(){
	map->removeChildByTag(999999997);
}

int MapChess::getTileOrder(int i,int j,int h){
	return (i + j)*100 + h*3;
}

int MapChess::getPieceOrder(int i,int j,int h){
	return (i + j + 1)*100 + h*3+1;
}


Vec2 MapChess::getPos(Vec2 p){
	double distY = 32.0/sqrt(3); 
	return Vec2(32*(p.y-p.x), -distY*(p.x+p.y) + MapChess::getHeight(p.x,p.y)*12);
}

Vec2 MapChess::getMapPos(Vec2 p){
	for(int i=row-1;i>=0;i--)
		for(int j=col-1;j>=0;j--)
			if (MapChess::checkInside(p,i,j)) return Vec2(i,j);
	return Vec2(-1,-1);
}

Vec2 MapChess::getRealPos(int i, int j, int h){
	double distY = 32.0/sqrt(3);
	return Vec2(32*(j-i), -distY*(i+j) + h*12);
}

int MapChess::getHeight(int i,int j){
	return height[i][j];
}

int MapChess::getHeight(Vec2 p){
	return height[(int)(p.x)][(int)(p.y)];
}

int MapChess::getType(int i,int j){
	return type[i][j];
}

void MapChess::setHeight(int i,int j,int h){
	height[i][j] = h;
}
void MapChess::setType(int i,int j,int t){
	type[i][j] = t;
}

void MapChess::setOccupied(Vec2 p, bool value){
	occupied[(int)(p.x)][(int)(p.y)] = value;
}

bool MapChess::getOccupied(Vec2 p){
	return occupied[(int)(p.x)][(int)(p.y)];
}

int MapChess::getTileTag(int i, int j, int h){
	return  i*1000000+j*10000+h*100;
}

int MapChess::getPieceTag(int i, int j, int h){
	return  100000000+i*1000000+j*10000+h*100;
}

void MapChess::removeTile(int i,int j, int h){
	map->removeChildByTag(i*1000000+j*10000+h*100);
}

int MapChess::downHeight(int i,int j){
	if (height[i][j]>0) height[i][j]--;
	return height[i][j];
}

int MapChess::upHeight(int i,int j){
	height[i][j]++;
	return height[i][j];
}

bool MapChess::checkInside(Vec2 p, int i, int j){
	double distY = 32.0/sqrt(3); 
	double x = 32*(j-i), y = -distY*(i+j) + MapChess::getHeight(i,j)*12;

	Poly polygon;
	int h[4][2] = {{32,0},{0,18},{-31,0},{0,-18}};
	for(int k=0;k<4;k++) polygon.push_back(Vec2(x+h[k][0], y+h[k][1]));
	//p = p - Vec2(x,y); return p.length() < 17.0; 
	return polygon.inside(p);
}

void MapChess::drawTile(int type, Vec2 p, int order, int tag){
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create(__String::createWithFormat("Tile/%d.png", type)->getCString());
	Vec2 imgSize = sprite->getContentSize();
	sprite->setPosition(Vec2(p.x, p.y + imgSize.y/2-24));
	map->addChild(sprite, order,tag);
}

void MapChess::drawPiece(Piece *piece, int order, int tag){
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SpriteChess* sprite = SpriteChess::create(__String::createWithFormat("Character/%s%d.png", piece->getTypeOfPiece(),piece->getOwner()->getSide())->getCString());
	
	piece->addSprite(sprite);
	sprite->setPiece(piece);
	Vec2 imgSize = sprite->getContentSize();
	Vec2 p = MapChess::getPos(piece->getPosition());
	sprite->setPosition(Vec2(p.x, p.y + imgSize.y/2-24));
	map->addChild(sprite, order,tag);
	sprite->scheduleUpdate();
	
	//sprite.SpriteChess::update(0);
	//sprite->setScheduler(BattleScene::getScheduler());
}

void MapChess::drawMap(){
	for(int i=0;i<player2->getNumPieces();i++){
		Piece* p = player2->getPiece(i);
		Vec2 pos = p->getPosition();
		drawPiece(p, MapChess::getPieceOrder(pos.x,pos.y, MapChess::getHeight(pos)),
			MapChess::getPieceTag(pos.x,pos.y, MapChess::getHeight(pos)));
	}
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			for(int k=0;k<=MapChess::getHeight(i,j);k++){
				drawTile(	MapChess::getType(i,j),
							MapChess::getRealPos(i,j,k),
							MapChess::getTileOrder(i,j,k), 
							MapChess::getTileTag(i,j,k)); 
			}
		}
	}
	for(int i=0;i<player1->getNumPieces();i++){
		Piece* p = player1->getPiece(i);
		Vec2 pos = p->getPosition();
		drawPiece(p, MapChess::getPieceOrder(pos.x,pos.y, MapChess::getHeight(pos)),
			MapChess::getPieceTag(pos.x,pos.y, MapChess::getHeight(pos)));
	}
	
}

void MapChess::addPlayer(){
	player1 = Player::createPlayer();
	player1->setSide(0);
	player1->addAllPieces();

	player2 = Player::createPlayer();
	player2->setSide(1);
	player2->addAllPieces();

}

Piece* MapChess::focusOnPiece(){
	for(int i=0;i<player1->getNumPieces();i++){
		Piece* p = player1->getPiece(i);
		if (!p->isDied()){
			Vec2 pos = p->getPosition();
			if (pos == focus) {
				focusedPiece = p;
				return p;
			}
		}
	}
	for(int i=0;i<player2->getNumPieces();i++){
		Piece* p = player2->getPiece(i);
		if (!p->isDied()){
			Vec2 pos = p->getPosition();
			if (pos == focus) {
				focusedPiece = p;
				return p;
			}
		}
	}
	return NULL;
}

Player* MapChess::getPlayer(int u){
	if (u==1) return player1;
	else return player2;
}

void MapChess::loadFromFile(char *fileName){
	string fullPath = FileUtils::getInstance()->getWritablePath() + fileName;
	ifstream fi(fullPath.c_str(),ios::out|ios::binary);
	
	if (fi.is_open()){
		fi.seekg (0, fi.end);
		int length = fi.tellg();
		fi.seekg (0, fi.beg);

		char *buffer = new char[length];
		fi.read(buffer,length);
		int size = 0;
		MapChess::setRow(buffer[size++]);
		MapChess::setCol(buffer[size++]);

		for(int i=0;i<MapChess::getRow();i++){
			for(int j=0;j<MapChess::getCol();j++){
				MapChess::setHeight(i,j,buffer[size++]);
				MapChess::setType(i,j,buffer[size++]);
			}
		}
		delete[] buffer;
		fi.close();
	}
	MapChess::refressMap();
}

void MapChess::setAreaOfEffect(std::vector<Vec2> area){
	areaOfEffect =  area;
}

std::vector<Vec2> MapChess::getAreaOfEffect(){
	return areaOfEffect; 
}

bool MapChess::focusOnAreaOfEffect(){
	for(int i=0;i<areaOfEffect.size();i++){
		if (areaOfEffect.at(i).equals(focus)) return true;
	}
	return false;
}

Piece* MapChess::getFocusedPiece(){
	return focusedPiece;
}

void MapChess::clearAreaOfEffect(){
	areaOfEffect.clear();
	MapChess::removeAreaOfEffect();
}

int MapChess::getTurn(){
	return turn;
}

void MapChess::increaseTurn(){
	turn++;
	BattleScene::updateLabelTurn();
}

void MapChess::setPhrase(int p){
	phrase = p;
}

int MapChess::getPhrase(){
	return phrase;
}

void MapChess::setActionPiece(Piece *p){
	actionPiece = p;
}

Piece* MapChess::getActionPiece(){
	return actionPiece;
}

void MapChess::setActingPiece(Piece *p){
	actingPiece = p;
}

Piece* MapChess::getActingPiece(){
	return actingPiece;
}

void MapChess::showDamage(Vec2 pos, int damage){

	labelDamage->setString(__String::createWithFormat("%d",-damage)->getCString());
	labelDamage->setPosition(pos+Vec2(0,20));
	labelDamage->setOpacity(0);
	
	Vector<FiniteTimeAction*> vecSeq;
	vecSeq.pushBack(MoveBy::create(0.5,Vec2::ZERO));
	vecSeq.pushBack(MoveBy::create(0.5,Vec2(0,100)));
	vecSeq.pushBack(FadeOut::create(0.5));
	labelDamage->runAction(Sequence::create(vecSeq));
	labelDamage->runAction(FadeIn::create(0.5));
}

Player* MapChess::getCurrentTurnPlayer(){
	if ((turn%2)==0) return player1;
	else return player2;
}

void MapChess::setFocusedPieceToNULL(){
	focusedPiece = NULL;
}

Piece* MapChess::getPreFocusedPiece(){
	return preFocusedPiece;
}
	
void MapChess::setPreFocusedPiece(Piece* p){
	preFocusedPiece = p;
}