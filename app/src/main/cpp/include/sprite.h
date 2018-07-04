#ifndef FLAPPYBIRDANDROID_SPRITE_H
#define FLAPPYBIRDANDROID_SPRITE_H

#include "texture2D.h"

class Sprite final
{
public:
    Sprite(const Texture2D &texture, int originX, int originY, int width, int height);
    ~Sprite();
    const Texture2D& GetTexture() const;
    float* GetTextureCoords() const;
    int GetWidth() const;
    int GetHeight() const;

private:
    Texture2D mTexture;
    float *mTexCoords = nullptr;
    const int mCoordsSize = 12;
    int mWidth = 0;
    int mHeight = 0;

};
#endif //FLAPPYBIRDANDROID_SPRITE_H
