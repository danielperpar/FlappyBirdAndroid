#ifndef FLAPPYBIRDANDROID_SOUND_H
#define FLAPPYBIRDANDROID_SOUND_H

#include <string>

class Sound final
{
public:
    Sound(std::string name);
    ~Sound();

    void SetSoundBuffer(uint8_t *soundBuffer);
    void SetBufferLength(off_t length);
    uint8_t *GetBuffer() const;
    off_t GetLength() const;

private:
    std::string mName;
    uint8_t *mBuffer = nullptr;
    off_t mLength = 0;
};

#endif //FLAPPYBIRDANDROID_SOUND_H
