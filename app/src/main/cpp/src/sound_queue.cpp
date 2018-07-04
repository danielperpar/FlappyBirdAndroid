#include "sound_queue.h"
#include "android/log.h"
#include "sound.h"


SoundQueue::SoundQueue(): mPlayerObj(nullptr), mPlayer(nullptr), mPlayerQueue(nullptr){};

SoundQueue::~SoundQueue(){}

void SoundQueue::Initialize(SLEngineItf pEngine, SLObjectItf pOutputMixObj)
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid", "Starting sound player.");

    SLresult result;
    // Set-up sound audio source.
    SLDataLocator_AndroidSimpleBufferQueue dataLocatorIn;
    dataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
    // At most one buffer in the queue.
    dataLocatorIn.numBuffers = 1;

    SLDataFormat_PCM dataFormat;
    dataFormat.formatType = SL_DATAFORMAT_PCM;
    dataFormat.numChannels = 1; // Mono sound.
    dataFormat.samplesPerSec = SL_SAMPLINGRATE_44_1;
    dataFormat.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
    dataFormat.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
    dataFormat.channelMask = SL_SPEAKER_FRONT_CENTER;
    dataFormat.endianness = SL_BYTEORDER_LITTLEENDIAN;

    SLDataSource dataSource;
    dataSource.pLocator = &dataLocatorIn;
    dataSource.pFormat = &dataFormat;
    SLDataLocator_OutputMix dataLocatorOut;
    dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    dataLocatorOut.outputMix = pOutputMixObj;

    SLDataSink dataSink;
    dataSink.pLocator = &dataLocatorOut;
    dataSink.pFormat = NULL;

    const SLuint32 soundPlayerIIDCount = 2;
    const SLInterfaceID soundPlayerIIDs[] = { SL_IID_PLAY, SL_IID_BUFFERQUEUE };
    const SLboolean soundPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
    result = (*pEngine)->CreateAudioPlayer(pEngine, &mPlayerObj, &dataSource, &dataSink, soundPlayerIIDCount, soundPlayerIIDs, soundPlayerReqs);
    CheckSLError(result);
    result = (*mPlayerObj)->Realize(mPlayerObj, SL_BOOLEAN_FALSE);
    CheckSLError(result);
    result = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_PLAY, &mPlayer);
    CheckSLError(result);
    result = (*mPlayerObj)->GetInterface(mPlayerObj, SL_IID_BUFFERQUEUE, &mPlayerQueue);
    CheckSLError(result);
    result = (*mPlayer)->SetPlayState(mPlayer, SL_PLAYSTATE_PLAYING);
    CheckSLError(result);
}

void SoundQueue::Finalize()
{
    __android_log_print(ANDROID_LOG_INFO, "FlappyBirdAndroid","Stopping SoundQueue.");

    if (mPlayerObj != nullptr)
    {
        (*mPlayerObj)->Destroy(mPlayerObj);
        mPlayerObj = nullptr;
        mPlayer = nullptr;
        mPlayerQueue = nullptr;
    }
}

void SoundQueue::PlaySound(Sound* pSound)
{
    SLresult result;
    SLuint32 playerState;
    (*mPlayerObj)->GetState(mPlayerObj, &playerState);
    if (playerState == SL_OBJECT_STATE_REALIZED) {
        int16_t* buffer = (int16_t*) pSound->GetBuffer();
        off_t length = pSound->GetLength();

        // Removes any sound from the queue.
        result = (*mPlayerQueue)->Clear(mPlayerQueue);
        if(result != SL_RESULT_SUCCESS)
        {
            __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "Error trying to play sound.");
        }

        // Plays the new sound.
        result = (*mPlayerQueue)->Enqueue(mPlayerQueue, buffer, length);
        if(result != SL_RESULT_SUCCESS)
        {
            __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "Error trying to play sound.");
        }
    }
}

void SoundQueue::CheckSLError(SLresult result)
{
    if(result != SL_RESULT_SUCCESS)
    {
        __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "Error while starting SoundQueue.");
    }
}