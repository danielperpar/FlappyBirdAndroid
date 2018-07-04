#ifndef FLAPPYBIRDANDROID_TEXTURE2D_H
#define FLAPPYBIRDANDROID_TEXTURE2D_H

#include <GLES2/gl2.h>
#include <stdio.h>

struct AAssetManager;
class Texture2D final
{
public:

    Texture2D(int width, int height, unsigned char *image);
    void Bind() const;
    int GetWidth() const;
    int GetHeight() const;
    void Clear();

private:
    GLuint mTexId;
    int mWidth;
    int mHeight;
    GLuint mWrapS;
    GLuint mWrapT;
    GLuint mFilterMin;
    GLuint mFilterMag;
};

#endif //FLAPPYBIRDANDROID_TEXTURE2D_H
