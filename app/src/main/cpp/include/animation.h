#ifndef FLAPPYBIRDANDROID_ANIMATION_H
#define FLAPPYBIRDANDROID_ANIMATION_H

#include <vector>
#include "sprite.h"

class Animation final
{
public:
    Animation(std::vector<Sprite*> sprites, float animSpeed);
    ~Animation();

    const Sprite* GetFrame(float dt);
    const Sprite* GetSprite(unsigned int index) const;
    void Reset();
    void Clear();

private:
    std::vector<Sprite*> mSprites;

    float mCount = 0.0f;
    int mIndex = 0;

    //sprites per second
    float mAnimSpeed = 0.0f;

    //time between sprites
    float mAnimTime;
};

#endif //FLAPPYBIRDANDROID_ANIMATION_H
