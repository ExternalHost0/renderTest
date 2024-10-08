//
// Created by Hayden Rivas on 7/13/24.
//
#include "Application.h"


Application::Application() = default;

Application& Application::get() {
    static Application instance;
    return instance;
}


Renderer renderer;

int Application::Init() {
    if(!glfwInit()) {
        std::cout << "GLFW FAILED TO BE INITIALIZED" << std::endl;
        return -1;
    }
    // builds m_Window with certain gl rules
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    std::cout << "APPLE DEVICE -> FORWARD COMPAT : TRUE" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    // make m_Window and check for success
    m_Window = glfwCreateWindow(mode->width, 600, "EVH Editor", nullptr, nullptr);

    if (m_Window == nullptr) {
        std::cout << "Failed to create GLFW m_Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_Window);


    // must be Init after making context current
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW FAILED TO BE INITIALIZED" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(this->m_Window, on_framebuffer_resize_callback);
    // init static modules of the editor
    GUI::Init();
    Input::Init();
    // end of main initilization by app
    // begin loading scene and required data to present
    // for now just autoload the same scene
//    m_CurrentScene.MakePrimaryCamera(new Camera);

//    m_CurrentScene.GetComponentManager().AddComponent<MeshComponent>(entity);

//    SystemManager.RegisterComponent(TransformComponent);

    // init dynamic modules required by scene
    renderer.Init();
    program = glCreateProgram();
    renderer.GenerateShaders(program);

    return 0;
}

void Application::Loop() {
    while(!glfwWindowShouldClose(this->m_Window)) {
        CalculateDelta();
        GUI::Update();
        renderer.GenerateFrameBufferNoMSAA(); // so idk why but this needs to go here to prevent error
        renderer.BindFrameBuffer(); // do not touch
        //     ----     //


        renderer.PreDraw();
        m_CurrentScene.Update();
        renderer.Draw();


        //     ----     //
        renderer.UnbindFrameBuffer(); // do not touch
        // update inputs for next frame to render
        Input::checkAllInput();
        // required glfw functions before finish
        glfwPollEvents();
        glfwSwapBuffers(this->m_Window);
    }
}

// SETTERS AND GETTERS
void Application::SetWindowTitle(const std::string& title) {
    glfwSetWindowTitle(m_Window, title.c_str());
}

GLFWwindow* Application::getWindow() { return m_Window; }
Renderer& Application::getRenderer() { return renderer; }

float Application::getDeltaTime() const { return m_DeltaTime; }
unsigned int Application::getProgram() const { return program; }


Scene& Application::GetCurrentScene() { return m_CurrentScene; }
void Application::SetCurrentScene(const Scene& newScene) { m_CurrentScene = newScene; }


// DELTA TIME FUNCTIONALITY
float lastFrame = 0.0f; // Time of last frame
void Application::CalculateDelta() {
    auto currentFrame = (float) glfwGetTime();
    m_DeltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

// QUIT FUNCTIONALITY
void Application::PreQuit() const {
    glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}
void Application::FullQuit() const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glDeleteProgram(program);
    glfwDestroyWindow(this->m_Window);
    glfwTerminate();
}


void Application::StateUpdate() {
    glPolygonMode(GL_FRONT_AND_BACK, isWireframe ? GL_LINE : GL_FILL);
    glfwSetInputMode(m_Window, GLFW_CURSOR, isCursorVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

// RESIZE EVENTS idk the difference
void Application::on_framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    Application::get().m_WindowSize = {width, height};
}
