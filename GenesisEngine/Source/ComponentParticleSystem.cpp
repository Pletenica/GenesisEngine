#include "ComponentParticleSystem.h"
#include "glew/include/glew.h"
#include "ImGui/imgui.h"
#include "Application.h"

ComponentParticleSystem::ComponentParticleSystem()
{
	type = ComponentType::PARTICLE;
	emitterName = "Emitter Name";
	particleName = "Particle Name";
}

ComponentParticleSystem::ComponentParticleSystem(GameObject* gameObject) : Component(gameObject)
{
	_gameObject = gameObject;
	emitterName = "Emitter Name";
	particleName = "Particle Name";

	particlesWindow = new WindowParticles();
	emiterWindow = new WindowEmitter();
}

ComponentParticleSystem::~ComponentParticleSystem()
{
}

void ComponentParticleSystem::Update()
{
}

void ComponentParticleSystem::Reset()
{
}

void ComponentParticleSystem::OnEditor()
{
	ImVec4 textColor = ImVec4(0.7f, 0, 1, 1);
	if (ImGui::CollapsingHeader("Particle System", ImGuiTreeNodeFlags_DefaultOpen)){
		ImGui::Indent();
		if (ImGui::Checkbox("Enabled", &enabled)) {}
		ImGui::SameLine();
		if (ImGui::Checkbox("Preview", &enabled)) {}

		if (ImGui::CollapsingHeader("Emitter Settings", nullptr)) {
			if (ImGui::Checkbox("Show Emitter Window", &App->editor->windows[EMITTER_EDITOR_WINDOW]->visible)) {}

			ImGui::TextColored(textColor, "Emitter Name: ");
			ImGui::SameLine();
			ImGui::Text(emitterName.c_str());

			if (ImGui::Button("Save Emitter", ImVec2(150, 20))) {

			}
			ImGui::SameLine();
			if (ImGui::Button("Load Emitter", ImVec2(150, 20))) {

			}
		}
		if (ImGui::CollapsingHeader("Particles Settings", nullptr)) {
			if (ImGui::Checkbox("Show Particles Window", &App->editor->windows[PARTICLES_EDITOR_WINDOW]->visible)) {}

			ImGui::TextColored(textColor, "Particles Name: ");
			ImGui::SameLine();
			ImGui::Text(particleName.c_str());

			if (ImGui::Button("Save Particles", ImVec2(150, 20))) {

			}
			ImGui::SameLine();
			if (ImGui::Button("Load Particles", ImVec2(150, 20))) {

			}
		}
		ImGui::Unindent();
	}
}

void ComponentParticleSystem::SetResourceUID(uint UID)
{
}

Resource* ComponentParticleSystem::GetResource(ResourceType type)
{
	return nullptr;
}
