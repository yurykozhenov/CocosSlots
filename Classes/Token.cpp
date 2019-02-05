#include "Token.h"

USING_NS_CC;

Token::Token()
{
    sprite = Sprite::create("token.png");
    sprite->setVisible(false);
}

void Token::insert(Vec2 holePosition, const std::function<void()>& func)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // Reset token
    sprite->setVisible(true);
    sprite->setOpacity(255);
    sprite->setTexture("token.png");
    sprite->setPosition(Vec2(visibleSize.width + 100, 100));

    // Play token animation, then invoke the callback function
    sprite->runAction(Sequence::create(
        DelayTime::create(1),
        MoveTo::create(1.5, holePosition),
        CallFunc::create([this]() { sprite->setTexture("insertToken.png"); }),
        Spawn::create(
            MoveBy::create(0.5, Vec2(-35, 0)),
            FadeOut::create(0.5),
            nullptr
        ),
        CallFunc::create([this, func]() { func(); }),
        nullptr
    ));
}
