#ifndef __MAPCHESS_H__
#define __MAPCHESS_H__
#include <cocos2d.h>
#include "Player.h"
#include "Pieces\Piece.h"
#include "BattleScene.h"
USING_NS_CC;

class MapChess {
private:
	static int MapChess::height[20][20];
	static int MapChess::type[20][20];
	static bool MapChess::occupied[20][20];
	static Vec2 MapChess::focus;
	static int row;
	static int col;
	static Player *player1, *player2;
	static std::vector<Vec2> areaOfEffect;
	static Piece* preFocusedPiece;
	static Piece* focusedPiece;
	static Piece* actionPiece;
	static Piece* actingPiece;
	static int turn;
	static int phrase; // 0: nothing; 1: acting; 2: move; 3:attack
	static Layer* map;
	static LabelTTF* labelDamage;

public:
	static void resetMap();
	static void addPlayer();
	static void refressMap();
	static void setMapPosition(Vec2 p);
	static Layer* getMap();
	static int getHeight(int i,int j);
	static int getHeight(Vec2 p);
	static void setHeight(int i,int j,int h);
	static int getType(int i,int j);
	static void setType(int i,int j,int t);
	static bool getOccupied(Vec2 p);
	static void setOccupied(Vec2 p, bool value);
	static int getTileTag(int i, int j, int h);
	static int getPieceTag(int i, int j, int h);
	static int getTileOrder(int i,int j,int h);
	static int getPieceOrder(int i,int j,int h);
	static int getRow();
	static void setRow(int r);
	static int getCol();
	static void setCol(int c);
	static Vec2 getFocus();
	static void setFocus(Vec2 p);
	static void drawFocus();
	static void removeFocus();
	static void removeTile(int i,int j, int h);
	static Vec2 getPos(Vec2 p);
	static Vec2 getMapPos(Vec2 p);
	static Vec2 getRealPos(int i, int j, int h);
	static int downHeight(int i,int j);
	static int upHeight(int i,int j);
	static Player* getPlayer(int u);
	static bool checkInside(Vec2 p, int i, int j);
	static void drawTile(int type, Vec2 p, int order,int tag);
	static void drawPiece(Piece* piece, int order,int tag);
	static void drawMap();
	static void drawAreaOfEffect(std::vector<Vec2> AreaOfEffect);
	static void removeAreaOfEffect();
	static Piece* focusOnPiece();
	static void loadFromFile(char *nameFile);
	static void setAreaOfEffect(std::vector<Vec2> area);
	static std::vector<Vec2> getAreaOfEffect();
	static bool focusOnAreaOfEffect();
	static Piece* getFocusedPiece();
	static void setFocusedPieceToNULL();
	static void clearAreaOfEffect();
	static int getTurn();
	static void increaseTurn();
	static void setPhrase(int p);
	static int getPhrase();
	static void setActionPiece(Piece *p);
	static Piece* getActionPiece();
	static void setActingPiece(Piece *p);
	static Piece* getActingPiece();
	static void showDamage(Vec2 pos, int damage);
	static Player* getCurrentTurnPlayer();
	static Piece* getPreFocusedPiece();
	static void setPreFocusedPiece(Piece* p);
	static void drawActing();
	static void removeActing();
};
#endif // __HELLOWORLD_SCENE_H__
