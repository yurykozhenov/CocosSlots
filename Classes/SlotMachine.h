#ifndef COCOSSLOTS_SLOTMACHINE_H
#define COCOSSLOTS_SLOTMACHINE_H

#include "cocos2d.h"
#include "WinText.h"
#include "Token.h"
#include "Slots.h"
#include "Knob.h"

class SlotMachine
{
public:
    cocos2d::Sprite* sprite;

    SlotMachine(WinText*, Token*);

    virtual void start();

private:
    int attempts;
    WinText* winText;
    Token* token;
    Slots* slots;
    Knob* knob;

    virtual void onSpinEnd();
};


#endif //COCOSSLOTS_SLOTMACHINE_H
