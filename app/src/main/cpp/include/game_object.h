#ifndef FLAPPYBIRDANDROID_GAME_OBJECT_H
#define FLAPPYBIRDANDROID_GAME_OBJECT_H

#include <glm/glm.hpp>
#include "animation.h"
#include "sprite_renderer.h"
#include <vector>

class GameObject
{
public:
    GameObject(glm::vec2 position, float rotInDegrees, glm::vec2 velocity, Animation* animation, int shakeValue);
    virtual ~GameObject();
    virtual void UpdatePosition(float dt);
    void Draw(const SpriteRenderer *spriteRenderer, float dt) const;
    void PrepareShake();
    void BeginShake();
    void EndShake();

    const glm::vec2& GetPosition() const;
    void SetPosition(const glm::vec2 &position);
    float GetRotInDegrees() const;
    void SetRotInDegrees(float rotInDegrees);
    const glm::vec2 &GetVelocity() const;
    const Animation *GetAnimation() const;
    int GetShakeValue() const;
    const glm::vec2 &GetPosBeforeShake() const;

protected:
    glm::vec2 mPosition;
    float mRotInDegrees = 0.0f;
    glm::vec2 mVelocity;
    Animation *mAnimation = nullptr;
    int mShakeValue = 3;
    glm::vec2 mPosBeforeShake;

    void Clear();
};
#endif //FLAPPYBIRDANDROID_GAME_OBJECT_H
