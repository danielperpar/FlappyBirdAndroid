#ifndef FLAPPYBIRDANDROID_SOUND_QUEUE_H
#define FLAPPYBIRDANDROID_SOUND_QUEUE_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class Sound;
class SoundQueue final
{
public:
    SoundQueue();
    ~SoundQueue();
    void Initialize(SLEngineItf pEngine, SLObjectItf pOutputMixObj);
    void Finalize();
    void PlaySound(Sound* pSound);

private:
    SLObjectItf mPlayerObj;
    SLPlayItf mPlayer;
    SLBufferQueueItf mPlayerQueue;

    void CheckSLError(SLresult result);

};

#endif //FLAPPYBIRDANDROID_SOUND_QUEUE_H
