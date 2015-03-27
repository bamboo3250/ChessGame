#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "MapChess.h"

class BattleScene : public cocos2d::Layer
{
private:
	static cocos2d::Sprite* mainInfoPieceUI[2];
	static cocos2d::Sprite* damageArrow;

	static LabelTTF* labelCountTurn;
	static LabelTTF* labelShowTurn;
	static MenuItemImage* moveButton;
	static MenuItemImage* attackButton;
	static MenuItemImage* skillButton;
	static MenuItemImage* endTurnButton;
	static MenuItemImage* cancelButton;
	static MenuItemImage* cancelButton2;
	static Menu* menu;
	static Menu* menu2;
	static Vec2 prePos;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void moveButtonPressedCallback(cocos2d::Ref* pSender);
	void attackButtonPressedCallback(cocos2d::Ref* pSender);
	void skillButtonPressedCallback(cocos2d::Ref* pSender);
	void endTurnButtonPressedCallback(cocos2d::Ref* pSender);
	void cancelButtonPressedCallback(cocos2d::Ref* pSender);


    void addListener();
	void addInfoPieceUI();
	void addBattleMenu();
	static void showInfoPiece(int index, bool show);
    static void changeInfoPiece(int index, Piece* piece);
	static void addTextInfo(int index, LabelTTF* text, Color3B color, Vec2 position, int tag);
	static void updateLabelTurn();
	static void openMenuChooseAction(Vec2 p);
	static void endTurn();
	static void changeShowDamage(int damage);
    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);
};

#endif // __BATTLE_SCENE_H__
