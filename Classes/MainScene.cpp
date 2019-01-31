/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// TODO: Set text to YOU WIN!
    winText = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	winText->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - winText->getContentSize().height));
	this->addChild(winText, 2);

    auto slotMachine = Sprite::create("SlotMachine.png");
	slotMachine->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(slotMachine);

	auto arrow = Sprite::create("arrow.png");
	arrow->setPosition(Vec2(60, slotMachine->getContentSize().height / 2));
	slotMachine->addChild(arrow, 1);

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
	auto xSlotPositionOffset = -41;
	auto ySlotPositionOffset = 236;
	auto distanceBetweenSlotCols = 200;

	for (int i = 1; i <= 3; i++) {
		auto slot = Sprite::create("SlotBG.png");
		slot->setPosition(Vec2(i * distanceBetweenSlotCols + xSlotPositionOffset, ySlotPositionOffset));

		slotMachine->addChild(slot);
	}

    return true;
}

void MainScene::onKnobPress(EventMouse* event)
{
	isKnobPressed = true;
	knob->setVisible(false);
	knobDown->setVisible(true);
}

void MainScene::onKnobRelease(EventMouse* event)
{
	if (!isKnobPressed) return;

	isKnobPressed = false;

	// TODO: Insert coin, start rolling
}

void MainScene::onKnobHover(EventMouse* event)
{
	auto cursorX = event->getCursorX() - 45;
	auto cursorY = event->getCursorY() - 130;

	if (event->getCurrentTarget()->getBoundingBox().containsPoint(Vec2(cursorX, cursorY))) {
		knob->setTexture("KnobGlowHL.png");
	}
	else {
		knob->setTexture("knob1.png");
	}
}
