#ifndef FLAPPYBIRDANDROID_SPRITE_RENDERER_H
#define FLAPPYBIRDANDROID_SPRITE_RENDERER_H

#include <GLES2/gl2.h>
#include "shader.h"
#include "texture2D.h"
#include <glm/glm.hpp>

class Sprite;
class Animation;
class SpriteRenderer final
{
public:
    SpriteRenderer(const Shader &shader, const glm::vec2 &screenScaling);
    ~SpriteRenderer();
    void DrawSprite(const Sprite *sprite, const glm::vec2 &position, float rotInDegrees, float alpha = 1.0f) const;
    void DrawSpritesShifted(const Sprite *sprite, const glm::vec2 &position, float deltaShift) const;
    bool FadedPerformed(bool isFadingIn, float dt);
    void DrawSpriteFaded(const Sprite *sprite, const glm::vec2 &position) const;
    void ResetAlpha();

private:
    Shader mShader;
    GLuint mQuadVBO;
    glm::vec2 mScreenScaling;
    float mFadeSpeed = 5.0f;
    float mAlpha = 0.0f;
    const int mCoordsSize = 12;

    void Init();
};
#endif //FLAPPYBIRDANDROID_SPRITE_RENDERER_H
