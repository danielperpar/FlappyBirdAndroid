#include "texture2D.h"
#include <GLES2/gl2.h>

Texture2D::Texture2D(int width, int height, unsigned char *image) : mWrapS(GL_REPEAT), mWrapT(GL_REPEAT), mFilterMin(GL_LINEAR), mFilterMag(GL_LINEAR)
{
    mWidth = width;
    mHeight = height;

    glGenTextures(1, &mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilterMag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, mTexId);
}

int Texture2D::GetWidth() const
{
    return mWidth;
}

int Texture2D::GetHeight() const
{
    return mHeight;
}

void Texture2D::Clear()
{
    glDeleteTextures(1, &mTexId);
}