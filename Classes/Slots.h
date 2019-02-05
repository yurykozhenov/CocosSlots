#ifndef COCOSSLOTS_SLOTS_H
#define COCOSSLOTS_SLOTS_H

#include "cocos2d.h"

class SlotMachine;

class Slots
{
public:
    Slots(SlotMachine*);

    virtual void spin(int, const std::function<void()>&);
    virtual void reset();

private:
    int currentSlots[3];
    float distanceBetweenSlots;
    float slotAnimationSpeed;
    cocos2d::Sprite* slots[3][5];
    SlotMachine* slotMachine;

    virtual void spinSingleSlot(int);
};


#endif //COCOSSLOTS_SLOTS_H
