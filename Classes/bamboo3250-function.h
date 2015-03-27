#ifndef __BAMBOO3250_FUNCTION_H__
#define __BAMBOO3250_FUNCTION_H__

#include "cocos2d.h"
#include <fstream>
#define eps 0.0000001

USING_NS_CC;
using namespace std;

int CCW(Vec2 p1, Vec2 p2, Vec2 p3);
void addImage(Node* target, char* url, int x, int y, int order);
void addText(Node* target,char* str, int x, int y, int order,int tag);

class Poly{
private:
	Vec2 V[4];
	int size;
public:
	Poly();
	void push_back(Vec2 v);
	bool inside(Vec2 p);
};

#endif
