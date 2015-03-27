#include "Piece.h"

int Piece::expToLevel[101];
int Piece::count = 0;
bool Piece::computeExpToLevel = false;

void Piece::generateExpToLevel(){
	if (!computeExpToLevel){
		for(int i=0;i<=100;i++){
			expToLevel[i] = (int) (10000.0*(exp(i/15.0)-1)/(exp(30/15.0)-1));
		}
		computeExpToLevel = true;
	}
};

void Piece::refresh(){
	level = getLevel(experience);
	maxHP = baseMaxHP + maxHPGrowth*level;
	maxMana = baseMana + manaGrowth*level;
	atk = baseAtk + atkGrowth*level;
	def = baseDef + defGrowth*level;
	
}

int Piece::getExp(){
	return experience;
}

int Piece::getLevel(int e){
	generateExpToLevel();
	int d=0, c=100, md, ans=0;
	while(d<=c){
		md=(d+c)/2;
		if (expToLevel[md]>e) {
			ans = md;
			c = md-1;
		} else 
			d = md+1;
	}
	//ans = 100;
	return ans;
}

int Piece::getLevel(){
	return level;
}

int Piece::getMaxHP(){
	return maxHP;
}

int Piece::getCurrentHP(){
	return currentHP;
}

int Piece::getMaxMana(){
	return maxMana;
}

int Piece::getCurrentMana(){
	return currentMana;
}

int Piece::getAtk(){
	return atk;
}

int Piece::getDef(){
	return def;
}

Vec2 Piece::getPosition(){
	return position;
}

void Piece::setPosition(Vec2 pos){
	position = pos;
}

Player* Piece::getOwner(){
	return owner;
}

void Piece::setOwner(Player *p){
	owner = p;
}

void Piece::attack(Piece *target){
	int damage = target->defend(this->atk);

	Vec2 targetRealPos = MapChess::getPos(target->getPosition());
	Vec2 thisRealPos = MapChess::getPos(this->getPosition());
	Vec2 direction = targetRealPos - thisRealPos;
	direction = direction/direction.getLength();
	Vector<FiniteTimeAction*> vecSeq;
	vecSeq.pushBack(MoveBy::create(0.1,-direction*7));
	vecSeq.pushBack(MoveBy::create(0.1,direction*17));
	vecSeq.pushBack(MoveBy::create(0.1,-direction*10));
	this->image->runAction(Sequence::create(vecSeq));

	Vector<FiniteTimeAction*> vecSeq2;
	vecSeq2.pushBack(MoveBy::create(0.5,Vec2::ZERO));
	vecSeq2.pushBack(Blink::create(0.5,3));
	target->image->runAction(Sequence::create(vecSeq2));

	MapChess::showDamage(target->image->getPosition(),damage);

	if (target->getCurrentHP()==0) {
		target->die();
		this->moveTo(target->getPosition(), 1.5);
	}
}

double Piece::getPercentHP(){
	return 100.0*currentHP/maxHP;
}

// 1.5s
void Piece::die(){
	Vector<FiniteTimeAction*> vecSeq1;
	Vector<FiniteTimeAction*> vecSeq2;
	Vector<FiniteTimeAction*> vecSeq3;
	Vector<FiniteTimeAction*> vecSeq4;
	vecSeq1.pushBack(MoveBy::create(1,Vec2::ZERO));
	vecSeq1.pushBack(ScaleTo::create(0.5,0,2));
	vecSeq2.pushBack(MoveBy::create(1,Vec2::ZERO));
	vecSeq2.pushBack(FadeOut::create(0.5));
	vecSeq3.pushBack(MoveBy::create(1,Vec2::ZERO));
	vecSeq3.pushBack(Blink::create(0.5,5));
	vecSeq4.pushBack(MoveBy::create(1,Vec2::ZERO));
	vecSeq4.pushBack(MoveBy::create(0.5,Vec2(0,40)));
	this->image->runAction(Sequence::create(vecSeq1));
	this->image->runAction(Sequence::create(vecSeq2));
	this->image->runAction(Sequence::create(vecSeq3));
	this->image->runAction(Sequence::create(vecSeq4));
	MapChess::setOccupied(this->getPosition(),false);


}

int Piece::defend(int incomingAtk){
	if (incomingAtk>def){
		currentHP -= incomingAtk-def;
		if (currentHP<0) currentHP = 0;
		return incomingAtk-def;
	}
	return 0;
}

