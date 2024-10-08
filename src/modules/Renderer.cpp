//
// Created by Hayden Rivas on 7/16/24.
//

#include "Renderer.h"
#include "../Application.h"

Renderer::Renderer() = default;

void Renderer::Init() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    // binding vertex array required for core profile of OpenGL
    BindVertexArray();
}

// clear and set clear color
void Renderer::PreDraw() {
    Application& app = Application::get();

    // sizing requirements for the renderer's scene window
    app.getRenderer().RescaleFrameBuffer();
    glViewport(0, 0, m_ViewportSize.x, m_ViewportSize.y);
    // glClear must go after glViewport, or else artifacts on changes of m_ViewportSize will occur
    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT); // clears the m_Window with the given glClearColor
}


void Renderer::Draw() {
    Application& app = Application::get();
    unsigned int program = app.getProgram();

    int fragColorLoc = glGetUniformLocation(program, "ourColor");
    auto time = (float) glfwGetTime();
    float newColor = sin(time) / 0.5f;
    glUniform4f(fragColorLoc, newColor/2, newColor, 0.0f, 1.0f);

    // the only important part here is this draw command

    glDrawElements(GL_TRIANGLES, (6*6), GL_UNSIGNED_INT, nullptr);


    app.GetCurrentScene().GetPrimaryCamera().setAspect((float) m_ViewportSize.x / (float) m_ViewportSize.y);

//    if (m_UseAntialiasing) {
//        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FBO);
//        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_IFBO);
//        glBlitFramebuffer(0, 0, m_ViewportSize.x, m_ViewportSize.y, 0, 0, m_ViewportSize.x, m_ViewportSize.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
//    }

}

// Vertex Array Controls
void Renderer::BindVertexArray() {
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
}

void Renderer::GenerateShaders(unsigned int program) {
    // buffer for verts
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Primitives::cubeVerts), Primitives::cubeVerts, GL_STATIC_DRAW);

    // buffer for elements
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Primitives::cubeIndicies), Primitives::cubeIndicies, GL_STATIC_DRAW);

    // position, controls how vertices are read
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, nullptr);


    // read and set theses two shaders
    unsigned int vs = Util::compileShader(GL_VERTEX_SHADER, "vertex.glsl");
    unsigned int fs = Util::compileShader(GL_FRAGMENT_SHADER, "fragment.glsl");

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glUseProgram(program);
}


void Renderer::GenerateFrameBufferwithMSAA() {
    // MSAA framebuffer
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    glGenTextures(1, &m_TexID);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_TexID);

    // create the texture & unbind
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_MSAA_samples, GL_RGB, m_ViewportSize.x, m_ViewportSize.y, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    // attach texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_TexID, 0);

    // Color Attachment framebuffer

    // render buffer attachment
    glGenRenderbuffers(1, &m_RBO);

    BindRenderBuffer();
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_MSAA_samples, GL_DEPTH24_STENCIL8, m_ViewportSize.x, m_ViewportSize.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
    UnbindRenderBuffer();

    // simple error checking
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete! (MSAA)" << std::endl;
    UnbindFrameBuffer();


    // secondary framebuffer
    glGenFramebuffers(1, &m_IFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_IFBO);

    // create a color attachment texture
    glGenTextures(1, &m_TexID_Second);
    glBindTexture(GL_TEXTURE_2D, m_TexID_Second);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ViewportSize.x, m_ViewportSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE,nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexID_Second, 0);    // we only need a color buffer


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete! (MSAA)" << std::endl;
    UnbindFrameBuffer();
}


void Renderer::GenerateFrameBufferNoMSAA() {
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    glGenTextures(1, &m_TexID);
    glBindTexture(GL_TEXTURE_2D, m_TexID);

    // create the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ViewportSize.x, m_ViewportSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // attach texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexID, 0);

    glGenRenderbuffers(1, &m_RBO);

    BindRenderBuffer();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_ViewportSize.x, m_ViewportSize.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
    UnbindRenderBuffer();

    // simple error checking
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete! (No MSAA)" << std::endl;

    UnbindFrameBuffer();
}

void Renderer::RescaleFrameBuffer() {
    if (m_UseAntialiasing) {
        glBindTexture(GL_TEXTURE_2D, m_TexID_Second);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ViewportSize.x, m_ViewportSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE,nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexID_Second, 0);

        BindRenderBuffer();
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_ViewportSize.x, m_ViewportSize.y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
        UnbindRenderBuffer();
    } else {
        glBindTexture(GL_TEXTURE_2D, m_TexID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ViewportSize.x, m_ViewportSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE,nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexID, 0);

        BindRenderBuffer();
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_ViewportSize.x, m_ViewportSize.y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
        UnbindRenderBuffer();
    }

}

// returns the texture drawn from framebuffer
unsigned int Renderer::GetFramebufferTexture() {
    return m_UseAntialiasing ? m_TexID_Second : m_TexID;
}

// Frame Buffer Controls
void Renderer::BindFrameBuffer() const { glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); }
void Renderer::UnbindFrameBuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
// Render Buffer OCntrols
void Renderer::BindRenderBuffer() const { glBindRenderbuffer(GL_RENDERBUFFER, m_RBO); }
void Renderer::UnbindRenderBuffer() { glBindRenderbuffer(GL_RENDERBUFFER, 0); }


// Delete all data in buffers
void Renderer::DeleteAllBuffers() {
    if (m_FBO) {
        glDeleteFramebuffers(1, &m_FBO);
        glDeleteTextures(1, &m_TexID);
        m_TexID = 0;

    } else {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer does not exist!" << std::endl;
    }
}

// viewport size getter and setter
Vec2GLsizei Renderer::getViewportSize() { return m_ViewportSize; }
void Renderer::setViewportSize(Vec2GLsizei newViewportSize) { m_ViewportSize = newViewportSize; }




