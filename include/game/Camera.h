#pragma once
#include "GameObject.h"
#include "math/MatrixAndVectorMath.h"

namespace game
{

class Camera
{
public:
    Camera(const float originalDistance);
    void FollowObject(GameObject* object);
    void Update(const float timeElapsed);
    my_math::mat4 GetViewProjectionMatrix () const;
    void SetProjection( const my_math::mat4& projection );
    void AddZoom(const float zoomDelta);
    
private:
    GameObject* m_followingObject{nullptr};
    float m_distance{0.0f};
    my_math::mat4 m_projectionMatrix{1.0f};
};
} // namespace game