vector<Vec2> Piece::BFS(Vec2 start, Vec2 des){
	Vec2 h[8] = {Vec2(0,1),Vec2(1,0),Vec2(1,1),Vec2(-1,0),Vec2(0,-1),Vec2(-1,1),Vec2(1,-1),Vec2(-1,-1)};
	int preH[50][50];
	int tham[50][50] = {false};
	queue<Vec2> q;
	Vec2 u,v;
	q.push(start);
	tham[(int) start.x][(int) start.y] = true;
	preH[(int) start.x][(int) start.y] = 0;
	while(!q.empty()){
		u = q.front();
		q.pop();
		for(int i=0;i<8;i++){
			int curH = (preH[(int) u.x][(int) u.y] + i) % 8;
			v = u + h[curH];
			if ((0<=v.x) && (v.x<MapChess::getRow()) && (0<=v.y) && (v.y<MapChess::getCol())){
				if (!tham[(int)v.x][(int)v.y]){
					q.push(v);
					tham[(int)v.x][(int)v.y] = true;
					preH[(int)v.x][(int)v.y] = curH;
					if (v.equals(des)){
						vector<Vec2> res;
						while(!des.equals(start)){
							res.push_back(des);
							des = des - h[preH[(int)des.x][(int)des.y]];
						}
						return res;
					}
				}
			}
		}
	}
	return vector<Vec2>();
}

void Piece::refreshOrder(Vec2 pos, int h){
	position = pos;
	height = h;
	image->setZOrder(MapChess::getPieceOrder(position.x,position.y,height));
}

