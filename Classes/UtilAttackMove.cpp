/*
 * FadeRotateRy.cpp
 *
 *  Created on: 2014-7-7
 *      Author: LarryShi
 */
#include "UtilAttackMove.h"
USING_NS_CC;

Sequence* UtilAttackMove::create(float time, float x1, float y1, float x2, float y2){
	
	float tmp1 = x2-x1;
	float tmp2 = y2-y1;

	auto r4 = MoveTo::create(time / 8, Vec2(x1 + tmp1 / 32, y1 + tmp2 / 32));
	auto r5 = MoveTo::create(time / 8, Vec2(x1 + tmp1 / 16, y1 + tmp2 / 16));
	auto r6 = MoveTo::create(time / 8, Vec2(x1 + tmp1 / 8, y1 + tmp2 / 8));
	auto r7 = MoveTo::create(time / 8, Vec2(x1 + tmp1 / 4, y1 + tmp2 / 4));
	auto r8 = MoveTo::create(time / 8, Vec2(x1 + tmp1 / 2, y1 + tmp2 / 2));
	auto r9 = MoveTo::create(time / 8, Vec2(x1 + tmp1, y1 + tmp2));

	return Sequence::create(r4, r5, r6, r7, r8, r9, NULL);
}