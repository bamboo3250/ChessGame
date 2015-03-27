#include "BattleScene.h"


USING_NS_CC;

cocos2d::Sprite* BattleScene::mainInfoPieceUI[2];
cocos2d::Sprite* BattleScene::damageArrow;
LabelTTF* BattleScene::labelCountTurn;
LabelTTF* BattleScene::labelShowTurn;
MenuItemImage* BattleScene::moveButton;
MenuItemImage* BattleScene::attackButton;
MenuItemImage* BattleScene::skillButton;
MenuItemImage* BattleScene::endTurnButton;
MenuItemImage* BattleScene::cancelButton;
MenuItemImage* BattleScene::cancelButton2;
Menu* BattleScene::menu;
Menu* BattleScene::menu2;
Vec2 BattleScene::prePos;

Scene* BattleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BattleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
   
    if ( !Layer::init() ) return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	*/
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    /*auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);*/
	this->addInfoPieceUI();


	MapChess::resetMap();
	MapChess::addPlayer();
	MapChess::drawMap();
	MapChess::setMapPosition(Vec2(visibleSize.width*2/3,400));
	this->addChild(MapChess::getMap(),2,2);
	BattleScene::addListener();
	
	labelCountTurn = LabelTTF::create(__String::createWithFormat("Turn: %d",MapChess::getTurn())->getCString(),"Arial",20);
	labelCountTurn->setPosition(Vec2(900,600));
	labelCountTurn->setDimensions(Size(130,30));
	labelCountTurn->setColor(Color3B::WHITE);
	this->addChild(labelCountTurn,3);
	
	labelShowTurn = LabelTTF::create("","Arial",30);
	labelShowTurn->setPosition(Vec2(visibleSize.width/2,570));
	labelShowTurn->setDimensions(Size(530,40));
	labelShowTurn->setColor(Color3B::WHITE);
	this->addChild(labelShowTurn,3);
	BattleScene::updateLabelTurn();

	MapChess::loadFromFile("aaa.map");
	BattleScene::addBattleMenu();

	cancelButton2 = MenuItemImage::create("UI/CancelButton.png","UI/CancelButtonPressed.png","UI/CancelButtonDisabled.png",CC_CALLBACK_1(BattleScene::cancelButtonPressedCallback,this));
	cancelButton2->setPosition(Vec2(900,520));
	cancelButton2->setScale(1);
	menu2 = Menu::create(cancelButton2,NULL);
	menu2->setPosition(Vec2::ZERO);
	menu2->setVisible(false);
	this->addChild(menu2,1000000000);
	return true;
}

void BattleScene::addInfoPieceUI(){
	mainInfoPieceUI[0] = Sprite::create("UI/UIInfoChess2.png");
	mainInfoPieceUI[0]->setPosition(Vec2(210, 450));
	mainInfoPieceUI[0]->setVisible(false);
	
	mainInfoPieceUI[1] = Sprite::create("UI/UIInfoChess2.png");
	mainInfoPieceUI[1]->setPosition(Vec2(210, 170));
	mainInfoPieceUI[1]->setVisible(false);

	damageArrow = Sprite::create("UI/arrow2.png");
	damageArrow->setPosition(210,310);
	damageArrow->setOpacity(128);
	damageArrow->setVisible(false);

	this->addChild(mainInfoPieceUI[0],999999999);
	this->addChild(mainInfoPieceUI[1],999999999);
	this->addChild(damageArrow,999999999);
}

void BattleScene::showInfoPiece(int index, bool show){
	mainInfoPieceUI[index]->setVisible(show);
	if (index == 1) {
		damageArrow->setVisible(show);
	}
}

void BattleScene::addTextInfo(int index, LabelTTF* text, Color3B color, Vec2 position, int tag){
	text->setColor(color);
	text->setDimensions(Size(160,30));
	text->setHorizontalAlignment(TextHAlignment::LEFT);
	text->setPosition(position);
	text->setTag(tag);

	mainInfoPieceUI[index]->removeChildByTag(tag);
	mainInfoPieceUI[index]->addChild(text);
}

