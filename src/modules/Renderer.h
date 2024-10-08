//
// Created by Hayden Rivas on 7/16/24.
//


#include "../Structs.h"

#ifndef RENDERTEST_RENDERER_H
#define RENDERTEST_RENDERER_H

class Renderer {
private:
    Vec2GLsizei m_ViewportSize{};
    unsigned int m_FBO{}; // framebuffer object
    unsigned int m_IFBO{}; // intermediate framebuffer object
    unsigned int m_RBO{}; // renderbuffer object

    unsigned int m_VAO{}; // vertex array object
    unsigned int m_TexID{}; // texture id
    unsigned int m_TexID_Second{}; // texture id

    Vec4clampf m_clear_color = {0.25f, 0.25f, 0.25f, 1.0f};
    int m_MSAA_samples = 4;
    bool m_UseAntialiasing = false;

public:
    Renderer();
    void Init();
    void Draw();

    void GenerateShaders(unsigned int program);
    void BindVertexArray();

    unsigned int GetFramebufferTexture();

    void BindFrameBuffer() const;
    void UnbindFrameBuffer();
    void BindRenderBuffer() const;
    void UnbindRenderBuffer();

    Vec2GLsizei getViewportSize();
    void setViewportSize(Vec2GLsizei newViewportSize);


    void GenerateFrameBufferwithMSAA();
    void RescaleFrameBuffer();
    void DeleteAllBuffers();

    void PreDraw();

    void GenerateFrameBufferNoMSAA();
};


#endif //RENDERTEST_RENDERER_H
