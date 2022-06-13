//
// Created by 王波 on 2022/6/13.
//

#include "advance_framebuffer_render.h"
constexpr float AdvanceFrameBufferRender::quadVertices[];

void AdvanceFrameBufferRender::onDraw() {
    //draw fbo
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClearColor(0.1f, 0.1f,0.1f,0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_ATTACHMENT0);
    glEnable(GL_DEPTH_TEST);

    AdvanceTextureRender::onDraw();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f,0.1f,0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_ATTACHMENT0);

    //draw texture
    screenShader->use();
    glBindVertexArray(QUAD_VAO);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void AdvanceFrameBufferRender::initShader() {
    AdvanceTextureRender::initShader();
    //init  custom shader
    QUAD_VAO = GLUtils::createVAO();
    QUAD_VBO = GLUtils::createBuffers();
    QUAD_RBO = GLUtils::createRBO();

    glBindVertexArray(QUAD_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, QUAD_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float ), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float ), (void *)(3 * sizeof (float )));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    screenShader = new Shader(vShaderPath, fShaderPath);
    screenShader->use();
    screenShader->setFloat("texture1", 0);
}

void AdvanceFrameBufferRender::onInit() {
    //create fbo
    FBO = GLUtils::createFrameBuffer();
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);


    //create texture
    texture1 = GLUtils::createTexture(width, height, GL_RGB);

    //attach to fbo
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture1, 0);


    //attach to rbo
    glBindRenderbuffer(GL_RENDERBUFFER, QUAD_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
//    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, QUAD_RBO); // now actually attach it

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    AdvanceTextureRender::onInit();
}