void BattleScene::changeInfoPiece(int index, Piece* piece){
	mainInfoPieceUI[index]->removeChildByTag(1);
	auto img = Sprite::create(__String::createWithFormat("Character/%s%d.png", piece->getTypeOfPiece(),piece->getOwner()->getSide())->getCString());
	img->setPosition(Vec2(47, 120));
	img->setTag(1);
	mainInfoPieceUI[index]->addChild(img);

	int alignX1 = 170;
	int alignY1 = 110;

	auto pieceType = LabelTTF::create(piece->getTypeOfPiece(), "Arial", 20);
	BattleScene::addTextInfo(index,pieceType,Color3B(84,194,84),Vec2(alignX1, alignY1),2);
	
	auto pieceLevel = LabelTTF::create(__String::createWithFormat("Lv: %3d",piece->getLevel())->getCString(), "Arial", 20);
	BattleScene::addTextInfo(index,pieceLevel,Color3B::BLACK,Vec2(alignX1, alignY1-25),3);
	
	auto pieceExp = LabelTTF::create(__String::createWithFormat("Exp: %7d",piece->getExp())->getCString(), "Arial", 20);
	BattleScene::addTextInfo(index,pieceExp,Color3B::BLACK,Vec2(alignX1, alignY1-50),4);
	
	int alignX2 = 295;
	int alignY2 = 110;

	auto pieceHP = LabelTTF::create(__String::createWithFormat("HP: %4d/%4d",piece->getCurrentHP(),piece->getMaxHP())->getCString(), "Arial", 20);
	if (piece->getPercentHP()>=50){
		BattleScene::addTextInfo(index,pieceHP,Color3B::GREEN,Vec2(alignX2, alignY2),5);
	} else if (piece->getPercentHP()>=25){
		BattleScene::addTextInfo(index,pieceHP,Color3B::YELLOW,Vec2(alignX2, alignY2),5);
	} else 
		BattleScene::addTextInfo(index,pieceHP,Color3B::RED,Vec2(alignX2, alignY2),5);
	
	auto pieceMana = LabelTTF::create(__String::createWithFormat("MP: %4d/%4d",piece->getCurrentMana(),piece->getMaxMana())->getCString(), "Arial", 20);
	BattleScene::addTextInfo(index,pieceMana,Color3B::BLACK,Vec2(alignX2, alignY2-25),6);
	
	auto pieceAtk = LabelTTF::create(__String::createWithFormat("Atk: %4d",piece->getAtk())->getCString(), "Arial", 20);
	BattleScene::addTextInfo(index,pieceAtk,Color3B::BLACK,Vec2(alignX2, alignY2-50),7);
	
	auto pieceDef = LabelTTF::create(__String::createWithFormat("Def: %4d",piece->getDef())->getCString(), "Arial", 20);
	BattleScene::addTextInfo(index,pieceDef,Color3B::BLACK,Vec2(alignX2, alignY2-75),8);
	
}

void BattleScene::endTurn(){
	MapChess::setActingPiece(NULL);
	MapChess::setActionPiece(NULL);
	MapChess::increaseTurn();
	moveButton->setEnabled(true);
	attackButton->setEnabled(true);
	skillButton->setEnabled(true);
	endTurnButton->setEnabled(false);
	MapChess::setPhrase(0);
	menu->setVisible(false);
	menu2->setVisible(false);
}

