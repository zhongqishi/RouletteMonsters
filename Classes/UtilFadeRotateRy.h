/*
 * FadeRotateRy.h
 *
 *  Created on: 2014-7-7
 *      Author: LarryShi
 */
#include "cocos2d.h"


#ifndef FADEROTATERY_H_
#define FADEROTATERY_H_

class UtilFadeRotateRy : public cocos2d::Sequence{

public:
	static Sequence* create(float deltaAngle,float time);
};

#endif /* FADEROTATERY_H_ */
