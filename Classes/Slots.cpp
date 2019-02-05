#include "Slots.h"
#include "SlotMachine.h"

USING_NS_CC;

// TODO: Remove slot machine here
Slots::Slots(SlotMachine* slotMachine)
{
    this->slotMachine = slotMachine;

    // Add 3 slot columns
    auto distanceBetweenSlotCols = 200;
    distanceBetweenSlots = 200;

    for (int i = 0; i < 3; i++)
    {
        float xPosition = (i + 1) * distanceBetweenSlotCols - 41.0f;
        float yPosition = 236.0f;

        auto slotBackground = Sprite::create("SlotBG.png");
        slotBackground->setPosition(Vec2(xPosition, yPosition));
        slotMachine->sprite->addChild(slotBackground, 0);

        auto clipper = ClippingNode::create(slotBackground);
        clipper->setAlphaThreshold(0);
        slotMachine->sprite->addChild(clipper, 0);

        auto slotFrame = Sprite::create("Frame.png");
        slotFrame->setPosition(Vec2(xPosition, yPosition));
        clipper->addChild(slotFrame, 2);

        slots[i][0] = Sprite::create("slot_gold.png");
        slots[i][1] = Sprite::create("slot_feather.png");
        slots[i][2] = Sprite::create("pw_slot.png");
        slots[i][3] = Sprite::create("slot_seven.png");
        slots[i][4] = Sprite::create("slot_tickets.png");

        for (int j = 0; j < 5; j++)
        {
            slots[i][j]->setPosition(Vec2(xPosition, j * distanceBetweenSlots + yPosition));
            clipper->addChild(slots[i][j], 1);
        }
    }

    currentSlots[0] = 0;
    currentSlots[1] = 0;
    currentSlots[2] = 0;

    slotAnimationSpeed = 0.5;
}

void Slots::spin(int attempts, const std::function<void()>& func)
{
    // For demonstration purposes, make player win on third attempt
    if (attempts == 3)
    {
        int randomNumber = random(1, 4);
        currentSlots[0] = randomNumber;
        currentSlots[1] = randomNumber;
        currentSlots[2] = randomNumber;
    }
    else
    {
        currentSlots[0] = random(1, 4);
        currentSlots[1] = random(1, 4);
        currentSlots[2] = random(1, 4);
    }

    slotMachine->sprite->runAction(Sequence::create(
        CallFunc::create([this]() { spinSingleSlot(0); }),
        DelayTime::create(currentSlots[0] * slotAnimationSpeed),
        CallFunc::create([this]() { spinSingleSlot(1); }),
        DelayTime::create(currentSlots[1] * slotAnimationSpeed),
        CallFunc::create([this]() { spinSingleSlot(2); }),
        DelayTime::create(currentSlots[2] * slotAnimationSpeed),
        CallFunc::create([this, func] { func(); }),
        nullptr
    ));
}

void Slots::reset() {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            slots[i][j]->runAction(MoveBy::create(1, Vec2(0, currentSlots[i] * distanceBetweenSlots)));
        }
    }
}

void Slots::spinSingleSlot(int targetColumn)
{
    int targetSlot = currentSlots[targetColumn];

    for (int i = 0; i < 5; i++)
    {
        slots[targetColumn][i]->runAction(
            MoveBy::create(slotAnimationSpeed * targetSlot, Vec2(0, targetSlot * -distanceBetweenSlots))
        );
    }
}
