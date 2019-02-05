#ifndef COCOSSLOTS_SLOTCOLUMN_H
#define COCOSSLOTS_SLOTCOLUMN_H

#include "cocos2d.h"

class SlotColumn
{
public:
    cocos2d::Node* node;

    SlotColumn(cocos2d::Vec2, float, float);

    virtual void spin(int);
    virtual void reset(int);
private:
    std::vector<cocos2d::Sprite*> slots;
    float distanceBetweenSlots;
    float slotAnimationSpeed;
};


#endif //COCOSSLOTS_SLOTCOLUMN_H
