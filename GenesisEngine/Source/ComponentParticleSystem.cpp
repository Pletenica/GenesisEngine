#include "ComponentParticleSystem.h"
#include "glew/include/glew.h"
#include "ImGui/imgui.h"
#include "Application.h"
#include "WindowParticles.h"

ComponentParticleSystem::ComponentParticleSystem()
{
	type = ComponentType::PARTICLE;
}

ComponentParticleSystem::ComponentParticleSystem(GameObject* gameObject) : Component(gameObject)
{
	_gameObject = gameObject;
	type = ComponentType::PARTICLE;
}

ComponentParticleSystem::~ComponentParticleSystem()
{
}

void ComponentParticleSystem::Update(float dt)
{
	emitter.UpdateEmitter(dt);
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
		
		if (ImGui::Checkbox("Show Configuration Window", &App->editor->windows[PARTICLES_EDITOR_WINDOW]->visible)) {
			WindowParticles* w_part = (WindowParticles*)App->editor->windows[PARTICLES_EDITOR_WINDOW];
			w_part->UpdateEmitterInWindow(emitter);
		}

		if (ImGui::Button("Save Emitter", ImVec2(150, 20))) {
			std::string _path = "Library/Particles/Emitters/" + emitter._emitterConfig.emitterName + ".emittersettings";
			SaveEmitterSettings(_path.c_str());
		}
		ImGui::SameLine();
		if (ImGui::Button("Load Emitter", ImVec2(150, 20))) {

		}

		if (ImGui::Button("Save Particles", ImVec2(150, 20))) {
			std::string _path = "Library/Particles/Base Particles/" + emitter._emitterConfig.emitterName + ".particlesettings";
			SaveEmitterSettings(_path.c_str());
		}
		ImGui::SameLine();
		if (ImGui::Button("Load Particles", ImVec2(150, 20))) {

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

void ComponentParticleSystem::SaveEmitterSettings(const char* _path)
{

}

void ComponentParticleSystem::LoadEmitterSettings(const char* _path)
{

}

void ComponentParticleSystem::SaveParticleSettings(const char* _path)
{

}

void ComponentParticleSystem::LoadParticleSettings(const char* _path)
{

}
