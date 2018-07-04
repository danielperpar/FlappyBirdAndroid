#include "string_literals.h"

void StringLiterals::LoadLiterals()
{
    //BirdGameOject class string literals
    mBirdGameObject_JumpVelocityFactor = "BirdGameObject.JumpVelocityFactor";
    mBirdGameObject_MinVelocity = "BirdGameObject.MinVelocity"; 
    mBirdGameObject_MaxVelocity = "BirdGameObject.MaxVelocity";
    mBirdGameObject_MinRotation = "BirdGameObject.MinRotation";
    mBirdGameObject_MaxRotation = "BirdGameObject.MaxRotation";
    mBirdGameObject_TimeToStartRotation = "BirdGameObject.TimeToStartRotation";
    mBirdGameObject_TimeToMinRotation = "BirdGameObject.TimeToMinRotation";
    mBirdGameObject_RotSpeeedNotFalling = "BirdGameObject.RotSpeeedNotFalling";
    mBirdGameObject_HoverSpeed = "BirdGameObject.HoverSpeed";
    mBirdGameObject_MaxHoverAmp = "BirdGameObject.MaxHoverAmp";
    
    //Game class string literals
     mGame_FlappyBirdSpriteAtlasName = "Game.FlappyBirdSpriteAtlasName";
     mGame_FlappyBirdSpriteAtlasPath = "Game.FlappyBirdSpriteAtlasPath";
     mGame_ForegroundTexName = "Game.ForegroundTexName";
     mGame_ForegroundTexPath = "Game.ForegroundTexPath";
     mGame_GameShaderName = "Game.GameShaderName";
     mGame_VertexShaderPath = "Game.VertexShaderPath";
     mGame_FragmentShaderPath = "Game.FragmentShaderPath";
     mGame_BirdSpriteWidth = "Game.BirdSpriteWidth";
     mGame_BirdSpriteHeight = "Game.BirdSpriteHeight";
     mGame_BirdSpriteY = "Game.BirdSpriteY";
     mGame_BirdSprite1X = "Game.BirdSprite1X";
     mGame_BirdSprite2X = "Game.BirdSprite2X";
     mGame_BirdSprite3X = "Game.BirdSprite3X";
     mGame_BirdAnimSpeed = "Game.BirdAnimSpeed";
     mGame_FactorInitScreenPosX = "Game.FactorInitScreenPosX";
     mGame_FactorInitScreenPosY = "Game.FactorInitScreenPosY";
     mGame_FactorStartPosX = "Game.FactorStartPosX";
     mGame_FactorStartPosY = "Game.FactorStartPosY";
     mGame_StartRot = "Game.StartRot";
     mGame_WorldGravity = "Game.WorldGravity";
     mGame_ShiftSpeed = "Game.ShiftSpeed";
     mGame_BGroundSpriteOrigin = "Game.BGroundSpriteOrigin";
     mGame_BGroundSpriteWidth = "Game.BGroundSpriteWidth";
     mGame_BGroundSpriteHeight = "Game.BGroundSpriteHeight";
     mGame_FGroundSpriteOrigin = "Game.FGroundSpriteOrigin";
     mGame_FGroundSpriteWidth = "Game.FGroundSpriteWidth";
     mGame_FGroundSpriteHeight = "Game.FGroundSpriteHeight";
     mGame_FactorFGPosY = "Game.FactorFGPosY";
     mGame_GetReadyX = "Game.GetReadyX";
     mGame_GetReadyY = "Game.GetReadyY";
     mGame_GetReadyWidth = "Game.GetReadyWidth";
     mGame_GetReadyHeight = "Game.GetReadyHeight";
     mGame_FactorGetReadyScreenX = "Game.FactorGetReadyScreenX";
     mGame_FactorGetReadyScreenY = "Game.FactorGetReadyScreenY";
     mGame_InstructionsX = "Game.InstructionsX";
     mGame_InstructionsY = "Game.InstructionsY";
     mGame_InstructionsWidth = "Game.InstructionsWidth";
     mGame_InstructionsHeight = "Game.InstructionsHeight";
     mGame_FactorInstrucScreenX = "Game.FactorInstrucScreenX";
     mGame_FactorInstrucScreenY = "Game.FactorInstrucScreenY";
     mGame_TitleX = "Game.TitleX";
     mGame_TitleY = "Game.TitleY";
     mGame_TitleWidth = "Game.TitleWidth";
     mGame_TitleHeight = "Game.TitleHeight";
     mGame_FactorTitleScreenX = "Game.FactorTitleScreenX";
     mGame_FactorTitleScreenY = "Game.FactorTitleScreenY";
     mGame_PlayButtonX = "Game.PlayButtonX";
     mGame_PlayButtonY = "Game.PlayButtonY";
     mGame_PlayButtonWidth = "Game.PlayButtonWidth";
     mGame_PlayButtonHeight = "Game.PlayButtonHeight";
     mGame_FactorPlayBtnScreenX = "Game.FactorPlayBtnScreenX";
     mGame_FactorPlayBtnScreenY = "Game.FactorPlayBtnScreenY";
     mGame_GameOverX = "Game.GameOverX";
     mGame_GameOverY = "Game.GameOverY";
     mGame_GameOverWidth = "Game.GameOverWidth";
     mGame_GameOverHeight = "Game.GameOverHeight";
     mGame_FactorGameOverScreenX = "Game.FactorGameOverScreenX";
     mGame_FactorGameOverScreenY = "Game.FactorGameOverScreenY";
     mGame_MaxDeadTimer = "Game.MaxDeadTimer";
     mGame_FactorShakeTime = "Game.FactorShakeTime";
     mGame_ShakeValue = "Game.ShakeValue";
     mGame_FlyAudioPath = "Game.FlyAudioPath";
     mGame_CollissionAudioPath = "Game.CollissionAudioPath";
     mGame_DieAudioPath = "Game.DieAudioPath";
     mGame_GUIMovementAudioPath = "Game.GUIMovementAudioPath";
     mGame_ScorePointAudioPath = "Game.ScorePointAudioPath";
    
    //GameLevel class string literals
     mGameLevel_ColumnVerticalSeparation = "GameLevel.ColumnVerticalSeparation";
     mGameLevel_MinVerticalPos = "GameLevel.MinVerticalPos";
     mGameLevel_MaxVerticalPos = "GameLevel.MaxVerticalPos";
     mGameLevel_PassThreshold = "GameLevel.PassThreshold";
     mGameLevel_NumColumnPairs = "GameLevel.NumColumnPairs";
     mGameLevel_FactorHorizSeparation = "GameLevel.FactorHorizSeparation";
     mGameLevel_SpriteWidth = "GameLevel.SpriteWidth";
     mGameLevel_SpriteHeight = "GameLevel.SpriteHeight";
     mGameLevel_LowerColX = "GameLevel.LowerColX";
     mGameLevel_LowerColY = "GameLevel.LowerColY";
     mGameLevel_UpperColX = "GameLevel.UpperColX";
     mGameLevel_UpperColY = "GameLevel.UpperColY";
    
    //GUIScore class string literals
     mGUIScore_FlappyBirdSpriteAtlasName = "GUIScore.FlappyBirdSpriteAtlasName";
     mGUIScore_FactorScreenWidthBig = "GUIScore.FactorScreenWidthBig";
     mGUIScore_FactorScreenHeightBig = "GUIScore.FactorScreenHeightBig";
     mGUIScore_WidthBig = "GUIScore.WidthBig";
     mGUIScore_HeightBig = "GUIScore.HeightBig";
     mGUIScore_Num1WidthBig = "GUIScore.Num1WidthBig";
     mGUIScore_OriginYBig = "GUIScore.OriginYBig";
     mGUIScore_Num0XBig = "GUIScore.Num0XBig";
     mGUIScore_Num1XBig = "GUIScore.Num1XBig";
     mGUIScore_Num2XBig = "GUIScore.Num2XBig";
     mGUIScore_Num3XBig = "GUIScore.Num3XBig";
     mGUIScore_Num4XBig = "GUIScore.Num4XBig";
     mGUIScore_Num5XBig = "GUIScore.Num5XBig";
     mGUIScore_Num6XBig = "GUIScore.Num6XBig";
     mGUIScore_Num7XBig = "GUIScore.Num7XBig";
     mGUIScore_Num8XBig = "GUIScore.Num8XBig";
     mGUIScore_Num9XBig = "GUIScore.Num9XBig";
     mGUIScore_SBEdgeOffsetWidth = "GUIScore.SBEdgeOffsetWidth";
     mGUIScore_SBEdgeOffsetHeight = "GUIScore.SBEdgeOffsetHeight";
     mGUIScore_BestEdgeOffsetWidth = "GUIScore.BestEdgeOffsetWidth";
     mGUIScore_BestEdgeOffsetHeight = "GUIScore.BestEdgeOffsetHeight";
     mGUIScore_WidthSmall = "GUIScore.WidthSmall";
     mGUIScore_HeightSmall = "GUIScore.HeightSmall";
     mGUIScore_Num1WidthSmall = "GUIScore.Num1WidthSmall";
     mGUIScore_OriginXSmall = "GUIScore.OriginXSmall";
     mGUIScore_Num0YSmall = "GUIScore.Num0YSmall";
     mGUIScore_Num1YSmall = "GUIScore.Num1YSmall";
     mGUIScore_Num2YSmall = "GUIScore.Num2YSmall";
     mGUIScore_Num3YSmall = "GUIScore.Num3YSmall";
     mGUIScore_Num4YSmall = "GUIScore.Num4YSmall";
     mGUIScore_Num5YSmall = "GUIScore.Num5YSmall";
     mGUIScore_Num6YSmall = "GUIScore.Num6YSmall";
     mGUIScore_Num7YSmall = "GUIScore.Num7YSmall";
     mGUIScore_Num8YSmall = "GUIScore.Num8YSmall";
     mGUIScore_Num9YSmall = "GUIScore.Num9YSmall";
     mGUIScore_ScoreBoardX = "GUIScore.ScoreBoardX";
     mGUIScore_ScoreBoardY = "GUIScore.ScoreBoardY";
     mGUIScore_ScoreBoardWidth = "GUIScore.ScoreBoardWidth";
     mGUIScore_ScoreBoardHeight = "GUIScore.ScoreBoardHeight";
     mGUIScore_SBFactorScreenWidth = "GUIScore.SBFactorScreenWidth";
     mGUIScore_SBFactorScreenHeight = "GUIScore.SBFactorScreenHeight";
     mGUIScore_AscendSpeed = "GUIScore.AscendSpeed";

    //sound effects literals
    mSfxDie = "audio/sfx_die.raw";
    mSfxHit = "audio/sfx_hit.raw";
    mSfxPoint = "audio/sfx_point.raw";
    mSfxSwooshing = "audio/sfx_swooshing.raw";
    mSfxWing = "audio/sfx_wing.raw";
}

