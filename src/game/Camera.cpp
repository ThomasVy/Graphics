#include "Camera.h"

namespace game
{

Camera::Camera(const float originalDistance)
: m_distance(originalDistance)
{}


void Camera::FollowObject(GameObject* object)
{
    m_followingObject = object;
}

void Camera::AddZoom(const float zoomDelta)
{
    m_distance += zoomDelta;
    if (m_distance < 1.0f) 
        m_distance = 1.0f;
}

void Camera::SetProjection(const my_math::mat4& projection)
{
    m_projectionMatrix = projection;
}

my_math::mat4 Camera::GetViewProjectionMatrix() const
{
    const my_math::vec3 positionOfFocusedObject = std::invoke([this](){
        return m_followingObject ?  m_followingObject->GetPosition() : my_math::vec3(0.0f);
    });

    my_math::vec3 eye = my_math::vec3(positionOfFocusedObject.x, positionOfFocusedObject.y, m_distance); //position of the camera
    my_math::vec3 center = my_math::vec3(positionOfFocusedObject.x, positionOfFocusedObject.y, 0.0f); //where the camera is looking at
    my_math::vec3 up = my_math::vec3(0.0f, 1.0f, 0.0f);
    my_math::mat4 view = my_math::lookAt(eye, center, up);
    return m_projectionMatrix * view;
}

void Camera::Update(const float timeElapsed)
{
    //noop
}

} // namespace game
