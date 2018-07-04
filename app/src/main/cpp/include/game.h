#ifndef FLAPPYBIRDANDROID_GAME_H
#define FLAPPYBIRDANDROID_GAME_H

#include <glm/glm.hpp>
#include "sound_manager.h"
#include <string>

enum class GameState
{
    INITIAL_SCREEN,
    INSTRUCTIONS,
    ACTIVE,
    DEAD,
    SHOW_SCORE
};

class GameObject;
class BirdGameObject;
class ColumnGameObject;
class GameLevel;
class SpriteRenderer;
class Sprite;
class GUIScore;
struct AAssetManager;
class SoundManager;
class Game final
{
public:
    GameState mGameState = GameState::INITIAL_SCREEN;
    Game(int screenWidth, int screenHeight, AAssetManager *assetManager, const std::string& internalPath);
    ~Game();
    void LoadProperties();
    void LoadTexturesFromFile() const;
    void InitRendererObjects();
    void InitGameObjects();
    void ProcessInput();
    void Update(float dt);
    void Render(float dt);
    void ComputeScore();
    void TouchScreen();
    void LoadSoundEffects() const;
    void StartSoundManager();

private:
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    glm::vec2 mScreenScaling;
    std::string mInternalPath;
    AAssetManager *mAssetManager = nullptr;
    GameLevel *mLevel = nullptr;
    SpriteRenderer *mRenderer = nullptr;
    BirdGameObject *mFlappyBird = nullptr;
    Sprite *mBackground = nullptr;
    GameObject *mForeground = nullptr;
    Sprite *mGetReady = nullptr;
    Sprite *mInstructions = nullptr;
    Sprite *mTitle = nullptr;
    Sprite *mPlayButton = nullptr;
    Sprite *mScoreBoard = nullptr;
    Sprite *mGameOver = nullptr;
    unsigned int mScore = 0;
    GUIScore *mGUIScore = nullptr;
    float mFactorTitleScreenX = 0.0f;
    float mFactorTitleScreenY = 0.0f;
    float mFactorStartPosX = 0.0f;
    float mFactorStartPosY = 0.0f;
    int mShiftSpeed = 0;
    float mFactorGetReadyScreenX = 0.0f;
    float mFactorGetReadyScreenY = 0.0f;
    float mFactorInstrucScreenX = 0.0f;
    float mFactorInstrucScreenY = 0.0f;
    float mFactorPlayBtnScreenX = 0.0f;
    float mFactorPlayBtnScreenY = 0.0f;
    float mFactorGameOverScreenX = 0.0f;
    float mFactorGameOverScreenY = 0.0f;
    float mFactorShakeTime = 0.0f;
    float mDeadTimer = 0.0f;
    float mMaxDeadTimer = 0.0f;
    int mShakeValue = 0.0f;
    bool mIsSBShowed = false;
    SoundManager *mSoundManager = nullptr;
    std::string mFlyAudioPath;
    std::string mCollissionAudioPath;
    std::string mDieAudioPath;
    std::string mGUIMovementAudioPath;
    std::string mScorePointAudioPath;
    bool mGUIMovAudioPlayed = false;
    bool mDieAudioPlayed = false;
    bool mIsScreenTouched = false;
    bool mDrawPlayButton = false;

    void CreateBirdGameObject(const std::string &spriteAtlasName);
    void CreateBGSprite(const std::string &spriteAtlasName);
    void CreateFGGameObject();
    void CreateGetReadySprite(const std::string &spriteAtlasName);
    void CreateInstructionsSprite(const std::string &spriteAtlasName);
    void CreateTitleSprite(const std::string &spriteAtlasName);
    void CreatePlayButtonSprite(const std::string &spriteAtlasName);
    void CreateGUIScore();
    void CreateGameLevel(const std::string &spriteAtlasName);
    void CreateGameOverSprite(const std::string &spriteAtlasName);
    void ReleaseScreen();
    void InitProperties();
    void DoCollissions();
    void CheckCollissions(BirdGameObject *bird, ColumnGameObject *column);
    void CheckCollissions(BirdGameObject *bird, float groundHeight);
    void Clear();
};
#endif //FLAPPYBIRDANDROID_GAME_H
