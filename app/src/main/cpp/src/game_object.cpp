#include "game_object.h"
#include "globals.h"

GameObject::GameObject(glm::vec2 position, float rotInDegrees, glm::vec2 velocity, Animation* animation, int shakeValue) :
    mPosition(position),
    mRotInDegrees(rotInDegrees),
    mVelocity(velocity),
    mAnimation(animation),
    mShakeValue(shakeValue){}

GameObject::~GameObject()
{
    Clear();
}

void GameObject::UpdatePosition(float dt){}

void GameObject::Draw(const SpriteRenderer *spriteRenderer, float dt) const
{
    spriteRenderer->DrawSprite(mAnimation->GetFrame(dt), mPosition, mRotInDegrees);
}

void GameObject::PrepareShake()
{
    mPosBeforeShake = mPosition;
}

void GameObject::BeginShake()
{
    mShakeValue = -mShakeValue;
    mPosition.x += mShakeValue;
    mPosition.y += mShakeValue;
}

void GameObject::EndShake()
{
    mPosition = mPosBeforeShake;
}

void GameObject::Clear()
{
    DELETE_PTR(mAnimation);
}


//getters and setters
const glm::vec2& GameObject::GetPosition() const
{
    return mPosition;
}

void GameObject::SetPosition(const glm::vec2 &position)
{
    mPosition = position;
}

float GameObject::GetRotInDegrees() const
{
    return mRotInDegrees;
}

void GameObject::SetRotInDegrees(float rotInDegrees)
{
    mRotInDegrees = rotInDegrees;
}

const glm::vec2& GameObject::GetVelocity() const
{
    return mVelocity;
}

const Animation* GameObject::GetAnimation() const
{
    return mAnimation;
}

int GameObject::GetShakeValue() const
{
    return mShakeValue;
}

const glm::vec2& GameObject::GetPosBeforeShake() const
{
    return mPosBeforeShake;
}