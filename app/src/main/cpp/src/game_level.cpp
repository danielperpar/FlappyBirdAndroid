#include "game_level.h"
#include <glm/glm.hpp>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "sprite.h"
#include "animation.h"
#include "column_game_object.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "globals.h"
#include "string_literals.h"

GameLevel::GameLevel(int screenWidth, int screenHeight, const glm::vec2 &screenScaling, int shiftSpeedX,
                     const SpriteRenderer *spriteRenderer, const std::string &flappyBirdSpriteAtlasName, Game *game,
                     const BirdGameObject *bird, int shakeValue) :
        mScreenWidth(screenWidth),
        mScreenHeight(screenHeight),
        mScreenScaling(screenScaling),
        mShiftSpeedX(shiftSpeedX),
        mSpriteRenderer(spriteRenderer),
        mFlappyBirdSpriteAtlasName(flappyBirdSpriteAtlasName),
        mGame(game),
        mBird(bird),
        mShakeValue(shakeValue)
{
    mShiftSpeedX *= mScreenScaling.x;
    Init();
}

GameLevel::~GameLevel()
{
    Clear();
}

void GameLevel::Init()
{
    InitProperties();
    CreateLevel();
}

void GameLevel::InitProperties()
{
    mVerticalSeparation = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_ColumnVerticalSeparation());
    mMinVerticalPos = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_MinVerticalPos());
    mMaxVerticalPos = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_MaxVerticalPos());
    mPassThreshold = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_PassThreshold());
    mNumColumnPairs = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_NumColumnPairs());
    mFactorHorizSeparation = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_FactorHorizSeparation());
    mSpriteWidth = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_SpriteWidth());
    mSpriteHeight = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_SpriteHeight());
}

void GameLevel::CreateLevel()
{
    int lowerColX = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_LowerColX());
    int lowerColY = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_LowerColY());

    int upperColX = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_UpperColX());
    int upperColY = ResourceManager::GetPropInt(StringLiterals::GetGameLevel_UpperColY());

    float posXUpperLower;
    float posYLower;
    float separationDistanceY = mVerticalSeparation * mScreenScaling.y;
    glm::vec2 posLowerCol;
    glm::vec2 posUpperCol;

    srand(time(NULL));

    for (int i = 0; i < mNumColumnPairs; i++)
    {
        if (i != 0)
        {
            posYLower = mMinVerticalPos + (mMaxVerticalPos - mMinVerticalPos) * (float)rand() / (float)RAND_MAX;
            posYLower *= mScreenScaling.y;
            ColumnPair &pair = mColumns.back();
            posXUpperLower = ComputeXPos(pair.first->GetPosition(), pair.second->GetPosition().y, posYLower, posYLower + mSpriteHeight * mScreenScaling.y + separationDistanceY);
        }
        else
        {
            posXUpperLower = (float)mScreenWidth;
            posYLower = 0.0f;
        }

        posLowerCol.x = posXUpperLower;
        posLowerCol.y = posYLower;
        Sprite *lowerColumnSprite = new Sprite(ResourceManager::GetTexture(mFlappyBirdSpriteAtlasName), lowerColX, lowerColY, mSpriteWidth, mSpriteHeight);
        std::vector<Sprite*> lowerColumnSpriteVector = { lowerColumnSprite };
        Animation *lowerColumnAnim = new Animation(lowerColumnSpriteVector, 0.0f);
        ColumnGameObject *lowerColumnGO = new ColumnGameObject(posLowerCol, 0.0f, glm::vec2(mShiftSpeedX, 0.0f), lowerColumnAnim, mBird, mGame, mScreenScaling, true, mShakeValue);

        posUpperCol.x = posXUpperLower;
        posUpperCol.y = posYLower + mSpriteHeight * mScreenScaling.y + separationDistanceY;
        Sprite *upperColumnSprite = new Sprite(ResourceManager::GetTexture(mFlappyBirdSpriteAtlasName), upperColX, upperColY, mSpriteWidth, mSpriteHeight);
        std::vector<Sprite*> upperColumnSpriteVector = { upperColumnSprite };
        Animation *upperColumnAnim = new Animation(upperColumnSpriteVector, 0.0f);
        ColumnGameObject *upperColumnGO = new ColumnGameObject(posUpperCol, 0.0f, glm::vec2(mShiftSpeedX, 0.0f), upperColumnAnim, mBird, mGame, mScreenScaling, false, mShakeValue);

        ColumnPair columnPair = std::make_pair(lowerColumnGO, upperColumnGO);
        mColumns.push_back(columnPair);
    }
}

void GameLevel::UpdateColumnsPosition(float dt)
{
    for (ColumnPair &pair : mColumns)
    {
        pair.first->UpdatePosition(dt);
        pair.second->UpdatePosition(dt);
    }

    ColumnPair &firstPair = mColumns.front();

    //Sprite is out of the screen boundaries
    if (firstPair.first->GetPosition().x + mSpriteWidth * mScreenScaling.x < 0.0f)
    {
        ResetColumnPairPosition();
    }
}

