#include "SlotMachine.h"
#include "Knob.h"

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

    knob = new Knob(this);
    sprite->addChild(knob->sprite, 3);

    // Add 3 slot columns
    slotColumnsSize = 3;
    auto distanceBetweenSlotCols = 200.0f;
    auto distanceBetweenSlots = 200.0f;
    slotAnimationSpeed = 0.5f;

    for (int i = 0; i < slotColumnsSize; i++)
    {
        float xPosition = (i + 1) * distanceBetweenSlotCols - 41.0f;
        float yPosition = 236.0f;

        slotColumns[i] = new SlotColumn(Vec2(xPosition, yPosition), distanceBetweenSlots, slotAnimationSpeed);
        sprite->addChild(slotColumns[i]->node, 0);
    }

    attempts = 0;

    for (int i = 0; i < slotColumnsSize; i++)
    {
        currentSlots[i] = 0;
    }
}

void SlotMachine::start()
{
    attempts++;
    winText->label->setVisible(false);
    resetSlots();

    token->insert(Vec2(820, 380), [this]() { spinSlots(); });
}

void SlotMachine::spinSlots()
{
    // For demonstration purposes, make player win on third attempt
    if (attempts == 3)
    {
        int randomNumber = random(1, 4);
        for (int i = 0; i < slotColumnsSize; i++)
        {
            currentSlots[i] = randomNumber;
        }
    }
    else
    {
        for (int i = 0; i < slotColumnsSize; i++)
        {
            currentSlots[i] = random(1, 4);
        }
    }

    // TODO: It would be nice to use loop here
    sprite->runAction(Sequence::create(
        CallFunc::create([this]() { slotColumns[0]->spin(currentSlots[0]); }),
        DelayTime::create(currentSlots[0] * slotAnimationSpeed),
        CallFunc::create([this]() { slotColumns[1]->spin(currentSlots[1]); }),
        DelayTime::create(currentSlots[1] * slotAnimationSpeed),
        CallFunc::create([this]() { slotColumns[2]->spin(currentSlots[2]); }),
        DelayTime::create(currentSlots[2] * slotAnimationSpeed),
        CallFunc::create([this] { onSpinEnd(); }),
        nullptr
    ));
}

void SlotMachine::resetSlots()
{
    for (int i = 0; i < slotColumnsSize; i++)
    {
        slotColumns[i]->reset(currentSlots[i]);
    }
}

void SlotMachine::onSpinEnd()
{
    knob->reset();

    // Check win condition
    if (!(currentSlots[0] == currentSlots[1] &&
          currentSlots[1] == currentSlots[2]))
        return;

    winText->label->setVisible(true);
}
