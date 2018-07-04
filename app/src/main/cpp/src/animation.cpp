#include "animation.h"
#include <iostream>
#include "globals.h"

Animation::Animation(std::vector<Sprite*> sprites, float animSpeed) : mSprites(sprites), mAnimSpeed(animSpeed)
{
    mAnimTime = 1.0f / mAnimSpeed;
}

Animation::~Animation()
{
    Clear();
}

const Sprite* Animation::GetFrame(float dt)
{
    Sprite *sprite = mSprites[mIndex];
    mCount += dt;
    if (mCount >= mAnimTime)
    {
        mCount = 0.0f;
        mIndex++;
        if (mIndex >= mSprites.size())
        {
            mIndex = 0;
        }
    }
    return sprite;
}

const Sprite* Animation::GetSprite(unsigned int index) const
{
    return mSprites[index];
}

void Animation::Reset()
{
    mIndex = 0;
    mCount = 0.0f;
}

void Animation::Clear()
{
    for (std::vector<Sprite*>::iterator it = mSprites.begin(); it != mSprites.end(); it++)
    {
        DELETE_PTR(*it);
    }
    mSprites.clear();
}