void BattleScene::addListener(){
	auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);

    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Layer*>(event->getCurrentTarget());// event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());//Get the position of the current point relative to the button
        
		Vec2 pos = MapChess::getMapPos(locationInNode);
		MapChess::removeFocus();
		
		if (MapChess::getPhrase()!=3){
			BattleScene::showInfoPiece(0,false);
			BattleScene::showInfoPiece(1,false);
		}

		MapChess::setFocus(pos);
		MapChess::drawFocus();

		Piece* focusedPiece = NULL;
		if (MapChess::getPhrase()==0) {
			MapChess::removeAreaOfEffect();
		}
		//if ((MapChess::getPhrase()==0) || (MapChess::getPhrase()==3)) 
		focusedPiece = MapChess::focusOnPiece();

		switch (MapChess::getPhrase()){
			case 0: // Choose action
				if (focusedPiece!=NULL){
					if ((focusedPiece->getOwner()->getSide() == MapChess::getTurn()%2) && 
						((MapChess::getActingPiece()==NULL) || (MapChess::getActingPiece()==focusedPiece))){
							BattleScene::openMenuChooseAction(focusedPiece->getPosition());
					}
					BattleScene::showInfoPiece(0,true);
					BattleScene::changeInfoPiece(0,focusedPiece);
				} else {
					menu->setVisible(false);
				}
				break;
			case 1: 
				if (!menu->isVisible()){
					BattleScene::openMenuChooseAction(MapChess::getActingPiece()->getPosition());
				}
				BattleScene::showInfoPiece(0,true);
				if (focusedPiece!=NULL){
					BattleScene::changeInfoPiece(0,focusedPiece);
				} else {
					BattleScene::changeInfoPiece(0,MapChess::getActingPiece());
				}
				break;
			case 2:	// Move
				if (focusedPiece!=NULL){
					BattleScene::showInfoPiece(0,true);
					BattleScene::changeInfoPiece(0,focusedPiece);
				} else {
					BattleScene::showInfoPiece(0,false);
				}
				if (MapChess::focusOnAreaOfEffect()){
					Piece* p = MapChess::getActionPiece();
					MapChess::setActingPiece(p);
					MapChess::clearAreaOfEffect();
					prePos = p->getPosition();
					p->moveTo(MapChess::getFocus(), 0);
					moveButton->setEnabled(false);
					skillButton->setEnabled(false);
					MapChess::setPhrase(1);
					menu2->setVisible(false);
					endTurnButton->setEnabled(true);
					MapChess::removeActing();
					MapChess::drawActing();
					
				}
				break;
			case 3: // Attack
				if (focusedPiece!=NULL) {
					BattleScene::changeInfoPiece(0,MapChess::getFocusedPiece());
					BattleScene::showInfoPiece(0,true);
					BattleScene::showInfoPiece(1,false);
				}
				if ((MapChess::focusOnAreaOfEffect()) && (focusedPiece!=NULL) 
						&& (focusedPiece->getOwner()->getSide() != MapChess::getTurn()%2)){
					if (MapChess::getPreFocusedPiece()!=focusedPiece){
						MapChess::setPreFocusedPiece(focusedPiece);
						BattleScene::changeInfoPiece(0,MapChess::getActionPiece());
						BattleScene::changeInfoPiece(1,MapChess::getFocusedPiece());
						BattleScene::showInfoPiece(0,true);
						BattleScene::showInfoPiece(1,true);
						BattleScene::changeShowDamage(MapChess::getActionPiece()->getDamage(MapChess::getFocusedPiece()));
					} else {
						Piece* p = MapChess::getActionPiece();
						MapChess::setActingPiece(p);
						MapChess::removeActing();
						MapChess::drawActing();
					
						p->attack(focusedPiece);
						
						BattleScene::changeInfoPiece(0,MapChess::getActionPiece());
						BattleScene::changeInfoPiece(1,MapChess::getFocusedPiece());
						BattleScene::showInfoPiece(0,true);
						BattleScene::showInfoPiece(1,true);
						
						MapChess::clearAreaOfEffect();
						attackButton->setEnabled(false);
						skillButton->setEnabled(false);
						MapChess::setPhrase(1);
						menu2->setVisible(false);
						endTurnButton->setEnabled(true);
						if (!moveButton->isEnabled()) cancelButton->setEnabled(false);
					}
				} else {
					MapChess::setPreFocusedPiece(NULL);
				}
				break;
		}

		return true; //false;
    };

	listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
    };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, MapChess::getMap());
}

