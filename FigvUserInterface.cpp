//
// Created by fconde on 4/10/23.
//

#include "FigvUserInterface.h"
#include "FigvAuxiliaryFunctions.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "FigvScene.h"
#include "FigvRenderer.h"
#include <filesystem>

FigvUserInterface::FigvUserInterface(GLFWwindow* associatedWindow) {
    
    FigvLog("FigvUserInterface", __LINE__, "Initializing the user interface");
    
    this->associatedWindow = associatedWindow;
    this->glsl_version = "#version 400";
    this->darkMode = true;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO&ioo = ImGui::GetIO();
    ioo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ioo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ioo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ioo.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ioo.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    if (darkMode) { ImGui::StyleColorsDark(); }
    else { ImGui::StyleColorsLight(); }

    ImGui_ImplGlfw_InitForOpenGL(associatedWindow, false);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

FigvUserInterface::~FigvUserInterface() {

    FigvLog("FigvUserInterface", __LINE__, "Destroying the user interface");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void FigvUserInterface::preRenderActions() {

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(associatedWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
}

void FigvUserInterface::afterRenderActions() {

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = associatedWindow; // glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void FigvUserInterface::prepareInterfaceObjects() {

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    preparePalettes();
}

void FigvUserInterface::preparePalettes() {

    //const char* items[] = { "Spot", "Bob", "Blub" };
    FigvUserInterface::updateModelNamesCStr();
    ImGui::Begin("Renderer properties");
    ImGui::ColorEdit3("Background", FigvRenderer::getInstance()->getBackgroundColor());
    ImGui::SeparatorText("Model");
    if (ImGui::Button("Import Model")) {
        ImGui::SetNextWindowSize(ImVec2(700, 400));
        ImGuiFileDialog::Instance()->OpenDialog("ChooseModelDlgKey", "Choose Model", ".obj", ".");
    }
    if (ImGuiFileDialog::Instance()->Display("ChooseModelDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string modelPath = ImGuiFileDialog::Instance()->GetFilePathName();
            FigvScene::getInstance()->importModel(modelPath);          
            std::filesystem::path filePath(modelPath);
            std::string modelName = filePath.stem().string();
            modelNames.push_back(modelName);
            *FigvScene::getInstance()->getModelActive() = static_cast<int>(modelNames.size()) - 1;
        }
        ImGuiFileDialog::Instance()->Close();
    }
    ImGui::Combo("Model", FigvScene::getInstance()->getModelActive(), modelNamesCStr.data(), modelNamesCStr.size());  
    ImGui::SeparatorText("Material");
    ImGui::ColorEdit3("Kd", FigvScene::getInstance()->getKd());
    ImGui::ColorEdit3("Ks", FigvScene::getInstance()->getKs());
    ImGui::InputFloat("Shininess", FigvScene::getInstance()->getShininess(), 1.0f, 10.0f, "%.1f");
    ImGui::SeparatorText("Light source");
    ImGui::ColorEdit3("Ia", FigvScene::getInstance()->getIa());
    ImGui::ColorEdit3("Id", FigvScene::getInstance()->getId());
    ImGui::ColorEdit3("Is", FigvScene::getInstance()->getIs()); 
    ImGui::End();
// Si se descomenta la siguiente línea, se construye una segunda paleta en la
// que se muestran todos los widgets que se pueden usar con ImGui. El código
// que construye esos widgets se encuentra en el archivo: imgui_demo.cpp
    
// ImGui::ShowDemoWindow();
}

void FigvUserInterface::updateModelNamesCStr() {
    modelNamesCStr.clear();
    for (const auto& name : modelNames) {
        modelNamesCStr.push_back(name.c_str());
    }
}