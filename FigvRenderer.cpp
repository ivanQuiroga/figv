//
// Created by fconde on 4/10/23.
//

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "FigvRenderer.h"
#include "FigvAuxiliaryFunctions.h"
#include "FigvScene.h"

FigvRenderer* FigvRenderer::instance = NULL;

FigvRenderer::FigvRenderer() {
    
    FigvLog("FigvRenderer", __LINE__, "Initializing the renderer");
    
    background = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);

    shader = new FigvShader("./shaders/FigvADSVertex.glsl",
                            "./shaders/FigvADSFragment.glsl");
}

FigvRenderer::~FigvRenderer() {}

FigvRenderer *FigvRenderer::getInstance() {
    // - Se usa lazy initialization. Sólo se inicializa cuando se necesita.
    if (!instance) { instance = new FigvRenderer(); }
    return instance;
}

float* FigvRenderer::getBackgroundColor() {
    return glm::value_ptr(background);
}

void FigvRenderer::renderScene() {
    instance->render();
}

void FigvRenderer::render() {

    glClearColor(background[0], background[1], background[2], background[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_MULTISAMPLE);
    
    FigvScene::drawScene(*shader);
}
