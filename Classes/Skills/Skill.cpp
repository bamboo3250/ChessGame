#include "Skill.h"

void Skill::refresh(){
	manaCost = baseManaCost + manaCostGrowth*level;
	pow = basePow + powGrowth*level;
	cd = baseCd + cdGrowth*level;
}