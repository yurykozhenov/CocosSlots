#include "Knob.h"
#include "SlotMachine.h"

USING_NS_CC;

Knob::Knob(SlotMachine* slotMachine)
{
    this->slotMachine = slotMachine;

    auto slotMachineSize = slotMachine->sprite->getContentSize();
    initialPosition = Vec2(slotMachineSize.width - 41, slotMachineSize.height - 148);
    downPosition = Vec2(slotMachineSize.width - 41, slotMachineSize.height - 234);

    sprite = Sprite::create("knob1.png");
    sprite->setPosition(initialPosition);

    // Attach mouse listener to knob
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(Knob::onPress, this);
    listener->onMouseUp = CC_CALLBACK_1(Knob::onRelease, this);
    listener->onMouseMove = CC_CALLBACK_1(Knob::onHover, this);
    sprite->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);

    isKnobDown = false;
}

void Knob::reset()
{
    isKnobDown = false;
    sprite->setTexture("knob1.png");
    sprite->setPosition(initialPosition);
};

void Knob::onPress(EventMouse* event)
{
    if (isKnobDown) return;

    isKnobPressed = true;
}

void Knob::onRelease(EventMouse* event)
{
    if (!isKnobPressed) return;

    isKnobPressed = false;
    isKnobDown = true;
    sprite->setTexture("KnobDown.png");
    sprite->setPosition(downPosition);

    slotMachine->start();
}

void Knob::onHover(EventMouse* event)
{
    if (isKnobDown) return;

    auto cursorX = event->getCursorX() - 45;
    auto cursorY = event->getCursorY() - 130;

    if (event->getCurrentTarget()->getBoundingBox().containsPoint(Vec2(cursorX, cursorY)))
    {
        sprite->setTexture("KnobGlowHL.png");
    }
    else
    {
        sprite->setTexture("knob1.png");
    }
}
