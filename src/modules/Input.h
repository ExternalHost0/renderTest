//
// Created by Hayden Rivas on 7/14/24.
//
#include <GLFW/glfw3.h>
#include "glm.hpp"

#ifndef RENDERTEST_INPUT_H
#define RENDERTEST_INPUT_H


class Input {
private:
    Input();
    constexpr static float MOUSE_SENSITIVITY = 0.1f;
public:
    Input(const Input&) = delete;
    static void onMouseMove(GLFWwindow* window, double xpos, double ypos);
    static void CheckCameraInput();
    static void onKeyAction(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void Init();

    static void checkAllInput();
};


#endif //RENDERTEST_INPUT_H