const std::string &StringLiterals::GetBirdGameObject_JumpVelocityFactor() {
    return mBirdGameObject_JumpVelocityFactor;
}

const std::string &StringLiterals::GetBirdGameObject_MinVelocity() {
    return mBirdGameObject_MinVelocity;
}

const std::string &StringLiterals::GetBirdGameObject_MaxVelocity() {
    return mBirdGameObject_MaxVelocity;
}

const std::string &StringLiterals::GetBirdGameObject_MinRotation() {
    return mBirdGameObject_MinRotation;
}

const std::string &StringLiterals::GetBirdGameObject_MaxRotation() {
    return mBirdGameObject_MaxRotation;
}

const std::string &StringLiterals::GetBirdGameObject_TimeToStartRotation() {
    return mBirdGameObject_TimeToStartRotation;
}

const std::string &StringLiterals::GetBirdGameObject_TimeToMinRotation() {
    return mBirdGameObject_TimeToMinRotation;
}

const std::string &StringLiterals::GetBirdGameObject_RotSpeeedNotFalling() {
    return mBirdGameObject_RotSpeeedNotFalling;
}

const std::string &StringLiterals::GetBirdGameObject_HoverSpeed() {
    return mBirdGameObject_HoverSpeed;
}

const std::string &StringLiterals::GetBirdGameObject_MaxHoverAmp() {
    return mBirdGameObject_MaxHoverAmp;
}

