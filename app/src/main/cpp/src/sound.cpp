#include "sound.h"
#include "globals.h"

Sound::Sound(std::string name) : mName(name){}

Sound::~Sound()
{
    DELETE_PTR(mBuffer);
}

void Sound::SetSoundBuffer(uint8_t *soundBuffer)
{
    mBuffer = soundBuffer;
}

void Sound::SetBufferLength(off_t length)
{
    mLength = length;
}

uint8_t *Sound::GetBuffer() const
{
    return mBuffer;
}

off_t Sound::GetLength() const
{
    return mLength;
}