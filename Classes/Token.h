#ifndef COCOSSLOTS_TOKEN_H
#define COCOSSLOTS_TOKEN_H

#include "cocos2d.h"

class Token
{
public:
    cocos2d::Sprite* sprite;

    Token();

    virtual void insert(cocos2d::Vec2, const std::function<void()>&);
};


#endif //COCOSSLOTS_TOKEN_H