const std::string &StringLiterals::GetGame_FlappyBirdSpriteAtlasName() {
    return mGame_FlappyBirdSpriteAtlasName;
}

const std::string &StringLiterals::GetGame_FlappyBirdSpriteAtlasPath() {
    return mGame_FlappyBirdSpriteAtlasPath;
}

const std::string &StringLiterals::GetGame_ForegroundTexName() {
    return mGame_ForegroundTexName;
}

const std::string &StringLiterals::GetGame_ForegroundTexPath() {
    return mGame_ForegroundTexPath;
}

const std::string &StringLiterals::GetGame_GameShaderName() {
    return mGame_GameShaderName;
}

const std::string &StringLiterals::GetGame_VertexShaderPath() {
    return mGame_VertexShaderPath;
}

const std::string &StringLiterals::GetGame_FragmentShaderPath() {
    return mGame_FragmentShaderPath;
}

const std::string &StringLiterals::GetGame_BirdSpriteWidth() {
    return mGame_BirdSpriteWidth;
}

const std::string &StringLiterals::GetGame_BirdSpriteHeight() {
    return mGame_BirdSpriteHeight;
}

const std::string &StringLiterals::GetGame_BirdSpriteY() {
    return mGame_BirdSpriteY;
}

const std::string &StringLiterals::GetGame_BirdSprite1X() {
    return mGame_BirdSprite1X;
}

