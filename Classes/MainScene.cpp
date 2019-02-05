#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "SlotMachine.h"
#include "WinText.h"
#include "Token.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto winText = new WinText();
    addChild(winText->label, 1000);

    auto token = new Token();
    addChild(token->sprite, 1);

    auto slotMachine = new SlotMachine(winText, token);
    addChild(slotMachine->sprite);

    return true;
}
