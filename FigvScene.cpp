//
// Created by fconde on 4/10/23.
//

#include "FigvScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "FigvAuxiliaryFunctions.h"

FigvScene* FigvScene::instance = nullptr;

FigvScene::FigvScene() {
    
    FigvLog("FigvScene", __LINE__, "Initializing the scene");
    
    camera = new FigvCamera();
    models = std::vector<FigvModel>();
    
    models.push_back(FigvModel("./spot/spot_triangulated.obj"));
    models.push_back(FigvModel("./bob/bob_tri.obj"));
    models.push_back(FigvModel("./blub/blub_triangulated.obj"));
}

FigvScene::~FigvScene() = default;

FigvScene *FigvScene::getInstance() {
    // - Se usa lazy initialization. Sólo se construye cuando se necesita.
    if (!instance) { instance = new FigvScene(); }
    return instance;
}

void FigvScene::orbitCamera(float movementX, float movementY) {

    FigvScene::getInstance()->camera->orbit(movementX, movementY);
}

void FigvScene::dollyCamera(float distance) {

    FigvScene::getInstance()->camera->dolly(distance);
}

void FigvScene::trackCamera(float rightOffset, float upOffset) {

    FigvScene::getInstance()->camera->track(rightOffset, upOffset);
}

void FigvScene::zoomCamera(float deltaFovX) {
    FigvScene::getInstance()->camera->zoom(deltaFovX);
}

void FigvScene::drawScene(FigvShader shader) {

    shader.use();
    glm::mat4 viewProj = instance->camera->getViewProjectionMatrix();
    shader.setMat4("mViewProjection", viewProj);
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    shader.setMat4("mModel", modelMatrix);
    shader.setVec3f("Kd", instance->Kd);
    shader.setVec3f("Ks", instance->Ks);
    shader.setFloat("shininess", instance->shininess);
    shader.setVec3f("Ia", instance->Ia);
    shader.setVec3f("Id", instance->Id);
    shader.setVec3f("Is", instance->Is);
    glm::vec4 lightPos = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
    shader.setVec3f("lightPosition", instance->camera->getPosition());
    shader.setVec3f("cameraPosition", instance->camera->getPosition());
    FigvScene::getInstance()->models[instance->modelActive].draw();
}

void FigvScene::setFrameSize(int width, int height) {

    FigvScene::getInstance()->camera->setAspect(width, height);
}

int* FigvScene::getModelActive() {
    return &modelActive;
}

float* FigvScene::getShininess() {
    return &shininess;
}

float* FigvScene::getKd() {
    return glm::value_ptr(Kd);
}

float* FigvScene::getKs() {
    return glm::value_ptr(Ks);
}

float* FigvScene::getIa() {
    return glm::value_ptr(Ia);
}

float* FigvScene::getId() {
    return glm::value_ptr(Id);
}

float* FigvScene::getIs() {
    return glm::value_ptr(Is);
}

