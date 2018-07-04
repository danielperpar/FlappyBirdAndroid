#include "sound_manager.h"
#include <android/log.h>
#include "resource_manager.h"
#include "android/asset_manager.h"

SoundManager::SoundManager() : mEngineObj(nullptr), mEngine(nullptr), mOutputMixObj(nullptr)
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Creating SoundManager.");
}
SoundManager::~SoundManager(){
    Stop();
}

void SoundManager::Start()
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Starting SoundManager.");

    SLresult result;
    const SLuint32 engineMixIIDCount = 1;
    const SLInterfaceID engineMixIIDs[] = {SL_IID_ENGINE};
    const SLboolean engineMixReqs[] = {SL_BOOLEAN_TRUE};
    const SLuint32 outputMixIIDCount = 0;
    const SLInterfaceID outputMixIIDs[] = {};
    const SLboolean outputMixReqs[] = {};

    // Creates OpenSL ES engine and dumps its capabilities.
    result = slCreateEngine(&mEngineObj, 0, nullptr, engineMixIIDCount, engineMixIIDs, engineMixReqs);
    CheckSLError(result);

    result = (*mEngineObj)->Realize(mEngineObj, SL_BOOLEAN_FALSE);
    CheckSLError(result);

    result = (*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE, &mEngine);
    CheckSLError(result);

    //Creates audio output.
    result = (*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj, outputMixIIDCount, outputMixIIDs, outputMixReqs);
    CheckSLError(result);

    result = (*mOutputMixObj)->Realize(mOutputMixObj, SL_BOOLEAN_FALSE);
    CheckSLError(result);

    //Initialize sound queues
    for(int i = 0; i < QUEUE_COUNT; i++)
    {
        mSoundQueues[i].Initialize(mEngine, mOutputMixObj);
    }
}

void SoundManager::Stop()
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Stopping SoundManager.");

    //Destroy sound queues
    for(int i = 0; i < QUEUE_COUNT; i++)
    {
        mSoundQueues[i].Finalize();
    }

    if(mOutputMixObj != nullptr)
    {
        (*mOutputMixObj)->Destroy(mOutputMixObj);
        mOutputMixObj = nullptr;
    }

    if(mEngineObj != nullptr)
    {
        (*mEngineObj)->Destroy(mEngineObj);
        mEngineObj = nullptr;
    }
}

void SoundManager::LoadSound(AAssetManager *assetManager, std::string soundPath)
{
    ResourceManager::LoadSound(assetManager, soundPath);
}

void SoundManager::Play(std::string soundPath)
{
    mSoundQueues[mCurrentCount].PlaySound(ResourceManager::GetSound(soundPath));
    mCurrentCount++;
    mCurrentCount %= QUEUE_COUNT;
}

void SoundManager::CheckSLError(SLresult result)
{
    if(result != SL_RESULT_SUCCESS)
    {
        __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "Error while starting SoundManager");
        Stop();
    }
}