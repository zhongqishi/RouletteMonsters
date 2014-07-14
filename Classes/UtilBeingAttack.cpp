/*
 * FadeRotateRy.cpp
 *
 *  Created on: 2014-7-7
 *      Author: LarryShi
 */
#include "UtilBeingAttack.h"
USING_NS_CC;

Sequence* UtilBeingAttack::create(float time, float scal){
	auto r1 = RotateBy::create(time*0.875, 0);
	auto r2 = ScaleBy::create(0.05f, scal*0.99);
	auto r3 = ScaleTo::create(0.125f, scal);
	
	return Sequence::create(r1, r2, r3, NULL);
}