void BattleScene::updateLabelTurn(){
	 Size visibleSize = Director::getInstance()->getVisibleSize();

	labelCountTurn->setString(__String::createWithFormat("Turn: %d",MapChess::getTurn())->getCString());
	labelShowTurn->setOpacity(0);
	labelShowTurn->setString(
		__String::createWithFormat("%s's turn",MapChess::getCurrentTurnPlayer()->getUserName().getCString())->getCString()
	);
	labelShowTurn->setScale(1);
	labelShowTurn->setPosition(visibleSize.width/2,570);

	Vector<FiniteTimeAction*> vecSeq1;
	vecSeq1.pushBack(MoveBy::create(1,Vec2::ZERO));
	vecSeq1.pushBack(MoveBy::create(0.5,Vec2(0,20)));

	Vector<FiniteTimeAction*> vecSeq2;
	vecSeq2.pushBack(MoveBy::create(1,Vec2::ZERO));
	vecSeq2.pushBack(FadeIn::create(0.5));

	Vector<FiniteTimeAction*> vecSeq3;
	vecSeq3.pushBack(MoveBy::create(1,Vec2::ZERO));
	vecSeq3.pushBack(ScaleBy::create(0.5,2,2));

	labelShowTurn->runAction(Sequence::create(vecSeq1));
	labelShowTurn->runAction(Sequence::create(vecSeq2));
	labelShowTurn->runAction(Sequence::create(vecSeq3));

}
/*Scheduler* BattleScene::getScheduler(){
	return mainScheduler;
}*/
/*void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}*/

void BattleScene::openMenuChooseAction(Vec2 p){
	Vec2 realPos = MapChess::getPos(p)+Vec2(0,22);
	Vec2 anchor = Vec2(0.5,-1.3);
	
	moveButton->setVisible(true);
	moveButton->setRotation(0);
	moveButton->setPosition(realPos);
	moveButton->setAnchorPoint(anchor);
	
	attackButton->setVisible(true);
	attackButton->setRotation(-72);
	attackButton->setPosition(realPos);
	attackButton->setAnchorPoint(Vec2(-1.211901729,-0.05623058987));
	
	skillButton->setVisible(true);
	skillButton->setRotation(-144);
	skillButton->setPosition(realPos);
	skillButton->setAnchorPoint(Vec2(-0.5580134541,1.95623059));
	
	endTurnButton->setVisible(true);
	endTurnButton->setRotation(-216);
	endTurnButton->setPosition(realPos);
	endTurnButton->setAnchorPoint(Vec2(1.558013454,1.95623059));
	if (MapChess::getPhrase()==0) endTurnButton->setEnabled(false);

	cancelButton->setVisible(true);
	cancelButton->setRotation(-288);
	cancelButton->setPosition(realPos);
	cancelButton->setAnchorPoint(Vec2(2.211901729,-0.05623058987));

	menu->setVisible(true);
	attackButton->runAction(RotateBy::create(0.3,72));
	skillButton->runAction(RotateBy::create(0.3,144));
	endTurnButton->runAction(RotateBy::create(0.3,216));
	cancelButton->runAction(RotateBy::create(0.3,288));
	
}