void GameLevel::ResetColumnPairPosition()
{
    ColumnPair columnOut = mColumns.front();
    mColumns.pop_front();

    float posYLower = mMinVerticalPos + (mMaxVerticalPos - mMinVerticalPos) * (float)rand() / (float)RAND_MAX;
    posYLower *= mScreenScaling.y;

    float separationDistanceY = mVerticalSeparation * mScreenScaling.y;

    ColumnPair &lastPair = mColumns.back();

    float posX = ComputeXPos(lastPair.first->GetPosition(), lastPair.second->GetPosition().y, posYLower, posYLower + mSpriteHeight * mScreenScaling.y + separationDistanceY);

    glm::vec2 posLowerCol(posX, posYLower);
    glm::vec2 posUpperCol(posX, posYLower + mSpriteHeight * mScreenScaling.y + separationDistanceY);

    columnOut.first->SetPosition(posLowerCol);
    columnOut.second->SetPosition(posUpperCol);

    columnOut.first->ResetScoreComputed();

    mColumns.push_back(columnOut);
}

void GameLevel::DrawLevel(float dt) const
{
    for (const ColumnPair &pair : mColumns)
    {
        if (pair.first->GetPosition().x > mScreenWidth)
        {
            break;
        }
        pair.first->Draw(mSpriteRenderer, dt);
        pair.second->Draw(mSpriteRenderer, dt);
    }
}

void GameLevel::Reset()
{
    float posX;
    float posYLower;
    float separationDistanceY = mVerticalSeparation * mScreenScaling.y;

    glm::vec2 posLowerCol;
    glm::vec2 posUpperCol;

    for (int i = 0; i < mNumColumnPairs; i++)
    {
        if (i == 0)
        {
            //Reset first column pair
            posX = (float)mScreenWidth;
            posYLower = 0.0f;
        }
        else
        {
            ColumnPair &previousPair = mColumns[i-1];

            posYLower = mMinVerticalPos + (mMaxVerticalPos - mMinVerticalPos) * (float)rand() / (float)RAND_MAX;
            posYLower *= mScreenScaling.y;

            posX = ComputeXPos(previousPair.first->GetPosition(), previousPair.second->GetPosition().y, posYLower, posYLower + mSpriteHeight * mScreenScaling.y + separationDistanceY);
        }

        //Lower column
        mColumns[i].first->SetPosition(glm::vec2(posX, posYLower));

        //Upper column
        mColumns[i].second->SetPosition(glm::vec2(posX, posYLower + mSpriteHeight * mScreenScaling.y + separationDistanceY));
    }
}

void GameLevel::PrepareShake()
{
    for (int i = 0; i < mColumns.size(); i++)
    {
        mColumns[i].first->PrepareShake();
        mColumns[i].second->PrepareShake();
    }
}

void GameLevel::BeginShake()
{
    for (int i = 0; i < mColumns.size(); i++)
    {
        mColumns[i].first->BeginShake();
        mColumns[i].second->BeginShake();
    }
}

void GameLevel::EndShake()
{
    for (int i = 0; i < mColumns.size(); i++)
    {
        mColumns[i].first->EndShake();
        mColumns[i].second->EndShake();
    }
}

//getters
const ColumnPair& GameLevel::GetColumnPair(unsigned int index) const
{
    return mColumns[index];
}

int GameLevel::GetNumColumnPairs()
{
    return mNumColumnPairs;
}

//private methods
void GameLevel::Clear()
{
    for (int i = 0; i < mNumColumnPairs; i++)
    {
        ColumnPair &pair = mColumns[i];
        DELETE_PTR(pair.first);
        DELETE_PTR(pair.second);
    }
    mColumns.clear();
}

//In case column pairs are generated too close to each another,
// ComputeXPos() checks if there is enough space between column
// pairs to allow the bird pass through them. If it is not enough,
// it spreads the columns according to a configuration factor.
/*
 * Left      Right
 * ColPair   ColPair
 * |    |    |____|
 * |    |
 * |____|     ____
 *           |    |
 * |----|    |    |
 * |    |    |    |
 * |    |    |    |
 */
float GameLevel::ComputeXPos(const glm::vec2 &posLowerLeft, float posUpperLeftY, float posLowerRightY, float posUpperRightY) const
{
    //highest point of the lower left column
    float topLowerLeftColumn =  posLowerLeft.y + mSpriteHeight * mScreenScaling.y;
    //highest point of the lower right column
    float topLowerRightColumn = posLowerRightY + mSpriteHeight * mScreenScaling.y;

    if (topLowerRightColumn >= topLowerLeftColumn)
    {
        if (posUpperLeftY - topLowerRightColumn < mPassThreshold * mScreenScaling.y)
        {
            return posLowerLeft.x + mFactorHorizSeparation * mSpriteWidth * mScreenScaling.x;
        }

        return posLowerLeft.x + (rand() % mFactorHorizSeparation + 1) * mSpriteWidth * mScreenScaling.x;
    }
    else
    {
        if (posUpperRightY - topLowerLeftColumn < mPassThreshold * mScreenScaling.y)
        {
            return posLowerLeft.x + mFactorHorizSeparation * mSpriteWidth * mScreenScaling.x;
        }

        return posLowerLeft.x + (rand() % mFactorHorizSeparation + 1) * mSpriteWidth * mScreenScaling.x;
    }
}
