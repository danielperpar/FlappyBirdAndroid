#include "game.h"
#include "resource_manager.h"
#include "bird_game_object.h"
#include "game_level.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include "sprite_renderer.h"
#include "sprite.h"
#include "animation.h"
#include "globals.h"
#include "gui_score.h"
#include <string>
#include <android/asset_manager.h>
#include "column_game_object.h"
#include "string_literals.h"
#include "sound_manager.h"
#include <android/log.h>

Game::Game(int screenWidth, int screenHeight, AAssetManager *assetManager, const std::string &internalPath) :
        mScreenWidth(screenWidth),
        mScreenHeight(screenHeight),
        mAssetManager(assetManager),
        mInternalPath(internalPath){}

Game::~Game()
{
    Clear();
}

void Game::LoadProperties()
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Loading properties.");

    StringLiterals::LoadLiterals();
    ResourceManager::LoadProperties(mAssetManager, PROPERTIES_PATH);
    InitProperties();
}

void Game::LoadTexturesFromFile() const
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Loading textures.");

    std::string flappyBirdSpriteAtlasName = ResourceManager::GetPropString(StringLiterals::GetGame_FlappyBirdSpriteAtlasName());
    std::string flappyBirdSpriteAtlasPath = ResourceManager::GetPropString(StringLiterals::GetGame_FlappyBirdSpriteAtlasPath());
    ResourceManager::LoadTextureFromFile(mAssetManager, flappyBirdSpriteAtlasName, flappyBirdSpriteAtlasPath);

    std::string foregroundTexName = ResourceManager::GetPropString(StringLiterals::GetGame_ForegroundTexName());
    std::string foregroundTexPath = ResourceManager::GetPropString(StringLiterals::GetGame_ForegroundTexPath());
    ResourceManager::LoadTextureFromFile(mAssetManager, foregroundTexName, foregroundTexPath);
}

void Game::InitRendererObjects()
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Initializing renderer objects.");

    std::string gameShaderName = ResourceManager::GetPropString(StringLiterals::GetGame_GameShaderName());
    std::string vertexShaderPath = ResourceManager::GetPropString(StringLiterals::GetGame_VertexShaderPath());
    std::string fragmentShaderPath = ResourceManager::GetPropString(StringLiterals::GetGame_FragmentShaderPath());
    ResourceManager::LoadShader(mAssetManager, gameShaderName, vertexShaderPath, fragmentShaderPath);
    glm::mat4 projection;
    projection = glm::ortho(0.0f, float(mScreenWidth), 0.0f, float(mScreenHeight), -1.0f, 1.0f);
    ResourceManager::GetShader(gameShaderName).SetMatrix4("projection", projection);
    ResourceManager::GetShader(gameShaderName).SetInteger("textureSampler", 0);

    //Get screenScaling factor to adjust textures to screen area
    int bgroundSpriteWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_BGroundSpriteWidth());
    int bgroundSpriteHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_BGroundSpriteHeight());
    mScreenScaling = glm::vec2((float)mScreenWidth/bgroundSpriteWidth, (float)mScreenHeight/bgroundSpriteHeight);

    //To allow recreation of EGL context each time the activity goes to sleep and comes back
    if(mRenderer != nullptr)
        DELETE_PTR(mRenderer);
    mRenderer = new SpriteRenderer(ResourceManager::GetShader(gameShaderName), mScreenScaling);
}

void Game::InitGameObjects()
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Initializing game objects.");

    std::string flappyBirdSpriteAtlasName = ResourceManager::GetPropString(StringLiterals::GetGame_FlappyBirdSpriteAtlasName());

    //Instantiation of the bird game object
    CreateBirdGameObject(flappyBirdSpriteAtlasName);

    //Instantiation of the  background sprite
    CreateBGSprite(flappyBirdSpriteAtlasName);

    //Instantiation of the foreground game object
    CreateFGGameObject();

    //Instantiation of the GetReady sprite
    CreateGetReadySprite(flappyBirdSpriteAtlasName);

    //Instantiation of the Instructions sprite
    CreateInstructionsSprite(flappyBirdSpriteAtlasName);

    //Instantiation of the title sprite
    CreateTitleSprite(flappyBirdSpriteAtlasName);

    //Instantiation of the play button sprite
    CreatePlayButtonSprite(flappyBirdSpriteAtlasName);

    //Instantiation of the score board object
    CreateGUIScore();

    //Instantiation of the game level object
    CreateGameLevel(flappyBirdSpriteAtlasName);

    //Instantiation of the game over sprite
    CreateGameOverSprite(flappyBirdSpriteAtlasName);
}

