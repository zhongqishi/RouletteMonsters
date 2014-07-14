/*
 * FadeRotateRy.cpp
 *
 *  Created on: 2014-7-7
 *      Author: LarryShi
 */
#define circlesToTurn 6
#include "UtilFadeRotateRy.h"
USING_NS_CC;

Sequence* UtilFadeRotateRy::create(float deltaAngle,float time){
	auto r2 = RotateBy::create(time/16, 30);
	auto r3 = RotateBy::create(time / 16, 60);
	auto r4 = RotateBy::create(time / 16, 105);
	auto r5 = RotateBy::create(time / 16, 150);

	auto r6 = RotateBy::create(time/2, circlesToTurn * 360 + deltaAngle);
	auto r7 = RotateBy::create(time / 16, 150);
	auto r8 = RotateBy::create(time / 16, 105);

	auto r9 = RotateBy::create(time / 16, 60);
	auto r10 = RotateBy::create(time / 16, 30);


	return Sequence::create(r2, r3, r4, r5, r6, r7, r8, r9, r10, NULL);
}