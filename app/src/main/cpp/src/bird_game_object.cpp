#include "bird_game_object.h"
#include <glm/glm.hpp>
#include "resource_manager.h"
#include "string_literals.h"

BirdGameObject::BirdGameObject(glm::vec2 position,
                               float rotInDegrees,
                               glm::vec2 velocity,
                               int worldGravity,
                               Animation* animation,
                               const glm::vec2 &screenScaling,
                               int shakeValue) : mWorldGravity(worldGravity), mScreenScaling(screenScaling), GameObject(position, rotInDegrees, velocity, animation, shakeValue)
{
    InitProperties();
}

BirdGameObject::~BirdGameObject() {}

void BirdGameObject::JumpPressed()
{
    mJumpPressed = true;
}

void BirdGameObject::UpdatePosition(float dt)
{
    mVelocity.y += mWorldGravity * dt;
    mPosition.y += mVelocity.y * dt;
    mFallingTime += dt;

    if (mJumpPressed)
    {
        mVelocity.y += mJumpVelocityFactor * mWorldGravity;
        mJumpPressed = false;
        mFallingTime = 0.0f;
        mFalling = false;
    }

    mVelocity.y = glm::clamp(mVelocity.y, mMinVelocity * mScreenScaling.y, mMaxVelocity * mScreenScaling.y);

    if (mFalling && mFallingTime >= mTimeToStartRotation)
    {
        mRotInDegrees =  mMinRotation * (mFallingTime - mTimeToStartRotation) / mTimeToMinRotation;
        mRotInDegrees = glm::clamp(mRotInDegrees, mMinRotation, mMaxRotation);
    }
    else if(!mFalling)
    {
        mRotInDegrees += mRotSpeeedNotFalling * dt;
        if (mRotInDegrees >= mMaxRotation)
        {
            mRotInDegrees = mMaxRotation;
            mFalling = true;
        }
    }
}

void BirdGameObject::Hover(float dt)
{
    mTimer += dt;
    if (mTimer > 60.0f)
    {
        mTimer = 0.0f;
    }
    mPosition.y += mMaxHoverAmp * mScreenScaling.y * glm::sin(mHoverSpeed * mTimer) * dt;
}

void BirdGameObject::InitProperties()
{
    mWorldGravity *= mScreenScaling.y;

    mJumpVelocityFactor = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_JumpVelocityFactor());
    mMinVelocity = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_MinVelocity());
    mMaxVelocity = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_MaxVelocity());
    mMinRotation = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_MinRotation());
    mMaxRotation = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_MaxRotation());
    mTimeToStartRotation = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_TimeToStartRotation());
    mTimeToMinRotation = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_TimeToMinRotation());
    mRotSpeeedNotFalling = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_RotSpeeedNotFalling());
    mHoverSpeed = ResourceManager::GetPropFloat(StringLiterals::GetBirdGameObject_HoverSpeed());
    mMaxHoverAmp = ResourceManager::GetPropInt(StringLiterals::GetBirdGameObject_MaxHoverAmp());
}