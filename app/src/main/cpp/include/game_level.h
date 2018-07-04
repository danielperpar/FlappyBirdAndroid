#ifndef FLAPPYBIRDANDROID_GAME_LEVEL_H
#define FLAPPYBIRDANDROID_GAME_LEVEL_H

#include <deque>
#include <utility>
#include <string>
#include <glm/glm.hpp>
#include <vector>

class ColumnGameObject;
class SpriteRenderer;
class Game;
class BirdGameObject;
class Animation;
typedef std::pair<ColumnGameObject*, ColumnGameObject*> ColumnPair;

class GameLevel final
{
public:
    GameLevel(int screenWidth, int screenHeight, const glm::vec2 &screenScaling, int shiftSpeedX,
              const SpriteRenderer *spriteRenderer, const std::string &flappyBirdSpriteAtlasName,
              Game *game, const BirdGameObject *bird, int shakeValue);
    ~GameLevel();
    void UpdateColumnsPosition(float dt);
    void DrawLevel(float dt) const;
    void Reset();
    void PrepareShake();
    void BeginShake();
    void EndShake();
    const ColumnPair& GetColumnPair(unsigned int index) const;
    int GetNumColumnPairs();

private:
    std::deque<ColumnPair> mColumns;
    int mNumColumnPairs = 10;
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    glm::vec2 mScreenScaling;
    int mVerticalSeparation = 0;
    int mMinVerticalPos = 0;
    int mMaxVerticalPos = 0;
    int mPassThreshold = 0;
    float mShiftSpeedX = 0.0f;
    const SpriteRenderer *mSpriteRenderer = nullptr;
    int mSpriteHeight = 0;
    int mSpriteWidth = 0;
    const std::string &mFlappyBirdSpriteAtlasName;
    Game *mGame = nullptr;
    const BirdGameObject *mBird = nullptr;
    int mFactorHorizSeparation = 0;
    int mShakeValue = 0;

    void Init();
    void InitProperties();
    void CreateLevel();
    void ResetColumnPairPosition();
    void Clear();
    float ComputeXPos(const glm::vec2 &posLowerLeft, float posUpperLeftY, float posLowerRightY, float posUpperRightY) const;
};

#endif //FLAPPYBIRDANDROID_GAME_LEVEL_H
