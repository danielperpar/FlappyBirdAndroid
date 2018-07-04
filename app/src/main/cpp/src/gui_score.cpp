#include "gui_score.h"
#include "resource_manager.h"
#include "globals.h"
#include "sprite_renderer.h"
#include <fstream>
#include <iostream>
#include <errno.h>
#include "utils.h"
#include <android/log.h>
#include <sstream>
#include "string_literals.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <cstdlib>

GUIScore::GUIScore(int screenWidth, int screenHeight, const glm::vec2 &screenScaling, AAssetManager *assetManager, const std::string &internalPath) :
        mScreenWidth(screenWidth),
        mScreenHeight(screenHeight),
        mScreenScaling(screenScaling),
        mInternalPath(internalPath),
        mAssetManager(assetManager)
{
    Init();
}

GUIScore::~GUIScore()
{
    Clear();
}

void GUIScore::DrawBigScoreNumbers(unsigned int score, const SpriteRenderer *renderer) const
{
    std::string scoreString = stringValue(score);
    int totalLength = 0;
    for (int i = 0; i < scoreString.size(); i++)
    {
        totalLength += mBigNumbers.find(scoreString[i])->second->GetWidth();
    }

    float posX = (mScreenWidth  - totalLength *  mScreenScaling.x) * mFactorScreenWidthBig;
    float posY = mScreenHeight - mFactorScreenHeightBig * mScreenHeight;
    for (int i = 0; i < scoreString.size(); i++)
    {
        Sprite *sprite = mBigNumbers.find(scoreString[i])->second;
        int offset = sprite->GetWidth();
        renderer->DrawSprite(sprite, glm::vec2(posX, posY), 0.0f);
        posX += offset * mScreenScaling.x;
    }
}

bool GUIScore::SlideScoreboard(float dt)
{
    bool ret = false;
    mSBPosY += mAscendSpeed * mScreenScaling.y * dt;
    if (mSBPosY > mSBPosYFinal)
    {
        ret = true;
        mSBPosY = mSBPosYFinal;
    }
    return ret;
}

void GUIScore::DrawScoreBoard(unsigned int score, const SpriteRenderer *renderer)
{
    renderer->DrawSprite(mScoreBoard, glm::vec2(mSBPosXFinal, mSBPosY), 0.0f);

    DrawSmallScoreNumbers(mScoreBoard, glm::vec2(mSBPosXFinal, mSBPosY), score, renderer, false);
    DrawSmallScoreNumbers(mScoreBoard, glm::vec2(mSBPosXFinal, mSBPosY), mBestScore, renderer, true);
}

void GUIScore::SaveMaxScore(unsigned int maxScore)
{
    mBestScore = maxScore;
    FILE *fp = fopen(mInternalPath.c_str(), "w");
    if (!fp)
    {
        __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Error opening score file: %s", strerror(errno));
        return;
    }
    std::string scoreText = "BestScore:" + stringValue(mBestScore);
    const char *buffer = scoreText.c_str();
    fwrite(buffer, sizeof(char), scoreText.length(), fp);
    fclose(fp);
}

unsigned int GUIScore::GetBestScore() const
{
    return mBestScore;
}

void GUIScore::ResetSBHeightPos()
{
    mSBPosY = mSBInitialPosY;
}

void GUIScore::LoadScoreFileName(AAssetManager *assetManager)
{
    AAsset *asset = AAssetManager_open(assetManager, SCOREFILE_PATH, AASSET_MODE_BUFFER);
    if(!asset)
    {
        __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "Error opening config file at: %s", SCOREFILE_PATH);
        return;
    }

    long length = AAsset_getLength(asset);
    char *buffer = (char*)malloc(length * sizeof(char));
    AAsset_read(asset, buffer, length);
    AAsset_close(asset);
    std::stringstream ss;
    ss << buffer;
    free(buffer);

    std::string dummy;
    std::string fileName;
    std::getline(ss, dummy, ':');
    std::getline(ss, fileName);
    mInternalPath += "/" + fileName;
}

