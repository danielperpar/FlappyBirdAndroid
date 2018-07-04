#ifndef FLAPPYBIRDANDROID_GUI_SCORE_H
#define FLAPPYBIRDANDROID_GUI_SCORE_H

#include <map>
#include "sprite.h"
#include <glm/glm.hpp>
#include <string.h>

class Sprite;
class SpriteRenderer;
class Texture2D;
struct AAssetManager;
class GUIScore final
{
public:
    GUIScore(int screenWidth, int screenHeight, const glm::vec2 &screenScaling, AAssetManager *assetManager, const std::string &internalPath);
    ~GUIScore();
    void DrawBigScoreNumbers(unsigned int score, const SpriteRenderer *renderer) const;
    bool SlideScoreboard(float dt);
    void DrawScoreBoard(unsigned int score, const SpriteRenderer *renderer);
    void SaveMaxScore(unsigned int maxScore);
    unsigned int GetBestScore() const;
    void ResetSBHeightPos();

private:
    AAssetManager *mAssetManager = nullptr;
    unsigned int mBestScore = 0;
    std::string mInternalPath;
    std::map<char, Sprite *> mBigNumbers;
    std::map<char, Sprite *> mSmallNumbers;
    glm::vec2 mScreenScaling;
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    float mFactorScreenWidthBig = 0.0f;
    float mFactorScreenHeightBig = 0.0f;

    //offsets in the score board to position score numbers
    int mSBEdgeOffsetWidth = 0;
    int mSBEdgeOffsetHeight = 0;
    int mBestEdgeOffsetWidth = 0;
    int mBestEdgeOffsetHeight = 0;

    //score board multiplicative factors
    float mSBFactorScreenWidth = 0.0f;
    float mSBFactorScreenHeight = 0.0f;

    float mSBInitialPosY = 0.0f;
    float mSBPosXFinal = 0.0f;
    float mSBPosYFinal = 0.0f;

    float mAscendSpeed = 0.0f;
    float mSBPosY = 0.0f;

    Sprite *mScoreBoard = nullptr;

    void InitProperties();
    void LoadScoreFileName(AAssetManager *assetManager);
    void Init();
    void DrawSmallScoreNumbers(const Sprite *scoreBoard, const glm::vec2 &scoreBoardPos, int score,
                               const SpriteRenderer *renderer, bool isBestScore) const;
    void CreateBigScoreNumbers(const std::string &spriteAtlasName);
    void CreateSmallScoreNumbers(const std::string &spriteAtlasName);
    void CreateScoreboard(const std::string &spriteAtlasName);
    void CreateFirstScoreFile() const;
    void ResetScoreFile() const;
    void LoadBestScore();
    void Clear();
};
#endif //FLAPPYBIRDANDROID_GUI_SCORE_H
