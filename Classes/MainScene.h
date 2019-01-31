#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void onKnobPress(cocos2d::EventMouse*);
	virtual void onKnobRelease(cocos2d::EventMouse*);
	virtual void onKnobHover(cocos2d::EventMouse*);

    CREATE_FUNC(MainScene);

private:
	bool isKnobPressed;
	bool isKnobDown;
	int currentSlots[3];
	int attempts;
	int distanceBetweenSlots;
	float slotAnimationSpeed;
	cocos2d::Sprite* knob;
	cocos2d::Sprite* knobDown;
	cocos2d::Sprite* token;
	cocos2d::Sprite* slots[3][5];
	cocos2d::Label* winText;

	virtual void startSlotMachine();
	virtual void spinSlots();
	virtual void spinSingleSlot(int);
};

#endif // __HELLOWORLD_SCENE_H__
