/*
 * FadeRotateRy.h
 *
 *  Created on: 2014-7-7
 *      Author: LarryShi
 */
#include "cocos2d.h"


#ifndef AttackMove_H_
#define AttackMove_H_

class UtilAttackMove : public cocos2d::Sequence{

public:
	static Sequence* create(float time, float x1,float y1,float x2,float y2);
};

#endif /* AttackMove_H_ */
