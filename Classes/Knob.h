#ifndef COCOSSLOTS_KNOB_H
#define COCOSSLOTS_KNOB_H

#include "cocos2d.h"

class SlotMachine;

class Knob
{
public:
    cocos2d::Sprite* sprite;

    Knob(SlotMachine*);

    virtual void reset();

private:
    bool isKnobPressed;
    bool isKnobDown;
    SlotMachine* slotMachine;
    cocos2d::Vec2 initialPosition;
    cocos2d::Vec2 downPosition;

    virtual void onPress(cocos2d::EventMouse*);
    virtual void onRelease(cocos2d::EventMouse*);
    virtual void onHover(cocos2d::EventMouse*);
};


#endif //COCOSSLOTS_KNOB_H