void Game::ProcessInput()
{
    switch (mGameState)
    {
        case GameState::INITIAL_SCREEN:
            if (mIsScreenTouched)
            {
                mFlappyBird->SetPosition(glm::vec2(mScreenWidth * mFactorStartPosX, mScreenHeight * mFactorStartPosY));
                mGameState = GameState::INSTRUCTIONS;
                ReleaseScreen();
            }
            break;
        case GameState::INSTRUCTIONS:
            if (mIsScreenTouched)
            {
                mFlappyBird->JumpPressed();
                mSoundManager->Play(StringLiterals::GetSfxWing());
                mGameState = GameState::ACTIVE;
                ReleaseScreen();
            }
            break;
        case GameState::ACTIVE:
            if (mIsScreenTouched)
            {
                mFlappyBird->JumpPressed();
                mSoundManager->Play(StringLiterals::GetSfxWing());
                ReleaseScreen();
            }
            break;
        case GameState::SHOW_SCORE:
            if (mIsSBShowed && mIsScreenTouched)
            {
                mIsSBShowed = false;
                mScore = 0;
                mFlappyBird->SetPosition(glm::vec2(mScreenWidth * mFactorStartPosX, mScreenHeight * mFactorStartPosY));
                mFlappyBird->SetRotInDegrees(0.0f);
                mLevel->Reset();
                mRenderer->ResetAlpha();
                mGUIScore->ResetSBHeightPos();
                mGUIMovAudioPlayed = false;
                mDrawPlayButton = false;
                mGameState = GameState::INSTRUCTIONS;
                ReleaseScreen();
            }
            break;
        default:
            //DEAD doesn't depend on the screen touch
            break;
    }
}

void Game::Update(float dt)
{
    switch (mGameState)
    {
        case GameState::INITIAL_SCREEN:
            mFlappyBird->Hover(dt);
            break;

        case GameState::INSTRUCTIONS:
            //fade in instructions sprite
            mRenderer->FadedPerformed(true, dt);
            mFlappyBird->Hover(dt);
            break;

        case GameState::ACTIVE:
            //fade out instructions sprite
            mRenderer->FadedPerformed(false, dt);
            mFlappyBird->UpdatePosition(dt);
            mLevel->UpdateColumnsPosition(dt);
            DoCollissions();
            break;

        case GameState::DEAD:
            mDeadTimer += dt;
            mLevel->BeginShake();
            mFlappyBird->BeginShake();
            mForeground->BeginShake();

            if (mDeadTimer > mFactorShakeTime * mMaxDeadTimer)
            {
                if (!mDieAudioPlayed)
                {
                    mSoundManager->Play(StringLiterals::GetSfxDie());
                    mDieAudioPlayed = true;
                }
                mLevel->EndShake();
                mFlappyBird->EndShake();
                mForeground->EndShake();
            }

            if (mDeadTimer > mMaxDeadTimer)
            {
                mDeadTimer = 0.0f;
                mDieAudioPlayed = false;

                if (mScore > mGUIScore->GetBestScore())
                {
                    mGUIScore->SaveMaxScore(mScore);
                }

                mGameState = GameState::SHOW_SCORE;
            }
            //Clear screen touch to prevent unwanted transition from score board to instructions screen
            ReleaseScreen();
            break;

        case GameState::SHOW_SCORE:
            //GameOver GUI element fades in
            bool isFadedIn = mRenderer->FadedPerformed(true, dt);
            if(isFadedIn)
            {
                if (!mGUIMovAudioPlayed)
                {
                    mSoundManager->Play(StringLiterals::GetSfxSwooshing());
                    mGUIMovAudioPlayed = true;
                }
                //Slide the score board upwards
                if(mGUIScore->SlideScoreboard(dt))
                {
                    mDrawPlayButton = true;
                }
            }
            break;
    }
}

