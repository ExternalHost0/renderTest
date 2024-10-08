//
// Created by Hayden Rivas on 7/12/24.
//


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


#ifndef RENDERTEST_CAMERA_H
#define RENDERTEST_CAMERA_H

#include "../../Structs.h"

class Camera {
private:
    // things that you should keep as is
    float yaw = -90.0f;
    float pitch = 0.0f;

    vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
    vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

    float aspectRatio = 1.33f;

public:

    // things you can change per camera
    vec3 m_Position;

    float m_CameraSpeed = 2.5f;
    float m_FOV = 55.0f;
    float m_zNear = 0.1f;
    float m_zFar = 100.0f;

    void Update();
    void processMouseMovement(float xoffset, float yoffset);


    vec3 getCameraFront();
    vec3 getCameraUp();

    void setCameraFront(vec3 in);
    void setCameraUp(vec3 in);
    void setAspect(float ratio);
};


#endif //RENDERTEST_CAMERA_H
