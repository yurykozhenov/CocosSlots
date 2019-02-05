#include "WinText.h"

USING_NS_CC;

WinText::WinText()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    label = Label::createWithTTF("YOU WIN!", "fonts/Marker Felt.ttf", 60);
    label->enableShadow();
    label->setColor(Color3B(255, 215, 0));
    label->setPosition(Vec2(
        visibleSize.width / 2 + origin.x,
        visibleSize.height + origin.y - label->getContentSize().height
    ));
    label->setVisible(false);
}