void Game::Render(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT);

    mRenderer->DrawSprite(mBackground, glm::vec2(0.0f), 0.0f);

    switch (mGameState)
    {
        case GameState::INITIAL_SCREEN:
        {

            mFlappyBird->Draw(mRenderer, dt);

            float titlePosX = (mScreenWidth - mTitle->GetWidth() * mScreenScaling.x) * mFactorTitleScreenX;
            float titlePosY = mScreenHeight * mFactorTitleScreenY;
            mRenderer->DrawSprite(mTitle, glm::vec2(titlePosX, titlePosY), 0.0f);

            float playBtnPosX = (mScreenWidth - mPlayButton->GetWidth() * mScreenScaling.x) * mFactorPlayBtnScreenX;
            float playBtnPosY = mScreenHeight * mFactorPlayBtnScreenY;
            mRenderer->DrawSprite(mPlayButton, glm::vec2(playBtnPosX, playBtnPosY), 0.0f);

            mRenderer->DrawSpritesShifted(mForeground->GetAnimation()->GetSprite(0), mForeground->GetPosition(), mShiftSpeed * dt);

            break;
        }
        case GameState::INSTRUCTIONS:
        {
            mFlappyBird->Draw(mRenderer, dt);

            mGUIScore->DrawBigScoreNumbers(mScore, mRenderer);

            float getReadyPosX = (mScreenWidth - mGetReady->GetWidth() * mScreenScaling.x) * mFactorGetReadyScreenX;
            float getReadyPosY = mScreenHeight * mFactorGetReadyScreenY;
            mRenderer->DrawSprite(mGetReady, glm::vec2(getReadyPosX, getReadyPosY), 0.0f);

            float instrucPosX = (mScreenWidth - mInstructions->GetWidth() * mScreenScaling.x) * mFactorInstrucScreenX;
            float instrucPosY = mScreenHeight * mFactorInstrucScreenY;
            mRenderer->DrawSpriteFaded(mInstructions, glm::vec2(instrucPosX, instrucPosY));

            mRenderer->DrawSpritesShifted(mForeground->GetAnimation()->GetSprite(0), mForeground->GetPosition(), mShiftSpeed * dt);

            break;
        }
        case GameState::ACTIVE:
        {
            mLevel->DrawLevel(dt);

            mFlappyBird->Draw(mRenderer, dt);

            mGUIScore->DrawBigScoreNumbers(mScore, mRenderer);

            float instrucPosX = (mScreenWidth - mInstructions->GetWidth() * mScreenScaling.x) * mFactorInstrucScreenX;
            float instrucPosY = mScreenHeight * mFactorInstrucScreenY;
            mRenderer->DrawSpriteFaded(mInstructions, glm::vec2(instrucPosX, instrucPosY));

            mRenderer->DrawSpritesShifted(mForeground->GetAnimation()->GetSprite(0), mForeground->GetPosition(), mShiftSpeed * dt);

            break;
        }
        case GameState::DEAD:
        {
            mLevel->DrawLevel(0.0f);
            mFlappyBird->Draw(mRenderer, 0.0f);
            mRenderer->DrawSpritesShifted(mForeground->GetAnimation()->GetSprite(0), mForeground->GetPosition(), 0.0f);
            break;
        }
        case GameState::SHOW_SCORE:
        {
            mLevel->DrawLevel(0.0f);

            float gameOverPosX = (mScreenWidth - mGameOver->GetWidth() * mScreenScaling.x) * mFactorGameOverScreenX;
            float gameOverPosY = mScreenHeight * mFactorGameOverScreenY;
            mRenderer->DrawSpriteFaded(mGameOver, glm::vec2(gameOverPosX, gameOverPosY));

            mGUIScore->DrawScoreBoard(mScore, mRenderer);

            if (mDrawPlayButton)
            {
                float playBtnPosX = (mScreenWidth - mPlayButton->GetWidth() * mScreenScaling.x) * mFactorPlayBtnScreenX;
                float playBtnPosY = mScreenHeight * mFactorPlayBtnScreenY;
                mRenderer->DrawSprite(mPlayButton, glm::vec2(playBtnPosX, playBtnPosY), 0.0f);

                //flag to allow the scoreboard to show up before the screen changes on user touch
                mIsSBShowed = true;
            }

            mRenderer->DrawSpritesShifted(mForeground->GetAnimation()->GetSprite(0), mForeground->GetPosition(), 0.0f);

            //Clear screen touch to prevent unwanted transition from score board to instructions screen
            ReleaseScreen();
            break;
        }
    }
}

void Game::ComputeScore()
{
    mSoundManager->Play(StringLiterals::GetSfxPoint());
    mScore++;
}

void Game::TouchScreen()
{
    mIsScreenTouched = true;
}

