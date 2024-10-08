//
// Created by Hayden Rivas on 7/14/24.
//
#include "../Application.h"
#include "Input.h"

Input::Input() {
    std::cout << "Init Input, you shouldnt be getting this message.";
}

float lastX = (float) Application::get().m_WindowSize.x / 2.0f;
float lastY = (float) Application::get().m_WindowSize.y / 2.0f;
bool firstMouse = true;

void Input::onMouseMove(GLFWwindow* window, double xposIn, double yposIn) {
    ImGui_ImplGlfw_CursorPosCallback(window, xposIn, yposIn);

    Application& app = Application::get();
    if (app.isCursorVisible){
        firstMouse=true;
        return;
    }

    Camera& camera = app.GetCurrentScene().GetPrimaryCamera();

    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);

    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    xoffset *= MOUSE_SENSITIVITY;
    yoffset *= MOUSE_SENSITIVITY;


    camera.processMouseMovement(xoffset, yoffset);

}

void Input::onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    Application& app = Application::get();

    if (key == GLFW_KEY_SLASH && action == GLFW_PRESS) app.isWireframe = !app.isWireframe;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) app.PreQuit();
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        app.isCursorVisible = !app.isCursorVisible;
        app.isInViewport = !app.isInViewport;
        if (app.isInViewport) {
            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
        } else {
            ImGui::GetIO().ConfigFlags -= ImGuiConfigFlags_NoMouse;
        }
    }

}



void Input::CheckCameraInput() {
    Application& app = Application::get();
    if (!app.isInViewport) return;
    GLFWwindow* window = app.getWindow();
    Camera& camera = app.GetCurrentScene().GetPrimaryCamera();

    // adjusted speed accounts for m_DeltaTime (frame difference)
    float adjustedSpeed = camera.m_CameraSpeed * app.getDeltaTime();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.m_Position = camera.m_Position + adjustedSpeed * camera.getCameraFront();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.m_Position = camera.m_Position - adjustedSpeed * camera.getCameraFront();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.m_Position = camera.m_Position - glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp())) * adjustedSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.m_Position = camera.m_Position + glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp())) * adjustedSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.m_Position = camera.m_Position + adjustedSpeed * camera.getCameraUp();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.m_Position = camera.m_Position - adjustedSpeed * camera.getCameraUp();
}

void Input::Init() {
    Application& app = Application::get();
    GLFWwindow* window = app.getWindow();

    // define input callback functions
    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetKeyCallback(window, onKeyAction);
}

void Input::checkAllInput() {
    CheckCameraInput();
    Application& app = Application::get();
    app.StateUpdate();
}
