/*
 * FadeRotateRy.h
 *
 *  Created on: 2014-7-7
 *      Author: LarryShi
 */
#include "cocos2d.h"


#ifndef BeingAttack_H_
#define BeingAttack_H_

class UtilBeingAttack : public cocos2d::Sequence{

public:
	static Sequence* create(float time, float scal);
};

#endif /* BeingAttack_H_ */
