//
// Created by Hayden Rivas on 7/12/24.
//

#include "Camera.h"
#include "../../Application.h"

vec3 Camera::getCameraFront() { return cameraFront; }
vec3 Camera::getCameraUp() { return cameraUp; }

void Camera::setCameraFront(vec3 in) { cameraFront = in; }
void Camera::setCameraUp(vec3 in) { cameraUp = in; }

void Camera::Update() {
    Application& app = Application::get();
    unsigned int program = app.getProgram();

    auto model = glm::mat4(1.0f);
    auto view = glm::mat4(1.0f);
    auto proj = glm::mat4(1.0f);

//    model = glm::rotate(model, (float) glfwGetTime() * glm::radians(50.0f), vec3(0.0f, 1.0f, 0.0f));
//    model = glm::translate(model, vec3(0.0f, sin((float) glfwGetTime() * 2.0f), 0.0f));
//    view = glm::translate(view, m_Position);

    proj = glm::perspective(glm::radians(m_FOV), aspectRatio, m_zNear, m_zFar);
    view = glm::lookAt(m_Position, m_Position + cameraFront, cameraUp);

    int modelLoc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(program, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::setAspect(float ratio) {
    aspectRatio = ratio;
}