const std::string &StringLiterals::GetGame_BirdSprite2X() {
    return mGame_BirdSprite2X;
}

const std::string &StringLiterals::GetGame_BirdSprite3X() {
    return mGame_BirdSprite3X;
}

const std::string &StringLiterals::GetGame_BirdAnimSpeed() {
    return mGame_BirdAnimSpeed;
}

const std::string &StringLiterals::GetGame_FactorInitScreenPosX() {
    return mGame_FactorInitScreenPosX;
}

const std::string &StringLiterals::GetGame_FactorInitScreenPosY() {
    return mGame_FactorInitScreenPosY;
}

const std::string &StringLiterals::GetGame_FactorStartPosX() {
    return mGame_FactorStartPosX;
}

const std::string &StringLiterals::GetGame_FactorStartPosY() {
    return mGame_FactorStartPosY;
}

const std::string &StringLiterals::GetGame_StartRot() {
    return mGame_StartRot;
}

const std::string &StringLiterals::GetGame_WorldGravity() {
    return mGame_WorldGravity;
}

const std::string &StringLiterals::GetGame_ShiftSpeed() {
    return mGame_ShiftSpeed;
}

const std::string &StringLiterals::GetGame_BGroundSpriteOrigin() {
    return mGame_BGroundSpriteOrigin;
}

const std::string &StringLiterals::GetGame_BGroundSpriteWidth() {
    return mGame_BGroundSpriteWidth;
}

const std::string &StringLiterals::GetGame_BGroundSpriteHeight() {
    return mGame_BGroundSpriteHeight;
}

const std::string &StringLiterals::GetGame_FGroundSpriteOrigin() {
    return mGame_FGroundSpriteOrigin;
}

const std::string &StringLiterals::GetGame_FGroundSpriteWidth() {
    return mGame_FGroundSpriteWidth;
}

const std::string &StringLiterals::GetGame_FGroundSpriteHeight() {
    return mGame_FGroundSpriteHeight;
}

const std::string &StringLiterals::GetGame_FactorFGPosY() {
    return mGame_FactorFGPosY;
}

const std::string &StringLiterals::GetGame_GetReadyX() {
    return mGame_GetReadyX;
}

const std::string &StringLiterals::GetGame_GetReadyY() {
    return mGame_GetReadyY;
}

const std::string &StringLiterals::GetGame_GetReadyWidth() {
    return mGame_GetReadyWidth;
}

const std::string &StringLiterals::GetGame_GetReadyHeight() {
    return mGame_GetReadyHeight;
}

const std::string &StringLiterals::GetGame_FactorGetReadyScreenX() {
    return mGame_FactorGetReadyScreenX;
}

const std::string &StringLiterals::GetGame_FactorGetReadyScreenY() {
    return mGame_FactorGetReadyScreenY;
}

const std::string &StringLiterals::GetGame_InstructionsX() {
    return mGame_InstructionsX;
}

const std::string &StringLiterals::GetGame_InstructionsY() {
    return mGame_InstructionsY;
}

const std::string &StringLiterals::GetGame_InstructionsWidth() {
    return mGame_InstructionsWidth;
}

const std::string &StringLiterals::GetGame_InstructionsHeight() {
    return mGame_InstructionsHeight;
}

const std::string &StringLiterals::GetGame_FactorInstrucScreenX() {
    return mGame_FactorInstrucScreenX;
}

const std::string &StringLiterals::GetGame_FactorInstrucScreenY() {
    return mGame_FactorInstrucScreenY;
}

const std::string &StringLiterals::GetGame_TitleX() {
    return mGame_TitleX;
}

const std::string &StringLiterals::GetGame_TitleY() {
    return mGame_TitleY;
}

const std::string &StringLiterals::GetGame_TitleWidth() {
    return mGame_TitleWidth;
}

const std::string &StringLiterals::GetGame_TitleHeight() {
    return mGame_TitleHeight;
}

const std::string &StringLiterals::GetGame_FactorTitleScreenX() {
    return mGame_FactorTitleScreenX;
}

const std::string &StringLiterals::GetGame_FactorTitleScreenY() {
    return mGame_FactorTitleScreenY;
}

const std::string &StringLiterals::GetGame_PlayButtonX() {
    return mGame_PlayButtonX;
}

const std::string &StringLiterals::GetGame_PlayButtonY() {
    return mGame_PlayButtonY;
}

