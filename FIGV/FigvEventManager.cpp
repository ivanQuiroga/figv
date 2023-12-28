//
// Created by fconde on 5/10/23.
//

#include "FigvEventManager.h"
#include "imgui.h"
#include "FigvScene.h"

FigvEventManager* FigvEventManager::instance = NULL;

FigvEventManager::FigvEventManager() = default;

FigvEventManager* FigvEventManager::getInstance() {

    if (!instance) { instance = new FigvEventManager(); }
    return instance;
}

void FigvEventManager::processMouseClics(GLFWwindow* window, int button, int action, int mods) {

    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action);

    if (!io.WantCaptureMouse) {
        if ((button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_PRESS)) {
            glfwGetCursorPos(window, &lastX, &lastY);
            dragging = true;
        } else if ((button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_RELEASE)) {
            dragging = false;
        }
    }
}

void FigvEventManager::processMouseScroll(double yDisplacement) {

    FigvScene::dollyCamera(float(yDisplacement));
}

void FigvEventManager::processCursorPosition(double xPos, double yPos) {

    if (dragging) {
        double xOffset = lastX - xPos;
        double yOffset = lastY - yPos;

        lastX = xPos;
        lastY = yPos;

        FigvScene::orbitCamera(float(-xOffset), float(-yOffset));
    }
}
