#ifndef FLAPPYBIRDANDROID_COLUMN_GAME_OBJECT_H
#define FLAPPYBIRDANDROID_COLUMN_GAME_OBJECT_H

#include "game_object.h"
#include <glm/glm.hpp>

class BirdGameObject;
class Game;
class ColumnGameObject final : public GameObject
{
public:
    ColumnGameObject(glm::vec2 position, float rotInDegrees, glm::vec2 velocity, Animation* animation,
                     const BirdGameObject *bird, Game *game, const glm::vec2 &screenScaling,
                     bool isLowerColumn, int shakeValue);
    ~ColumnGameObject();
    virtual void UpdatePosition(float dt);
    void ResetScoreComputed();

private:
    bool mScoreComputed = false;
    const BirdGameObject *mBird = nullptr;
    Game *mGame = nullptr;
    glm::vec2 mScreenScaling;
    bool mIsLowerColumn = false;
};

#endif //FLAPPYBIRDANDROID_COLUMN_GAME_OBJECT_H