const std::string &StringLiterals::GetGame_PlayButtonWidth() {
    return mGame_PlayButtonWidth;
}

const std::string &StringLiterals::GetGame_PlayButtonHeight() {
    return mGame_PlayButtonHeight;
}

const std::string &StringLiterals::GetGame_FactorPlayBtnScreenX() {
    return mGame_FactorPlayBtnScreenX;
}

const std::string &StringLiterals::GetGame_FactorPlayBtnScreenY() {
    return mGame_FactorPlayBtnScreenY;
}

const std::string &StringLiterals::GetGame_GameOverX() {
    return mGame_GameOverX;
}

const std::string &StringLiterals::GetGame_GameOverY() {
    return mGame_GameOverY;
}

const std::string &StringLiterals::GetGame_GameOverWidth() {
    return mGame_GameOverWidth;
}

const std::string &StringLiterals::GetGame_GameOverHeight() {
    return mGame_GameOverHeight;
}

const std::string &StringLiterals::GetGame_FactorGameOverScreenX() {
    return mGame_FactorGameOverScreenX;
}

const std::string &StringLiterals::GetGame_FactorGameOverScreenY() {
    return mGame_FactorGameOverScreenY;
}

const std::string &StringLiterals::GetGame_MaxDeadTimer() {
    return mGame_MaxDeadTimer;
}

const std::string &StringLiterals::GetGame_FactorShakeTime() {
    return mGame_FactorShakeTime;
}

const std::string &StringLiterals::GetGame_ShakeValue() {
    return mGame_ShakeValue;
}

const std::string &StringLiterals::GetGame_FlyAudioPath() {
    return mGame_FlyAudioPath;
}

const std::string &StringLiterals::GetGame_CollissionAudioPath() {
    return mGame_CollissionAudioPath;
}

const std::string &StringLiterals::GetGame_DieAudioPath() {
    return mGame_DieAudioPath;
}

const std::string &StringLiterals::GetGame_GUIMovementAudioPath() {
    return mGame_GUIMovementAudioPath;
}

const std::string &StringLiterals::GetGame_ScorePointAudioPath() {
    return mGame_ScorePointAudioPath;
}

const std::string &StringLiterals::GetGameLevel_ColumnVerticalSeparation() {
    return mGameLevel_ColumnVerticalSeparation;
}

const std::string &StringLiterals::GetGameLevel_MinVerticalPos() {
    return mGameLevel_MinVerticalPos;
}

const std::string &StringLiterals::GetGameLevel_MaxVerticalPos() {
    return mGameLevel_MaxVerticalPos;
}

const std::string &StringLiterals::GetGameLevel_PassThreshold() {
    return mGameLevel_PassThreshold;
}

const std::string &StringLiterals::GetGameLevel_NumColumnPairs() {
    return mGameLevel_NumColumnPairs;
}

const std::string &StringLiterals::GetGameLevel_FactorHorizSeparation() {
    return mGameLevel_FactorHorizSeparation;
}

const std::string &StringLiterals::GetGameLevel_SpriteWidth() {
    return mGameLevel_SpriteWidth;
}

const std::string &StringLiterals::GetGameLevel_SpriteHeight() {
    return mGameLevel_SpriteHeight;
}

const std::string &StringLiterals::GetGameLevel_LowerColX() {
    return mGameLevel_LowerColX;
}

const std::string &StringLiterals::GetGameLevel_LowerColY() {
    return mGameLevel_LowerColY;
}

const std::string &StringLiterals::GetGameLevel_UpperColX() {
    return mGameLevel_UpperColX;
}

const std::string &StringLiterals::GetGameLevel_UpperColY() {
    return mGameLevel_UpperColY;
}

const std::string &StringLiterals::GetGUIScore_FlappyBirdSpriteAtlasName() {
    return mGUIScore_FlappyBirdSpriteAtlasName;
}

const std::string &StringLiterals::GetGUIScore_FactorScreenWidthBig() {
    return mGUIScore_FactorScreenWidthBig;
}

const std::string &StringLiterals::GetGUIScore_FactorScreenHeightBig() {
    return mGUIScore_FactorScreenHeightBig;
}

const std::string &StringLiterals::GetGUIScore_WidthBig() {
    return mGUIScore_WidthBig;
}

const std::string &StringLiterals::GetGUIScore_HeightBig() {
    return mGUIScore_HeightBig;
}

const std::string &StringLiterals::GetGUIScore_Num1WidthBig() {
    return mGUIScore_Num1WidthBig;
}

const std::string &StringLiterals::GetGUIScore_OriginYBig() {
    return mGUIScore_OriginYBig;
}

