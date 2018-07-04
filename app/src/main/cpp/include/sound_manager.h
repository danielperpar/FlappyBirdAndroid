#ifndef FLAPPYBIRDANDROID_SOUND_MANAGER_H
#define FLAPPYBIRDANDROID_SOUND_MANAGER_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "sound_queue.h"
#include <string>

struct AAssetManager;
class SoundManager final
{
public:
    SoundManager();
    ~SoundManager();

    void Start();
    void Stop();
    void LoadSound(AAssetManager *assetManager, std::string soundPath);
    void Play(std::string soundPath);

private:
    SLObjectItf mEngineObj;
    SLEngineItf mEngine;
    SLObjectItf mOutputMixObj;

    static const int QUEUE_COUNT = 4;
    SoundQueue mSoundQueues[QUEUE_COUNT];
    int mCurrentCount = 0;

    void CheckSLError(SLresult result);
};

#endif //FLAPPYBIRDANDROID_SOUND_MANAGER_H
