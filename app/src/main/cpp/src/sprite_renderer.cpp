#include "sprite_renderer.h"
#include <glm/gtx/transform.hpp>
#include "sprite.h"

SpriteRenderer::SpriteRenderer(const Shader &shader, const glm::vec2 &screenScaling) : mShader(shader), mScreenScaling(screenScaling){
    Init();
}

SpriteRenderer::~SpriteRenderer()
{
    //OpenGL context is destoyed and resources are freed on Activity onDestroy().
    //It's not required to free resources manually
    //glDeleteBuffers(1, &mQuadVBO);
}

void SpriteRenderer::DrawSprite(const Sprite *sprite, const glm::vec2 &position, float rotInDegrees, float alpha) const
{
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));

    //Rotate the sprite around the center of the quad
    model = glm::translate(model, glm::vec3(0.5f * sprite->GetWidth() * mScreenScaling.x, 0.5f * sprite->GetHeight() * mScreenScaling.y, 0.0f));
    model = glm::rotate(model, glm::radians<float>(rotInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * sprite->GetWidth() * mScreenScaling.x, -0.5f * sprite->GetHeight() * mScreenScaling.y, 0.0f));

    model = glm::scale(model, glm::vec3(sprite->GetWidth() * mScreenScaling.x, sprite->GetHeight() * mScreenScaling.y, 1.0f));

    mShader.SetMatrix4("model", model);
    mShader.SetFloat("alpha", alpha);

    glBindBuffer(GL_ARRAY_BUFFER, mQuadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, mCoordsSize *  sizeof(float),  mCoordsSize * sizeof(float), sprite->GetTextureCoords());
    glActiveTexture(GL_TEXTURE0);
    sprite->GetTexture().Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteRenderer::DrawSpritesShifted(const Sprite *sprite, const glm::vec2 &position, float deltaShift) const
{
     float *texCoords = sprite->GetTextureCoords();
     int texWidth = sprite->GetTexture().GetWidth();

    for (int i = 0; i < mCoordsSize; i += 2)
    {
        //convert shift in pixels to shift in texture coordinates:  pixel to texture = shift/texture_width
        texCoords[i] += (deltaShift / texWidth);
    }

    DrawSprite(sprite, position, 0.0f);
}

bool SpriteRenderer::FadedPerformed(bool isFadingIn, float dt)
{
    bool ret = false;

    if (isFadingIn)
    {
        mAlpha += mFadeSpeed * dt;
        if (mAlpha > 1.0f)
        {
            ret = true;
            mAlpha = 1.0f;
        }
    }
    else
    {
        mAlpha -= mFadeSpeed * dt;
        if (mAlpha < 0.0f)
        {
            ret = true;
            mAlpha = 0.0f;
        }
    }
    return ret;
}
void SpriteRenderer::DrawSpriteFaded(const Sprite *sprite, const glm::vec2 &position) const
{
    DrawSprite(sprite, position, 0.0f, mAlpha);
}

void SpriteRenderer::ResetAlpha()
{
    mAlpha = 0.0f;
}


void SpriteRenderer::Init()
{
    float vertices[] = { 0.0f, 0.0f,
                         1.0f, 0.0f,
                         0.0f, 1.0f,
                         1.0f, 0.0f,
                         1.0f, 1.0f,
                         0.0f, 1.0f
    };


    float texCoords[] = { 0.0f, 0.0f,
                          1.0f, 0.0f,
                          0.0f, 1.0f,
                          1.0f, 0.0f,
                          1.0f, 1.0f,
                          0.0f, 1.0f
    };

    glGenBuffers(1, &mQuadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mQuadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(texCoords), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(texCoords), texCoords);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(vertices)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}