const std::string &StringLiterals::GetGUIScore_Num0XBig() {
    return mGUIScore_Num0XBig;
}

const std::string &StringLiterals::GetGUIScore_Num1XBig() {
    return mGUIScore_Num1XBig;
}

const std::string &StringLiterals::GetGUIScore_Num2XBig() {
    return mGUIScore_Num2XBig;
}

const std::string &StringLiterals::GetGUIScore_Num3XBig() {
    return mGUIScore_Num3XBig;
}

const std::string &StringLiterals::GetGUIScore_Num4XBig() {
    return mGUIScore_Num4XBig;
}

const std::string &StringLiterals::GetGUIScore_Num5XBig() {
    return mGUIScore_Num5XBig;
}

const std::string &StringLiterals::GetGUIScore_Num6XBig() {
    return mGUIScore_Num6XBig;
}

const std::string &StringLiterals::GetGUIScore_Num7XBig() {
    return mGUIScore_Num7XBig;
}

const std::string &StringLiterals::GetGUIScore_Num8XBig() {
    return mGUIScore_Num8XBig;
}

const std::string &StringLiterals::GetGUIScore_Num9XBig() {
    return mGUIScore_Num9XBig;
}

const std::string &StringLiterals::GetGUIScore_SBEdgeOffsetWidth() {
    return mGUIScore_SBEdgeOffsetWidth;
}

const std::string &StringLiterals::GetGUIScore_SBEdgeOffsetHeight() {
    return mGUIScore_SBEdgeOffsetHeight;
}

const std::string &StringLiterals::GetGUIScore_BestEdgeOffsetWidth() {
    return mGUIScore_BestEdgeOffsetWidth;
}

const std::string &StringLiterals::GetGUIScore_BestEdgeOffsetHeight() {
    return mGUIScore_BestEdgeOffsetHeight;
}

const std::string &StringLiterals::GetGUIScore_WidthSmall() {
    return mGUIScore_WidthSmall;
}

const std::string &StringLiterals::GetGUIScore_HeightSmall() {
    return mGUIScore_HeightSmall;
}

const std::string &StringLiterals::GetGUIScore_Num1WidthSmall() {
    return mGUIScore_Num1WidthSmall;
}

const std::string &StringLiterals::GetGUIScore_OriginXSmall() {
    return mGUIScore_OriginXSmall;
}

