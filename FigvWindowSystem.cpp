//
// Created by fconde on 4/10/23.
//

#include <glad/glad.h>
#include <iostream>
#include "FigvWindowSystem.h"
#include "FigvAuxiliaryFunctions.h"
#include "FigvScene.h"

FigvWindowSystem::FigvWindowSystem(int width, int height, const char* name) {

    FigvLog("FigvWindowSystem", __LINE__, "Initializing the window system");

    this->windowName = name;
    this->window = NULL;
    
    if (!glfwInit()) {
        FigvLog("FigvWindowSystem", __LINE__, "Error initializing GLFW");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
    if (window == nullptr) {
        FigvLog("FigvWindowSystem", __LINE__, "Failed to create GLFW window");
        glfwTerminate();
        exit(2);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        FigvLog("FigvWindowSystem", __LINE__, "Failed to initialize GLAD");
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(3);
    }
    
    FigvScene::setFrameSize(width, height);
}

FigvWindowSystem::~FigvWindowSystem() {

    FigvLog("FigvWindowSystem", __LINE__, "Destroying the window system");

    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* FigvWindowSystem::getAppWindow() {
    return window;
}

bool FigvWindowSystem::getWindowShouldClose() {
    return glfwWindowShouldClose(window);
}

void FigvWindowSystem::swapBuffers() {
    glfwSwapBuffers(window);
}
