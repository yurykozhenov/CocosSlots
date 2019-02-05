#ifndef COCOSSLOTS_SLOTMACHINE_H
#define COCOSSLOTS_SLOTMACHINE_H

#include "cocos2d.h"
#include "WinText.h"
#include "Token.h"
#include "Knob.h"
#include "SlotColumn.h"

class SlotMachine
{
public:
    cocos2d::Sprite* sprite;

    SlotMachine(WinText*, Token*);

    virtual void start();

private:
    int attempts;
    int slotColumnsSize;
    int currentSlots[3];
    float slotAnimationSpeed;
    WinText* winText;
    Token* token;
    SlotColumn* slotColumns[3];
    Knob* knob;

    virtual void spinSlots();
    virtual void resetSlots();
    virtual void onSpinEnd();
};


#endif //COCOSSLOTS_SLOTMACHINE_H