const std::string &StringLiterals::GetGUIScore_Num0YSmall() {
    return mGUIScore_Num0YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num1YSmall() {
    return mGUIScore_Num1YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num2YSmall() {
    return mGUIScore_Num2YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num3YSmall() {
    return mGUIScore_Num3YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num4YSmall() {
    return mGUIScore_Num4YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num5YSmall() {
    return mGUIScore_Num5YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num6YSmall() {
    return mGUIScore_Num6YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num7YSmall() {
    return mGUIScore_Num7YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num8YSmall() {
    return mGUIScore_Num8YSmall;
}

const std::string &StringLiterals::GetGUIScore_Num9YSmall() {
    return mGUIScore_Num9YSmall;
}

const std::string &StringLiterals::GetGUIScore_ScoreBoardX() {
    return mGUIScore_ScoreBoardX;
}

const std::string &StringLiterals::GetGUIScore_ScoreBoardY() {
    return mGUIScore_ScoreBoardY;
}

const std::string &StringLiterals::GetGUIScore_ScoreBoardWidth() {
    return mGUIScore_ScoreBoardWidth;
}

const std::string &StringLiterals::GetGUIScore_ScoreBoardHeight() {
    return mGUIScore_ScoreBoardHeight;
}

const std::string &StringLiterals::GetGUIScore_SBFactorScreenWidth() {
    return mGUIScore_SBFactorScreenWidth;
}

const std::string &StringLiterals::GetGUIScore_SBFactorScreenHeight() {
    return mGUIScore_SBFactorScreenHeight;
}

const std::string &StringLiterals::GetGUIScore_AscendSpeed() {
    return mGUIScore_AscendSpeed;
}

const std::string &StringLiterals::GetSfxDie(){
    return mSfxDie;
}

const std::string &StringLiterals::GetSfxHit(){
    return mSfxHit;
}

const std::string &StringLiterals::GetSfxPoint(){
    return mSfxPoint;
}

const std::string &StringLiterals::GetSfxSwooshing(){
    return mSfxSwooshing;
}

const std::string &StringLiterals::GetSfxWing(){
    return mSfxWing;
}

//BirdGameOject class string literals definition
 std::string StringLiterals::mBirdGameObject_JumpVelocityFactor;
 std::string StringLiterals::mBirdGameObject_MinVelocity;
 std::string StringLiterals::mBirdGameObject_MaxVelocity;
 std::string StringLiterals::mBirdGameObject_MinRotation;
 std::string StringLiterals::mBirdGameObject_MaxRotation;
 std::string StringLiterals::mBirdGameObject_TimeToStartRotation;
 std::string StringLiterals::mBirdGameObject_TimeToMinRotation;
 std::string StringLiterals::mBirdGameObject_RotSpeeedNotFalling;
 std::string StringLiterals::mBirdGameObject_HoverSpeed;
 std::string StringLiterals::mBirdGameObject_MaxHoverAmp;

//Game class string literals definition
 std::string StringLiterals::mGame_FlappyBirdSpriteAtlasName;
 std::string StringLiterals::mGame_FlappyBirdSpriteAtlasPath;
 std::string StringLiterals::mGame_ForegroundTexName;
 std::string StringLiterals::mGame_ForegroundTexPath;
 std::string StringLiterals::mGame_GameShaderName;
 std::string StringLiterals::mGame_VertexShaderPath;
 std::string StringLiterals::mGame_FragmentShaderPath;
 std::string StringLiterals::mGame_BirdSpriteWidth;
 std::string StringLiterals::mGame_BirdSpriteHeight;
 std::string StringLiterals::mGame_BirdSpriteY;
 std::string StringLiterals::mGame_BirdSprite1X;
 std::string StringLiterals::mGame_BirdSprite2X;
 std::string StringLiterals::mGame_BirdSprite3X;
 std::string StringLiterals::mGame_BirdAnimSpeed;
 std::string StringLiterals::mGame_FactorInitScreenPosX;
 std::string StringLiterals::mGame_FactorInitScreenPosY;
 std::string StringLiterals::mGame_FactorStartPosX;
 std::string StringLiterals::mGame_FactorStartPosY;
 std::string StringLiterals::mGame_StartRot;
 std::string StringLiterals::mGame_WorldGravity;
 std::string StringLiterals::mGame_ShiftSpeed;
 std::string StringLiterals::mGame_BGroundSpriteOrigin;
 std::string StringLiterals::mGame_BGroundSpriteWidth;
 std::string StringLiterals::mGame_BGroundSpriteHeight;
 std::string StringLiterals::mGame_FGroundSpriteOrigin;
 std::string StringLiterals::mGame_FGroundSpriteWidth;
 std::string StringLiterals::mGame_FGroundSpriteHeight;
 std::string StringLiterals::mGame_FactorFGPosY;
 std::string StringLiterals::mGame_GetReadyX;
 std::string StringLiterals::mGame_GetReadyY;
 std::string StringLiterals::mGame_GetReadyWidth;
 std::string StringLiterals::mGame_GetReadyHeight;
 std::string StringLiterals::mGame_FactorGetReadyScreenX;
 std::string StringLiterals::mGame_FactorGetReadyScreenY;
 std::string StringLiterals::mGame_InstructionsX;
 std::string StringLiterals::mGame_InstructionsY;
 std::string StringLiterals::mGame_InstructionsWidth;
 std::string StringLiterals::mGame_InstructionsHeight;
 std::string StringLiterals::mGame_FactorInstrucScreenX;
 std::string StringLiterals::mGame_FactorInstrucScreenY;
 std::string StringLiterals::mGame_TitleX;
 std::string StringLiterals::mGame_TitleY;
 std::string StringLiterals::mGame_TitleWidth;
 std::string StringLiterals::mGame_TitleHeight;
 std::string StringLiterals::mGame_FactorTitleScreenX;
 std::string StringLiterals::mGame_FactorTitleScreenY;
 std::string StringLiterals::mGame_PlayButtonX;
 std::string StringLiterals::mGame_PlayButtonY;
 std::string StringLiterals::mGame_PlayButtonWidth;
 std::string StringLiterals::mGame_PlayButtonHeight;
 std::string StringLiterals::mGame_FactorPlayBtnScreenX;
 std::string StringLiterals::mGame_FactorPlayBtnScreenY;
 std::string StringLiterals::mGame_GameOverX;
 std::string StringLiterals::mGame_GameOverY;
 std::string StringLiterals::mGame_GameOverWidth;
 std::string StringLiterals::mGame_GameOverHeight;
 std::string StringLiterals::mGame_FactorGameOverScreenX;
 std::string StringLiterals::mGame_FactorGameOverScreenY;
 std::string StringLiterals::mGame_MaxDeadTimer;
 std::string StringLiterals::mGame_FactorShakeTime;
 std::string StringLiterals::mGame_ShakeValue;
 std::string StringLiterals::mGame_FlyAudioPath;
 std::string StringLiterals::mGame_CollissionAudioPath;
 std::string StringLiterals::mGame_DieAudioPath;
 std::string StringLiterals::mGame_GUIMovementAudioPath;
 std::string StringLiterals::mGame_ScorePointAudioPath;

//GameLevel class string literals definition
 std::string StringLiterals::mGameLevel_ColumnVerticalSeparation;
 std::string StringLiterals::mGameLevel_MinVerticalPos;
 std::string StringLiterals::mGameLevel_MaxVerticalPos;
 std::string StringLiterals::mGameLevel_PassThreshold;
 std::string StringLiterals::mGameLevel_NumColumnPairs;
 std::string StringLiterals::mGameLevel_FactorHorizSeparation;
 std::string StringLiterals::mGameLevel_SpriteWidth;
 std::string StringLiterals::mGameLevel_SpriteHeight;
 std::string StringLiterals::mGameLevel_LowerColX;
 std::string StringLiterals::mGameLevel_LowerColY;
 std::string StringLiterals::mGameLevel_UpperColX;
 std::string StringLiterals::mGameLevel_UpperColY;

//GUIScore class string literals definition
 std::string StringLiterals::mGUIScore_FlappyBirdSpriteAtlasName;
 std::string StringLiterals::mGUIScore_FactorScreenWidthBig;
 std::string StringLiterals::mGUIScore_FactorScreenHeightBig;
 std::string StringLiterals::mGUIScore_WidthBig;
 std::string StringLiterals::mGUIScore_HeightBig;
 std::string StringLiterals::mGUIScore_Num1WidthBig;
 std::string StringLiterals::mGUIScore_OriginYBig;
 std::string StringLiterals::mGUIScore_Num0XBig;
 std::string StringLiterals::mGUIScore_Num1XBig;
 std::string StringLiterals::mGUIScore_Num2XBig;
 std::string StringLiterals::mGUIScore_Num3XBig;
 std::string StringLiterals::mGUIScore_Num4XBig;
 std::string StringLiterals::mGUIScore_Num5XBig;
 std::string StringLiterals::mGUIScore_Num6XBig;
 std::string StringLiterals::mGUIScore_Num7XBig;
 std::string StringLiterals::mGUIScore_Num8XBig;
 std::string StringLiterals::mGUIScore_Num9XBig;
 std::string StringLiterals::mGUIScore_SBEdgeOffsetWidth;
 std::string StringLiterals::mGUIScore_SBEdgeOffsetHeight;
 std::string StringLiterals::mGUIScore_BestEdgeOffsetWidth;
 std::string StringLiterals::mGUIScore_BestEdgeOffsetHeight;
 std::string StringLiterals::mGUIScore_WidthSmall;
 std::string StringLiterals::mGUIScore_HeightSmall;
 std::string StringLiterals::mGUIScore_Num1WidthSmall;
 std::string StringLiterals::mGUIScore_OriginXSmall;
 std::string StringLiterals::mGUIScore_Num0YSmall;
 std::string StringLiterals::mGUIScore_Num1YSmall;
 std::string StringLiterals::mGUIScore_Num2YSmall;
 std::string StringLiterals::mGUIScore_Num3YSmall;
 std::string StringLiterals::mGUIScore_Num4YSmall;
 std::string StringLiterals::mGUIScore_Num5YSmall;
 std::string StringLiterals::mGUIScore_Num6YSmall;
 std::string StringLiterals::mGUIScore_Num7YSmall;
 std::string StringLiterals::mGUIScore_Num8YSmall;
 std::string StringLiterals::mGUIScore_Num9YSmall;
 std::string StringLiterals::mGUIScore_ScoreBoardX;
 std::string StringLiterals::mGUIScore_ScoreBoardY;
 std::string StringLiterals::mGUIScore_ScoreBoardWidth;
 std::string StringLiterals::mGUIScore_ScoreBoardHeight;
 std::string StringLiterals::mGUIScore_SBFactorScreenWidth;
 std::string StringLiterals::mGUIScore_SBFactorScreenHeight;
 std::string StringLiterals::mGUIScore_AscendSpeed;

//audio string literals
std::string StringLiterals::mSfxDie;
std::string StringLiterals::mSfxHit;
std::string StringLiterals::mSfxPoint;
std::string StringLiterals::mSfxSwooshing;
std::string StringLiterals::mSfxWing;