#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// TODO: Place slot sprites under slot machine
bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    winText = Label::createWithTTF("YOU WIN!", "fonts/Marker Felt.ttf", 60);
    winText->enableShadow();
    winText->setColor(Color3B(255, 215, 0));
    winText->setPosition(Vec2(
        visibleSize.width / 2 + origin.x,
        visibleSize.height + origin.y - winText->getContentSize().height
    ));
    winText->setVisible(false);
    addChild(winText, 1000);

    auto slotMachine = Sprite::create("SlotMachine.png");
    slotMachine->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(slotMachine);

    auto arrow = Sprite::create("arrow.png");
    arrow->setPosition(Vec2(60, slotMachine->getContentSize().height / 2));
    slotMachine->addChild(arrow, 3);

    token = Sprite::create("token.png");
    token->setVisible(false);
    slotMachine->addChild(token, 5);

    knob = Sprite::create("knob1.png");
    knob->setPosition(Vec2(slotMachine->getContentSize().width - 41, slotMachine->getContentSize().height - 148));
    slotMachine->addChild(knob);

    knobDown = Sprite::create("KnobDown.png");
    knobDown->setPosition(Vec2(slotMachine->getContentSize().width - 41, slotMachine->getContentSize().height - 232));
    knobDown->setVisible(false);
    slotMachine->addChild(knobDown);

    // Attach mouse listener to knob
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(MainScene::onKnobPress, this);
    listener->onMouseUp = CC_CALLBACK_1(MainScene::onKnobRelease, this);
    listener->onMouseMove = CC_CALLBACK_1(MainScene::onKnobHover, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, knob);

    // Add 3 slot columns
    auto distanceBetweenSlotCols = 200;
    distanceBetweenSlots = 200;

    for (int i = 0; i < 3; i++)
    {
        auto xPosition = (i + 1) * distanceBetweenSlotCols - 41;
        auto yPosition = 236;

        auto slotBackground = Sprite::create("SlotBG.png");
        slotBackground->setPosition(Vec2(xPosition, yPosition));
        slotMachine->addChild(slotBackground, 0);

        auto slotFrame = Sprite::create("Frame.png");
        slotFrame->setPosition(Vec2(xPosition, yPosition));
        slotMachine->addChild(slotFrame, 2);

        slots[i][0] = Sprite::create("slot_gold.png");
        slots[i][1] = Sprite::create("slot_feather.png");
        slots[i][2] = Sprite::create("pw_slot.png");
        slots[i][3] = Sprite::create("slot_seven.png");
        slots[i][4] = Sprite::create("slot_tickets.png");

        for (int j = 0; j < 5; j++)
        {
            slots[i][j]->setPosition(Vec2(xPosition, j * distanceBetweenSlots + yPosition));
            slotMachine->addChild(slots[i][j], 1);
        }
    }

    currentSlots[0] = 0;
    currentSlots[1] = 0;
    currentSlots[2] = 0;

    attempts = 0;
    slotAnimationSpeed = 0.5;

    return true;
}

void MainScene::onKnobPress(EventMouse* event)
{
    if (isKnobDown) return;

    isKnobPressed = true;
    knob->setVisible(false);
    knobDown->setVisible(true);
}

void MainScene::onKnobRelease(EventMouse* event)
{
    if (!isKnobPressed) return;

    isKnobPressed = false;
    isKnobDown = true;

    startSlotMachine();
}

void MainScene::onKnobHover(EventMouse* event)
{
    auto cursorX = event->getCursorX() - 45;
    auto cursorY = event->getCursorY() - 130;

    if (event->getCurrentTarget()->getBoundingBox().containsPoint(Vec2(cursorX, cursorY)))
    {
        knob->setTexture("KnobGlowHL.png");
    }
    else
    {
        knob->setTexture("knob1.png");
    }
}

void MainScene::startSlotMachine()
{
    attempts++;

    winText->setVisible(false);

    // Reset slots
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            slots[i][j]->runAction(MoveBy::create(1, Vec2(0, currentSlots[i] * distanceBetweenSlots)));
        }
    }

    // Reset token
    token->setVisible(true);
    token->setOpacity(255);
    token->setTexture("token.png");
    token->setPosition(Vec2(1100, 0));

    // Play token animation, then spin slots
    token->runAction(Sequence::create(
        DelayTime::create(1),
        MoveTo::create(1.5, Vec2(780, 230)),
        CallFunc::create([this]() { token->setTexture("insertToken.png"); }),
        Spawn::create(
            MoveBy::create(0.5, Vec2(-35, 0)),
            FadeOut::create(0.5),
            nullptr
        ),
        CallFunc::create([this]() { spinSlots(); }),
        nullptr
    ));
}

void MainScene::spinSlots()
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

    runAction(Sequence::create(
        CallFunc::create([this]() { spinSingleSlot(0); }),
        DelayTime::create(currentSlots[0] * slotAnimationSpeed),
        CallFunc::create([this]() { spinSingleSlot(1); }),
        DelayTime::create(currentSlots[1] * slotAnimationSpeed),
        CallFunc::create([this]() { spinSingleSlot(2); }),
        DelayTime::create(currentSlots[2] * slotAnimationSpeed),
        CallFunc::create([this]()
        {
            // Reset slot machine state
            isKnobDown = false;
            knob->setVisible(true);
            knobDown->setVisible(false);

            // Check win condition
            if (!(currentSlots[0] == currentSlots[1] && currentSlots[1] == currentSlots[2])) return;

            winText->setVisible(true);
        }),
        nullptr
    ));
}

void MainScene::spinSingleSlot(int targetColumn)
{
    int targetSlot = currentSlots[targetColumn];

    for (int i = 0; i < 5; i++)
    {
        slots[targetColumn][i]->runAction(
            MoveBy::create(slotAnimationSpeed * targetSlot, Vec2(0, targetSlot * -distanceBetweenSlots))
        );
    }
}