void GUIScore::Init()
{
    InitProperties();
    LoadScoreFileName(mAssetManager);
    CreateFirstScoreFile();
    LoadBestScore();

    std::string spriteAtlasName = ResourceManager::GetPropString(StringLiterals::GetGUIScore_FlappyBirdSpriteAtlasName());
    CreateBigScoreNumbers(spriteAtlasName);
    CreateSmallScoreNumbers(spriteAtlasName);
    CreateScoreboard(spriteAtlasName);
}

void GUIScore::InitProperties()
{
    mSBEdgeOffsetWidth = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_SBEdgeOffsetWidth());
    mSBEdgeOffsetHeight = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_SBEdgeOffsetHeight());

    mBestEdgeOffsetWidth = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_BestEdgeOffsetWidth());
    mBestEdgeOffsetHeight = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_BestEdgeOffsetHeight());

    //load multiplicative factors for the score board
    mSBFactorScreenWidth = ResourceManager::GetPropFloat(StringLiterals::GetGUIScore_SBFactorScreenWidth());
    mSBFactorScreenHeight = ResourceManager::GetPropFloat(StringLiterals::GetGUIScore_SBFactorScreenHeight());

    int scoreBoardWidth = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_ScoreBoardWidth());
    mSBPosXFinal = (mScreenWidth - scoreBoardWidth * mScreenScaling.x) * mSBFactorScreenWidth;
    mSBPosYFinal = mScreenHeight - mSBFactorScreenHeight * mScreenHeight;
    int scoreBoardHeight = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_ScoreBoardHeight());
    mSBInitialPosY = -scoreBoardHeight * mScreenScaling.y;
    ResetSBHeightPos();
    mAscendSpeed = ResourceManager::GetPropFloat(StringLiterals::GetGUIScore_AscendSpeed());
}

void GUIScore::DrawSmallScoreNumbers(const Sprite *scoreBoard, const glm::vec2 &scoreBoardPos, int score, const SpriteRenderer *renderer, bool isBestScore) const
{
    std::string scoreString = stringValue(score);
    int totalLength = 0;
    for (int i = 0; i < scoreString.size(); i++)
    {
        totalLength += mSmallNumbers.find(scoreString[i])->second->GetWidth();
    }

    float posX;
    float posY;
    if (!isBestScore)
    {
        posX = scoreBoardPos.x + (scoreBoard->GetWidth() - mSBEdgeOffsetWidth - totalLength) * mScreenScaling.x;
        posY = scoreBoardPos.y + (scoreBoard->GetHeight() - mSBEdgeOffsetHeight) * mScreenScaling.y;
    }
    else
    {
        posX = scoreBoardPos.x + (scoreBoard->GetWidth() - mBestEdgeOffsetWidth  - totalLength) * mScreenScaling.x;
        posY = scoreBoardPos.y + (scoreBoard->GetHeight() - mBestEdgeOffsetHeight) * mScreenScaling.y;
    }

    for (int i = 0; i < scoreString.size(); i++)
    {
        Sprite *sprite = mSmallNumbers.find(scoreString[i])->second;
        int offset = sprite->GetWidth();
        renderer->DrawSprite(sprite, glm::vec2(posX, posY), 0.0f);
        posX += offset * mScreenScaling.x;
    }
}

void GUIScore::CreateBigScoreNumbers(const std::string &spriteAtlasName)
{
    const Texture2D &texture = ResourceManager::GetTexture(spriteAtlasName);

    mFactorScreenWidthBig = ResourceManager::GetPropFloat(StringLiterals::GetGUIScore_FactorScreenWidthBig());
    mFactorScreenHeightBig = ResourceManager::GetPropFloat(StringLiterals::GetGUIScore_FactorScreenHeightBig());

    //width and height of the sprites 0, 2 to 9 for big size sprites
    int widthBig = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_WidthBig());
    int heightBig = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_HeightBig());

    //all big number sprites share the Y position
    int originYBig = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_OriginYBig());

    //Create big size number 1 sprite - number 1 has its own width
    int num1WidthBig = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_Num1WidthBig());
    int num1XBig = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_Num1XBig());
    Sprite *sprite = new Sprite(texture, num1XBig, originYBig, num1WidthBig, heightBig);
    mBigNumbers.insert(std::make_pair('1', sprite));

    //Create the rest of numbers 0,2,...,9
    for (int i = 0; i < 10; i++)
    {
        if (i == 1)
            continue;

        std::string prop = "GUIScore.Num" + stringValue(i) + "XBig";
        sprite = new Sprite(texture, ResourceManager::GetPropInt(prop), originYBig, widthBig, heightBig);
        mBigNumbers.insert(std::make_pair(stringValue(i)[0], sprite));
    }
}

