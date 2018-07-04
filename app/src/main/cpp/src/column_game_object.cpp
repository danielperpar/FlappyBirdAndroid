#include "column_game_object.h"
#include "bird_game_object.h"
#include "game.h"

ColumnGameObject::ColumnGameObject(
    glm::vec2 position,
    float rotInDegrees,
    glm::vec2 velocity,
    Animation* animation,
    const BirdGameObject *bird,
    Game *game,
    const glm::vec2 &screenScaling,
    bool isLowerColumn,
    int shakeValue) : mBird(bird), mGame(game), mScreenScaling(screenScaling), mIsLowerColumn(isLowerColumn), GameObject(position, rotInDegrees, velocity, animation, shakeValue) {}

ColumnGameObject::~ColumnGameObject() {}

void ColumnGameObject::UpdatePosition(float dt)
{
    mPosition.x -= mVelocity.x * dt;

    //check if bird scored
    if (mIsLowerColumn)
    {
        float columnRightEdge = mPosition.x + mAnimation->GetSprite(0)->GetWidth() * mScreenScaling.x;
        if (columnRightEdge < mBird->GetPosition().x && !mScoreComputed)
        {
            mGame->ComputeScore();
            mScoreComputed = true;
        }
    }
}

void ColumnGameObject::ResetScoreComputed()
{
    mScoreComputed = false;
}

