#include "SlotColumn.h"

USING_NS_CC;

SlotColumn::SlotColumn(Vec2 position, float distanceBetweenSlots, float slotAnimationSpeed)
{
    this->distanceBetweenSlots = distanceBetweenSlots;
    this->slotAnimationSpeed = slotAnimationSpeed;

    auto slotBackground = Sprite::create("SlotBG.png");
    slotBackground->setPosition(position);

    auto clipper = ClippingNode::create(slotBackground);
    node = clipper;
    clipper->setAlphaThreshold(0);

    clipper->addChild(slotBackground, 0);

    auto slotFrame = Sprite::create("Frame.png");
    slotFrame->setPosition(position);
    clipper->addChild(slotFrame, 2);

    slots.push_back(Sprite::create("slot_gold.png"));
    slots.push_back(Sprite::create("slot_feather.png"));
    slots.push_back(Sprite::create("pw_slot.png"));
    slots.push_back(Sprite::create("slot_seven.png"));
    slots.push_back(Sprite::create("slot_tickets.png"));

    for (int i = 0, size = slots.size(); i < size; i++)
    {
        slots[i]->setPosition(Vec2(position.x, i * distanceBetweenSlots + position.y));
        clipper->addChild(slots[i], 1);
    }
}

void SlotColumn::spin(int targetSlotValue)
{
    for (auto slot : slots)
    {
        slot->runAction(
            MoveBy::create(slotAnimationSpeed * targetSlotValue, Vec2(0, targetSlotValue * -distanceBetweenSlots))
        );
    }
}

void SlotColumn::reset(int currentSlotValue)
{
    for (auto slot : slots)
    {
        slot->runAction(MoveBy::create(1, Vec2(0, currentSlotValue * distanceBetweenSlots)));
    }
}