void BattleScene::addBattleMenu(){
	moveButton = MenuItemImage::create("UI/MoveButton.png","UI/MoveButtonPressed.png","UI/MoveButtonDisabled.png",CC_CALLBACK_1(BattleScene::moveButtonPressedCallback,this));
	attackButton = MenuItemImage::create("UI/AttackButton.png","UI/AttackButtonPressed.png","UI/AttackButtonDisabled.png",CC_CALLBACK_1(BattleScene::attackButtonPressedCallback,this));
	skillButton = MenuItemImage::create("UI/SkillButton.png","UI/SkillButtonPressed.png","UI/SkillButtonDisabled.png",CC_CALLBACK_1(BattleScene::skillButtonPressedCallback,this));
	endTurnButton = MenuItemImage::create("UI/EndTurnButton.png","UI/EndTurnButtonPressed.png","UI/EndTurnButtonDisabled.png",CC_CALLBACK_1(BattleScene::endTurnButtonPressedCallback,this));
	cancelButton = MenuItemImage::create("UI/CancelButton.png","UI/CancelButtonPressed.png","UI/CancelButtonDisabled.png",CC_CALLBACK_1(BattleScene::cancelButtonPressedCallback,this));
	menu = Menu::create(moveButton,attackButton,skillButton,endTurnButton,cancelButton,NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setVisible(false);
	MapChess::getMap()->addChild(menu,1000000000);
}

void BattleScene::moveButtonPressedCallback(Ref* pSender){
	if (MapChess::getActingPiece()!=NULL){
		MapChess::setActionPiece(MapChess::getActingPiece());
	} else { 
		if (MapChess::getFocusedPiece()->getOwner()->getSide()==MapChess::getTurn()%2){
			MapChess::setActionPiece(MapChess::getFocusedPiece());
		}
	}
	menu->setVisible(false);
	menu2->setVisible(true);

	MapChess::setPhrase(2);

	if (MapChess::getActionPiece()->getOwner()->getSide()==MapChess::getTurn()%2){
		MapChess::setAreaOfEffect(MapChess::getActionPiece()->getAreaOfMove());
		MapChess::drawAreaOfEffect(MapChess::getAreaOfEffect());
	}

}

void BattleScene::attackButtonPressedCallback(Ref* pSender){
	if (MapChess::getActingPiece()!=NULL){
		MapChess::setActionPiece(MapChess::getActingPiece());
	} else { 
		if (MapChess::getFocusedPiece()->getOwner()->getSide()==MapChess::getTurn()%2){
			MapChess::setActionPiece(MapChess::getFocusedPiece());
		}
	}
	menu->setVisible(false);
	menu2->setVisible(true);
	
	MapChess::setPhrase(3);

	if (MapChess::getActionPiece()->getOwner()->getSide()==MapChess::getTurn()%2){
		MapChess::setAreaOfEffect(MapChess::getActionPiece()->getAreaOfAttack());
		MapChess::drawAreaOfEffect(MapChess::getAreaOfEffect());
	}
}

void BattleScene::skillButtonPressedCallback(Ref* pSender){
	
}

void BattleScene::endTurnButtonPressedCallback(Ref* pSender){
	MapChess::removeActing();
	MapChess::getActingPiece()->setFirstStep(false);
	MapChess::setActingPiece(NULL);
	MapChess::setActionPiece(NULL);
	MapChess::setPreFocusedPiece(NULL);

	MapChess::increaseTurn();
	moveButton->setEnabled(true);
	attackButton->setEnabled(true);
	skillButton->setEnabled(true);
	cancelButton->setEnabled(true);
	MapChess::setPhrase(0);
	menu->setVisible(false);
	menu2->setVisible(false);
}

void BattleScene::cancelButtonPressedCallback(Ref* pSender){
	MapChess::setPreFocusedPiece(NULL);
	BattleScene::showInfoPiece(0,false);
	BattleScene::showInfoPiece(1,false);

	if (MapChess::getActingPiece()==NULL) {
		menu->setVisible(false);
		MapChess::removeActing();
		MapChess::setPhrase(0);
		MapChess::setFocusedPieceToNULL();
	} else {
		if (MapChess::getPhrase()<=1){
			if (!moveButton->isEnabled()){
				moveButton->setEnabled(true);
				MapChess::getActingPiece()->returnToPosWithImage(prePos);
				openMenuChooseAction(MapChess::getActingPiece()->getPosition());
				MapChess::removeActing();
				MapChess::drawActing();
				if (attackButton->isEnabled()){
					skillButton->setEnabled(true);
					endTurnButton->setEnabled(false);
					MapChess::removeActing();
					MapChess::setPhrase(0);
					MapChess::setActingPiece(NULL);
				}
			}
		}
		if (MapChess::getActingPiece()!=NULL){
			openMenuChooseAction(MapChess::getActingPiece()->getPosition());
		} else if ((MapChess::getFocusedPiece()!=NULL) 
			&& (MapChess::getFocusedPiece()->getOwner()->getSide()==MapChess::getTurn()%2)){
			openMenuChooseAction(MapChess::getFocusedPiece()->getPosition());
		}
		if (MapChess::getPhrase()>1) MapChess::setPhrase(1);
	}
	menu2->setVisible(false);
	MapChess::removeAreaOfEffect();
	MapChess::removeFocus();
	
}

void BattleScene::changeShowDamage(int damage){
	damageArrow->removeAllChildren();
	auto text = LabelTTF::create(__String::createWithFormat("Damage: %d",damage)->getCString(),"Arial",25);
	text->setDimensions(Size(120,60));
	text->setPosition(damageArrow->getContentSize()/2);
	damageArrow->addChild(text,1,1);
}