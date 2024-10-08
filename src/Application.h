//
// Created by Hayden Rivas on 7/13/24.
//

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <list>
#include <vector>

#include "modules/GUI.h"
#include "modules/Input.h"
#include "modules/Renderer.h"
#include "modules/Util.h"

#include "components/subcomponents/TransformComponent.h"
#include "modules/Scene.h"

#include "prefabs/Primitives.h"

#ifndef RENDERTEST_APPLICATION_H
#define RENDERTEST_APPLICATION_H

class Application {
private:
  Application();
  GLFWwindow *m_Window{};

  float m_DeltaTime = 0.0f; // Time between current frame and last frame
  Scene m_CurrentScene;
  unsigned int program{};

public:
  vec2 m_WindowSize{1300, 800};

  bool isWireframe = false;
  bool isCursorVisible = true;
  bool isInViewport = false;

  Application(const Application &) = delete;
  static Application &get();

  int Init();
  void Loop();
  // ALWAYS call prequit when wanting to exit, NEVER call fullquit
  void PreQuit() const;
  void FullQuit() const;

  static void on_framebuffer_resize_callback(GLFWwindow *window, int width,
                                             int height);

  GLFWwindow *getWindow();
  Renderer &getRenderer();
  unsigned int getProgram() const;

  void CalculateDelta();
  float getDeltaTime() const;

  void StateUpdate();
  void SetWindowTitle(const std::string &title);

  void SetCurrentScene(const Scene &newScene);
  Scene &GetCurrentScene();
};

#endif // RENDERTEST_APPLICATION_H
