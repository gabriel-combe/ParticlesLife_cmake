#include "ParticleEditor.h"

void ParticleEditor::show() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar;

	ImGui::Begin("Particle Editor", NULL, windowFlags);

    // Create Menu Bar at the top of the Particle Editor
    if (ImGui::BeginMenuBar()) {

        if (ImGui::BeginMenu("Style")) {
            if (ImGui::MenuItem("Classic"))
                ImGui::StyleColorsClassic();

            if (ImGui::MenuItem("Dark"))
                ImGui::StyleColorsDark();

            if (ImGui::MenuItem("Light"))
                ImGui::StyleColorsLight();

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

ParticleEditor::ParticleEditor() {}

ParticleEditor::~ParticleEditor() {}

void ParticleEditor::ParticleEditorInitialize() {}

void ParticleEditor::ParticleEditorShow() { this->show(); }

void ParticleEditor::ParticleEditorShutdown() {}