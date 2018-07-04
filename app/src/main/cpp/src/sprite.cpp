#include "sprite.h"
#include "texture2D.h"
#include "globals.h"

Sprite::Sprite(const Texture2D &texture,
               int originX, int originY, int width, int height) : mTexture(texture), mWidth(width), mHeight(height) {

    /*Triangles vertices order
     *
     *      3,6 ----- 5
     *      |  \      |
     *      |    \    |
     *      |      \  |
     *      1-------2,4
     */
    //Adptation from origin at the top left (image coord system) to origin at the bottom left (OpenGL coord system)
    float vertex1X = (float) (originX) / mTexture.GetWidth();
    float vertex1Y = (float) (mTexture.GetHeight() - originY - height) / mTexture.GetHeight();

    float vertex2X = (float) (originX + width) / mTexture.GetWidth();
    float vertex2Y = vertex1Y;

    float vertex3X = vertex1X;
    float vertex3Y = (float) (mTexture.GetHeight() - originY) / mTexture.GetHeight();

    float vertex4X = vertex2X;
    float vertex4Y = vertex1Y;

    float vertex5X = vertex2X;
    float vertex5Y = vertex3Y;

    float vertex6X = vertex1X;
    float vertex6Y = vertex3Y;

    mTexCoords = new float[mCoordsSize]{
            vertex1X, vertex1Y,
            vertex2X, vertex2Y,
            vertex3X, vertex3Y,
            vertex4X, vertex4Y,
            vertex5X, vertex5Y,
            vertex6X, vertex6Y
    };
}

Sprite::~Sprite()
{
    DELETE_PTR_ARRAY(mTexCoords);

}

const Texture2D& Sprite::GetTexture() const
{
    return mTexture;
}

float* Sprite::GetTextureCoords() const
{
    return mTexCoords;
}

int Sprite::GetWidth() const
{
    return mWidth;
}

int Sprite::GetHeight() const
{
    return mHeight;
}