void GUIScore::CreateSmallScoreNumbers(const std::string &spriteAtlasName)
{
    const Texture2D &texture = ResourceManager::GetTexture(spriteAtlasName);

    //width and height of the sprites 0, 2 to 9 for small size sprites
    int widthSmall = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_WidthSmall());
    int heightSmall = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_HeightSmall());

    //all small number sprites share the X position
    int originXSmall = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_OriginXSmall());

    //Create small size number 1 sprite - number 1 has its own width
    int num1WidthSmall = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_Num1WidthSmall());
    int num1Ysmall = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_Num1YSmall());
    Sprite *sprite = new Sprite(texture, originXSmall, num1Ysmall, num1WidthSmall, heightSmall);
    mSmallNumbers.insert(std::make_pair('1', sprite));

    //Create the rest of numbers 0,2,...,9
    for (int i = 0; i < 10; i++)
    {
        if (i == 1)
            continue;

        std::string prop = "GUIScore.Num" + stringValue(i) + "YSmall";
        sprite = new Sprite(texture, originXSmall, ResourceManager::GetPropInt(prop), widthSmall, heightSmall);
        mSmallNumbers.insert(std::make_pair(stringValue(i)[0], sprite));
    }
}

void GUIScore::CreateScoreboard(const std::string &spriteAtlasName)
{
    const Texture2D &texture = ResourceManager::GetTexture(spriteAtlasName);

    //Create score board sprite
    int scoreBoardOriginX = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_ScoreBoardX());
    int scoreBoardOriginY = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_ScoreBoardY());
    int scoreBoardWidth = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_ScoreBoardWidth());
    int scoreBoardHeight = ResourceManager::GetPropInt(StringLiterals::GetGUIScore_ScoreBoardHeight());
    mScoreBoard = new Sprite(texture, scoreBoardOriginX, scoreBoardOriginY, scoreBoardWidth, scoreBoardHeight);
}

void GUIScore::CreateFirstScoreFile() const
{
    FILE *fp = fopen(mInternalPath.c_str(), "r");
    if(!fp)
    {
        ResetScoreFile();
        return;
    }
    fclose(fp);
}

void GUIScore::ResetScoreFile() const
{
    FILE *fp = fopen(mInternalPath.c_str(), "w");
    if(!fp)
    {
        __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Error creating score file: %s", strerror(errno));
        return;
    }
    const char score[] = "BestScore:0";
    fwrite(score, sizeof(char), sizeof(score), fp);
    fclose(fp);
}

void GUIScore::LoadBestScore()
{
    FILE *fp = fopen(mInternalPath.c_str(), "r");

    if(!fp)
    {
        __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Error opening score file: %s", strerror(errno));
        return;
    }

    fseek(fp, 0, SEEK_END);
    size_t length = ftell(fp);
    char *buffer = new char[length+1];
    fseek(fp, 0, SEEK_SET);
    fread(buffer, sizeof(char), length, fp);
    fclose(fp);
    buffer[length] = '\0';
    std::stringstream ss(buffer);
    std::string bestScore;
    std::string dummy;
    std::getline(ss, dummy, ':');
    std::getline(ss, bestScore);
    mBestScore = atoi(bestScore);
}

void GUIScore::Clear()
{
    for (auto &pair : mBigNumbers)
    {
        DELETE_PTR(pair.second);
    }
    mBigNumbers.clear();

    for (auto &pair : mSmallNumbers)
    {
        DELETE_PTR(pair.second);
    }
    mSmallNumbers.clear();

    DELETE_PTR(mScoreBoard);
}