void Piece::moveTo(Vec2 des, float waitTime){
	if (!MapChess::getOccupied(des)){
		MapChess::setOccupied(position,false);
		MapChess::setOccupied(des,true);
		
		Vec2 imgSize = image->getContentSize();
		
		Vector<FiniteTimeAction*> vecSeq1;
		Vector<FiniteTimeAction*> vecSeq2;
		Vector<FiniteTimeAction*> vecSeq3;
		Vector<FiniteTimeAction*> vecSeq4;
		Vector<FiniteTimeAction*> vecSeq5;
		Vector<FiniteTimeAction*> vecSeq6;
		Vector<FiniteTimeAction*> vecSeq7;
		Vector<FiniteTimeAction*> vecSeq8;
		Vector<FiniteTimeAction*> vecSeq9;

		vecSeq1.pushBack(MoveBy::create(waitTime,Vec2::ZERO));
		vecSeq1.pushBack(ScaleTo::create(0.1,0,2));
		image->runAction(Sequence::create(vecSeq1));

		vecSeq2.pushBack(MoveBy::create(waitTime,Vec2::ZERO));
		vecSeq2.pushBack(MoveBy::create(0.1,Vec2(0,40)));
		image->runAction(Sequence::create(vecSeq2));

		vecSeq3.pushBack(MoveBy::create(waitTime,Vec2::ZERO));
		vecSeq3.pushBack(FadeOut::create(0.1));
		image->runAction(Sequence::create(vecSeq3));

		vecSeq4.pushBack(MoveBy::create(waitTime+0.1,Vec2::ZERO));
		vecSeq4.pushBack(MoveTo::create(0.1,MapChess::getPos(des)+Vec2(0,imgSize.y/2-24)));
		image->runAction(Sequence::create(vecSeq4));

		vecSeq5.pushBack(MoveBy::create(waitTime+0.2,Vec2::ZERO));
		vecSeq5.pushBack(ScaleTo::create(0.2,1,1));
		image->runAction(Sequence::create(vecSeq5));

		vecSeq6.pushBack(MoveBy::create(waitTime+0.2,Vec2::ZERO));
		vecSeq6.pushBack(FadeIn::create(0.2));
		image->runAction(Sequence::create(vecSeq6));

		position = des;
		image->setZOrder(MapChess::getPieceOrder(des.x,des.y,MapChess::getHeight(des)));
		image->setTag(MapChess::getPieceTag(des.x,des.y,MapChess::getHeight(des)));
		
		Sprite *actingTile = (Sprite *) MapChess::getMap()->getChildByTag(999999997);
		if (actingTile!=NULL) {
			vecSeq7.pushBack(MoveBy::create(waitTime,Vec2::ZERO));
			vecSeq7.pushBack(FadeOut::create(0.1));
			
			vecSeq8.pushBack(MoveBy::create(waitTime+0.1,Vec2::ZERO));
			vecSeq8.pushBack(MoveTo::create(0.1,MapChess::getPos(des)+Vec2(0,imgSize.y/2-24)));
			
			vecSeq9.pushBack(MoveBy::create(waitTime+0.2,Vec2::ZERO));
			vecSeq9.pushBack(FadeIn::create(0.2));
			
			actingTile->runAction(Sequence::create(vecSeq7));
			actingTile->runAction(Sequence::create(vecSeq8));
			actingTile->runAction(Sequence::create(vecSeq9));
			actingTile->setZOrder((des.x + des.y)*100+MapChess::getHeight(des)*3+2);
		}
		//firstStep = false;

		/*vector<Vec2> steps = Piece::BFS(position,des);
		steps.push_back(position);
		Sequence* seq = NULL;
		Vec2 start = position;
		double inteval = 0.3;
		int maxHeight = 0;
		for(int i=0;i<steps.size();i++){
			maxHeight = max(MapChess::getHeight(steps.at(i)),maxHeight);
		}
		maxHeight += 4;

		if (steps.size()>1){
			Vec2 next = steps.at(steps.size()-2);
			Vec2 realNext;
			
			realNext = MapChess::getRealPos(start.x,start.y,maxHeight) + Vec2(0,+ imgSize.y/2-24);
			seq = Sequence::createWithTwoActions( 
					CallFunc::create(CC_CALLBACK_0(Piece::refreshOrder,this,start,maxHeight)),
					MoveTo::create(inteval,realNext));
				
			realNext = MapChess::getRealPos(next.x,next.y,maxHeight) + Vec2(0,+ imgSize.y/2-24);
			seq = Sequence::createWithTwoActions(seq,
					Sequence::createWithTwoActions( 
						CallFunc::create(CC_CALLBACK_0(Piece::refreshOrder,this,next,maxHeight)),
						MoveTo::create(inteval,realNext)));
			
			if (steps.size()==2){
				realNext = MapChess::getPos(next) +Vec2(0,+ imgSize.y/2-24);
				seq = Sequence::createWithTwoActions(seq,
					Sequence::createWithTwoActions( 
						CallFunc::create(CC_CALLBACK_0(Piece::refreshOrder,this,next,MapChess::getHeight(next))),
							MoveTo::create(inteval,realNext)));
			}

			for(int i=(int) steps.size()-3;i>=0;i--){
				next = steps.at(i);
				
				realNext = MapChess::getRealPos(next.x,next.y,maxHeight) + Vec2(0,+ imgSize.y/2-24);
				seq = Sequence::createWithTwoActions(seq,
						Sequence::createWithTwoActions(
							CallFunc::create(CC_CALLBACK_0(Piece::refreshOrder,this,next,maxHeight)),
							MoveTo::create(inteval,realNext)));
				if (i==0){
					realNext = MapChess::getPos(next) + Vec2(0,+ imgSize.y/2-24);
					seq = Sequence::createWithTwoActions(seq,
							Sequence::createWithTwoActions(
								CallFunc::create(CC_CALLBACK_0(Piece::refreshOrder,this,next,MapChess::getHeight(next))),
								MoveTo::create(inteval,realNext)));
				}
			}
			image->runAction(seq);
		

			//image->setPosition(realDes);
			//image->setZOrder(MapChess::getPieceOrder(des.x,des.y,MapChess::getHeight(des)));
			image->setTag(MapChess::getPieceTag(des.x,des.y,MapChess::getHeight(des)));
			firstStep = false;
		}*/
	}
}

void Piece::setFirstStep(bool b){
	firstStep = b;
}

void Piece::addSprite(SpriteChess* img){
	image = img;
}

int Piece::getHeight(){
	return height;
}

void Piece::setHeight(int h){
	height = h;
}

bool Piece::isDied(){
	return (this->getCurrentHP()<=0);
}

void Piece::returnToPosWithImage(Vec2 pos){
	MapChess::setOccupied(position,false);
	MapChess::setOccupied(pos,false);

	position = pos;
	pos = MapChess::getPos(pos);
	Vec2 imgSize = image->getContentSize();
	image->setPosition(Vec2(pos.x, pos.y + imgSize.y/2-24));
}

int Piece::getDamage(Piece* target){
	return atk > target->getDef() ? atk - target->getDef() : 0;
}