void Game::LoadSoundEffects() const
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Loading sound effects.");

    mSoundManager->LoadSound(mAssetManager, StringLiterals::GetSfxDie());
    mSoundManager->LoadSound(mAssetManager, StringLiterals::GetSfxHit());
    mSoundManager->LoadSound(mAssetManager, StringLiterals::GetSfxPoint());
    mSoundManager->LoadSound(mAssetManager, StringLiterals::GetSfxSwooshing());
    mSoundManager->LoadSound(mAssetManager, StringLiterals::GetSfxWing());
}

void Game::StartSoundManager()
{
    if(mSoundManager == nullptr)
    {
        mSoundManager = new SoundManager();
        mSoundManager->Start();
    }
}

void Game::CreateBirdGameObject(const std::string &spriteAtlasName)
{
    std::vector<Sprite*> birdSprites;
    int birdSpriteWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_BirdSpriteWidth());
    int birdSpriteHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_BirdSpriteHeight());

    int birdSpriteY = ResourceManager::GetPropInt(StringLiterals::GetGame_BirdSpriteY());
    int birdSprite1X = ResourceManager::GetPropInt(StringLiterals::GetGame_BirdSprite1X());
    int birdSprite2X = ResourceManager::GetPropInt(StringLiterals::GetGame_BirdSprite2X());
    int birdSprite3X = ResourceManager::GetPropInt(StringLiterals::GetGame_BirdSprite3X());

    birdSprites.push_back(new Sprite(ResourceManager::GetTexture(spriteAtlasName), birdSprite1X, birdSpriteY, birdSpriteWidth, birdSpriteHeight));
    birdSprites.push_back(new Sprite(ResourceManager::GetTexture(spriteAtlasName), birdSprite2X, birdSpriteY, birdSpriteWidth, birdSpriteHeight));
    birdSprites.push_back(new Sprite(ResourceManager::GetTexture(spriteAtlasName), birdSprite3X, birdSpriteY, birdSpriteWidth, birdSpriteHeight));

    float factorInitScreenPosX = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorInitScreenPosX());
    float factorInitScreenPosY = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorInitScreenPosY());

    float startRot = ResourceManager::GetPropFloat(StringLiterals::GetGame_StartRot());
    int worldGravity = ResourceManager::GetPropInt(StringLiterals::GetGame_WorldGravity());
    float birdAnimSpeed = ResourceManager::GetPropFloat(StringLiterals::GetGame_BirdAnimSpeed());
    Animation *flyAnimation = new Animation(birdSprites, birdAnimSpeed);
    glm::vec2 initPos(mScreenWidth * factorInitScreenPosX - birdSpriteWidth * mScreenScaling.x * factorInitScreenPosX , mScreenHeight * factorInitScreenPosY);
    mFlappyBird = new BirdGameObject(initPos, startRot, glm::vec2(0.0f, 0.0f), worldGravity, flyAnimation, mScreenScaling, mShakeValue);
}

void Game::CreateBGSprite(const std::string &spriteAtlasName)
{
    int bgroundSpriteOrigin = ResourceManager::GetPropInt(StringLiterals::GetGame_BGroundSpriteOrigin());
    int bgroundSpriteWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_BGroundSpriteWidth());
    int bgroundSpriteHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_BGroundSpriteHeight());
    mBackground = new Sprite(ResourceManager::GetTexture(spriteAtlasName), bgroundSpriteOrigin, bgroundSpriteOrigin, bgroundSpriteWidth, bgroundSpriteHeight);
}

void Game::CreateFGGameObject()
{
    std::string foregroundTexName = ResourceManager::GetPropString(StringLiterals::GetGame_ForegroundTexName());
    std::vector<Sprite*> foregroundSprites;
    int fgroundSpriteOrigin = ResourceManager::GetPropInt(StringLiterals::GetGame_FGroundSpriteOrigin());
    int fgroundSpriteWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_FGroundSpriteWidth());
    int fgroundSpriteHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_FGroundSpriteHeight());
    float factorFGPosy = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorFGPosY());
    foregroundSprites.push_back(new Sprite(ResourceManager::GetTexture(foregroundTexName), fgroundSpriteOrigin, fgroundSpriteOrigin, fgroundSpriteWidth, fgroundSpriteHeight));
    Animation *foregroundAnim = new Animation(foregroundSprites, 0.0f);
    mForeground = new GameObject(glm::vec2(0.0f,-factorFGPosy * mScreenHeight), 0.0f, glm::vec2(0.0f), foregroundAnim, mShakeValue);
}

