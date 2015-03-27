#include "bamboo3250-function.h";


int CCW(Vec2 p1, Vec2 p2, Vec2 p3){
	double a1 = p2.x - p1.x;
	double b1 = p2.y - p1.y;
	double a2 = p3.x - p1.x;
	double b2 = p3.y - p1.y;
	double t = a1*b2 - a2*b1;
	if (abs(t)<eps) return 0;
	if (t>eps) return 1;
	else return -1;
}

void addImage(Node* target, char* url, int x, int y, int order){
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create(url);
	sprite->setPosition(Vec2(origin.x + x, origin.y + y));
	target->addChild(sprite, order);
}

void addText(Node* target,char* str, int x, int y, int order,int tag){
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto label = LabelTTF::create(str, "Arial", 24);
    label->setPosition(Vec2(origin.x + x, origin.y + y));
	label->setTag(tag);
	target->addChild(label, order);
}


Poly::Poly(){
	size=0;
}

void Poly::push_back(Vec2 v){
	V[size]=v;
	size++;
}

bool Poly::inside(Vec2 p){
	for(int i=0;i<size;i++){
		if (CCW(V[i],V[(i+1)%size],p)<0) return false;
	}
	return true;
}