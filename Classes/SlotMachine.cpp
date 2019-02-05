#include "SlotMachine.h"
#include "Knob.h"
#include "Slots.h"

USING_NS_CC;

SlotMachine::SlotMachine(WinText* winText, Token* token)
{
    this->winText = winText;
    this->token = token;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    sprite = Sprite::create("SlotMachine.png");
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto slotMachineSize = sprite->getContentSize();

    auto arrow = Sprite::create("arrow.png");
    arrow->setPosition(Vec2(60, slotMachineSize.height / 2));
    sprite->addChild(arrow, 3);

    attempts = 0;

    knob = new Knob(this);
    sprite->addChild(knob->sprite, 3);

    slots = new Slots(this);
    // TODO: Add slots to slot machine
}

void SlotMachine::start()
{
    attempts++;
    winText->label->setVisible(false);

    slots->reset();
    token->insert(Vec2(820, 380), [this]() { slots->spin(attempts, [this]() { onSpinEnd(); }); });
}

void SlotMachine::onSpinEnd()
{
    knob->reset();

    // Check win condition
//    if (!(currentSlots[0] == currentSlots[1] &&
//          currentSlots[1] == currentSlots[2]))
//        return;
//
//    winText->label->setVisible(true);
}