void Game::CreateGetReadySprite(const std::string &spriteAtlasName)
{
    int getReadyX = ResourceManager::GetPropInt(StringLiterals::GetGame_GetReadyX());
    int getReadyY = ResourceManager::GetPropInt(StringLiterals::GetGame_GetReadyY());
    int getReadyWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_GetReadyWidth());
    int getReadyHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_GetReadyHeight());
    mGetReady = new Sprite(ResourceManager::GetTexture(spriteAtlasName), getReadyX, getReadyY, getReadyWidth, getReadyHeight);
}

void Game::CreateInstructionsSprite(const std::string &spriteAtlasName)
{
    int instructionsX = ResourceManager::GetPropInt(StringLiterals::GetGame_InstructionsX());
    int instructionsY = ResourceManager::GetPropInt(StringLiterals::GetGame_InstructionsY());
    int instructionsWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_InstructionsWidth());
    int instructionsHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_InstructionsHeight());
    mInstructions = new Sprite(ResourceManager::GetTexture(spriteAtlasName), instructionsX, instructionsY, instructionsWidth, instructionsHeight);
}

void Game::CreateTitleSprite(const std::string &spriteAtlasName)
{
    int titleX = ResourceManager::GetPropInt(StringLiterals::GetGame_TitleX());
    int titleY = ResourceManager::GetPropInt(StringLiterals::GetGame_TitleY());
    int titleWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_TitleWidth());
    int titleHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_TitleHeight());
    mTitle = new Sprite(ResourceManager::GetTexture(spriteAtlasName), titleX, titleY, titleWidth, titleHeight);
}

void Game::CreatePlayButtonSprite(const std::string &spriteAtlasName)
{
    int playButtonX = ResourceManager::GetPropInt(StringLiterals::GetGame_PlayButtonX());
    int playButtonY = ResourceManager::GetPropInt(StringLiterals::GetGame_PlayButtonY());
    int playButtonWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_PlayButtonWidth());
    int playButtonHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_PlayButtonHeight());
    mPlayButton = new Sprite(ResourceManager::GetTexture(spriteAtlasName), playButtonX, playButtonY, playButtonWidth, playButtonHeight);
}

void Game::CreateGUIScore()
{
    mGUIScore = new GUIScore(mScreenWidth, mScreenHeight, mScreenScaling, mAssetManager, mInternalPath);
}

void Game::CreateGameLevel(const std::string &spriteAtlasName)
{
    mLevel = new GameLevel(mScreenWidth, mScreenHeight, mScreenScaling, mShiftSpeed, mRenderer, spriteAtlasName, this, mFlappyBird, mShakeValue);
}

void Game::CreateGameOverSprite(const std::string &spriteAtlasName)
{
    int gameOverX = ResourceManager::GetPropInt(StringLiterals::GetGame_GameOverX());
    int gameOverY = ResourceManager::GetPropInt(StringLiterals::GetGame_GameOverY());
    int gameOverWidth = ResourceManager::GetPropInt(StringLiterals::GetGame_GameOverWidth());
    int gameOverHeight = ResourceManager::GetPropInt(StringLiterals::GetGame_GameOverHeight());
    mGameOver = new Sprite(ResourceManager::GetTexture(spriteAtlasName), gameOverX, gameOverY, gameOverWidth, gameOverHeight);
}

void Game::ReleaseScreen()
{
    mIsScreenTouched = false;
}

void Game::InitProperties()
{
    mFactorTitleScreenX = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorTitleScreenX());
    mFactorTitleScreenY = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorTitleScreenY());
    mFactorStartPosX = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorStartPosX());
    mFactorStartPosY = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorStartPosY());
    mShiftSpeed = ResourceManager::GetPropInt(StringLiterals::GetGame_ShiftSpeed());
    mFactorGetReadyScreenX = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorGetReadyScreenX());
    mFactorGetReadyScreenY = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorGetReadyScreenY());
    mFactorInstrucScreenX = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorInstrucScreenX());
    mFactorInstrucScreenY = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorInstrucScreenY());
    mFactorPlayBtnScreenX = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorPlayBtnScreenX());
    mFactorPlayBtnScreenY = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorPlayBtnScreenY());
    mFactorGameOverScreenX = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorGameOverScreenX());
    mFactorGameOverScreenY = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorGameOverScreenY());
    mMaxDeadTimer = ResourceManager::GetPropFloat(StringLiterals::GetGame_MaxDeadTimer());
    mShakeValue = ResourceManager::GetPropInt(StringLiterals::GetGame_ShakeValue());
    mFactorShakeTime = ResourceManager::GetPropFloat(StringLiterals::GetGame_FactorShakeTime());
    mFlyAudioPath = ResourceManager::GetPropString(StringLiterals::GetGame_FlyAudioPath());
    mCollissionAudioPath = ResourceManager::GetPropString(StringLiterals::GetGame_CollissionAudioPath());
    mGUIMovementAudioPath = ResourceManager::GetPropString(StringLiterals::GetGame_GUIMovementAudioPath());
    mScorePointAudioPath = ResourceManager::GetPropString(StringLiterals::GetGame_ScorePointAudioPath());
    mDieAudioPath = ResourceManager::GetPropString(StringLiterals::GetGame_DieAudioPath());
}

