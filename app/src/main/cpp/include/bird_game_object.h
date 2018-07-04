#ifndef FLAPPYBIRDANDROID_BIRD_GAME_OBJECT_H
#define FLAPPYBIRDANDROID_BIRD_GAME_OBJECT_H

#include "game_object.h"
#include <glm/glm.hpp>
#include "animation.h"
#include <string>

class BirdGameObject final : public GameObject
{
public:

    BirdGameObject(glm::vec2 position, float rotInDegrees, glm::vec2 velocity, int worldGravity, Animation* animation, const glm::vec2 &screenScaling, int shakeValue);
    ~BirdGameObject();
    void JumpPressed();
    virtual void UpdatePosition(float dt);
    void Hover(float dt);

private:
    bool mJumpPressed = false;
    float mWorldGravity = 0.0f;
    float mFallingTime = 0.0f;
    bool mFalling = true;
    float mJumpVelocityFactor = 0.0f;
    float mMinVelocity = 0.0f;
    float mMaxVelocity = 0.0f;
    float mMinRotation = 0.0f;
    float mMaxRotation = 0.0f;
    float mTimeToStartRotation = 0.0f;
    float mTimeToMinRotation = 0.0f;
    float mRotSpeeedNotFalling = 0.0f;
    float mHoverSpeed = 0.0f;
    int mMaxHoverAmp = 0;
    float mTimer = 0.0f;
    glm::vec2 mScreenScaling;

    void InitProperties();
};

#endif //FLAPPYBIRDANDROID_BIRD_GAME_OBJECT_H