void Game::DoCollissions()
{
    CheckCollissions(mFlappyBird, mForeground->GetPosition().y + mForeground->GetAnimation()->GetSprite(0)->GetHeight() * mScreenScaling.y);

    for (int i = 0; i < mLevel->GetNumColumnPairs(); i++)
    {
        //discard column pairs out of the screen
        if (mLevel->GetColumnPair(i).first->GetPosition().x > mScreenWidth * mScreenScaling.x)
        {
            break;
        }
        CheckCollissions(mFlappyBird, mLevel->GetColumnPair(i).first);
        CheckCollissions(mFlappyBird, mLevel->GetColumnPair(i).second);
    }
}

void Game::CheckCollissions(BirdGameObject *bird, ColumnGameObject *column)
{
    const Sprite *birdSprite = bird->GetAnimation()->GetSprite(0);
    glm::vec2 birdCentre = bird->GetPosition() + glm::vec2(birdSprite->GetWidth() * 0.5f * mScreenScaling.x, birdSprite->GetHeight() * 0.5f * mScreenScaling.y);

    const Sprite *colSprite = column->GetAnimation()->GetSprite(0);
    glm::vec2 colCentre = column->GetPosition() + glm::vec2(colSprite->GetWidth() * 0.5f * mScreenScaling.x, colSprite->GetHeight() * 0.5f * mScreenScaling.y);

    glm::vec2 colToBirdVector = birdCentre - colCentre;

    //Clamp colToBirdVector to the boundaries of the column rectangle to get the intersection point between colToBirdVector and the sides of the rectangle
    glm::vec2 minHalfExtents(-colSprite->GetWidth() * 0.5f * mScreenScaling.x, -colSprite->GetHeight() * 0.5f * mScreenScaling.y);
    glm::vec2 maxHalfExtents(colSprite->GetWidth() * 0.5f * mScreenScaling.x, colSprite->GetHeight() * 0.5f * mScreenScaling.y);
    glm::vec2 closestPoint = colCentre + glm::clamp(colToBirdVector, minHalfExtents, maxHalfExtents);

    //Check the distance between the intersection point and the center of the bird
    float distSqr = glm::distance2<float, glm::precision::defaultp>(birdCentre, closestPoint);
    float radiusSqr = (float)glm::pow(birdSprite->GetHeight() * mScreenScaling.y * 0.5f, 2);
    if (distSqr < radiusSqr)
    {

        mSoundManager->Play(StringLiterals::GetSfxHit());
        mLevel->PrepareShake();
        mFlappyBird->PrepareShake();
        mForeground->PrepareShake();
        mGameState = GameState::DEAD;
    }
}

void Game::CheckCollissions(BirdGameObject *bird, float groundHeight)
{
    if (bird->GetPosition().y < groundHeight)
    {
        mSoundManager->Play(StringLiterals::GetSfxHit());
        mLevel->PrepareShake();
        mFlappyBird->PrepareShake();
        mForeground->PrepareShake();
        mGameState = GameState::DEAD;
    }
}

void Game::Clear()
{
    DELETE_PTR(mRenderer);
    DELETE_PTR(mFlappyBird);
    DELETE_PTR(mLevel);
    DELETE_PTR(mBackground);
    DELETE_PTR(mForeground);
    DELETE_PTR(mGetReady);
    DELETE_PTR(mInstructions);
    DELETE_PTR(mTitle);
    DELETE_PTR(mPlayButton);
    DELETE_PTR(mScoreBoard);
    DELETE_PTR(mGameOver);
    DELETE_PTR(mGUIScore);
    DELETE_PTR(mSoundManager);
}
