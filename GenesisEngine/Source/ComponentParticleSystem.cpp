#include "ComponentParticleSystem.h"
#include "glew/include/glew.h"
#include "ImGui/imgui.h"
#include "Application.h"
#include "WindowParticles.h"
#include "GnJSON.h"
#include "FileSystem.h"

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
			std::string firstPart = "Library/Particles/Emitters/" + emitter._emitterConfig.emitterName + EMITTERSAVEEXTENSION;
			SaveEmitterSettings(firstPart.c_str());
		}
		ImGui::SameLine();
		if (ImGui::Button("Load Emitter", ImVec2(150, 20))) {
			std::string firstPart = "Library/Particles/Emitters/Default Emitter Name.emittersettings";
			LoadEmitterSettings(firstPart.c_str());
		}

		if (ImGui::Button("Save Particles", ImVec2(150, 20))) {
			std::string _path = "Library/Particles/Base Particles/" + emitter._particlesConfig.particlesName + PARTICLESAVEEXTENSION;
			SaveParticleSettings(_path.c_str());
		}
		ImGui::SameLine();
		if (ImGui::Button("Load Particles", ImVec2(150, 20))) {
			std::string firstPart = "Library/Particles/Emitters/Default Particle Name.particlessettings";
			LoadEmitterSettings(firstPart.c_str());
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
	bool ret = true;

	GnJSONObj save_file;

	GnJSONArray gameObjects = save_file.AddArray("Emitter Settings");

	//Aqui  guarda
	GnJSONObj _manager;

	_manager.AddString("Emitter Name", emitter._emitterConfig.emitterName.c_str());
	_manager.AddBool("Loop", emitter._emitterConfig.emitterLoop);
	_manager.AddBool("Show Emitter AABB", emitter._emitterConfig.showEmitterAABB);
	_manager.AddBool("Show Emitter Form", emitter._emitterConfig.showEmitterForm);

	_manager.AddInt("Emitter Form", (int)emitter._emitterConfig.emitterForm);
	_manager.AddInt("Particle Max Spawn", emitter._emitterConfig.particleMaxSpawn);
	_manager.AddFloat("Particle Min Speed", emitter._emitterConfig.particleMinSpeed);
	_manager.AddFloat("Particle Max Speed", emitter._emitterConfig.particleMaxSpeed);
	_manager.AddFloat("Time to init", emitter._emitterConfig.timeToInit);

	_manager.AddFloat("Particle Min Lifetime", emitter._emitterConfig.particlesMinLifetime);
	_manager.AddFloat("Particle Max Lifetime", emitter._emitterConfig.particlesMaxLifetime);
	_manager.AddFloat("Emitter Lifetime", emitter._emitterConfig.emitterMaxLifetime);

	_manager.AddFloat("Time Between Particles", emitter._emitterConfig.timeMaxBetweenParticles);

	gameObjects.AddObject(_manager);

	char* buffer = NULL;
	uint size = save_file.Save(&buffer);

	FileSystem::Save(_path, buffer, size);

	save_file.Release();
	RELEASE_ARRAY(buffer);
}

void ComponentParticleSystem::LoadEmitterSettings(const char* _path)
{
	char* buffer = nullptr;

	uint size = FileSystem::Load(_path, &buffer);
	GnJSONObj config(buffer);

	GnJSONArray emitterArray(config.GetArray("Emitter Settings"));
	GnJSONObj _manager(emitterArray.GetObjectAt(0));

	emitter._emitterConfig.emitterName = _manager.GetString("Emitter Name", "");
	emitter._emitterConfig.emitterLoop = _manager.GetBool("Loop");
	emitter._emitterConfig.showEmitterAABB = _manager.GetBool("Show Emitter AABB");
	emitter._emitterConfig.showEmitterForm = _manager.GetBool("Show Emitter Form");

	emitter._emitterConfig.emitterForm = (EmitterForm)_manager.GetInt("Emitter Form");
	emitter._emitterConfig.particleMaxSpawn = _manager.GetInt("Particle Max Spawn");
	emitter._emitterConfig.particleMinSpeed = _manager.GetFloat("Particle Min Speed");
	emitter._emitterConfig.particleMaxSpeed = _manager.GetFloat("Particle Max Speed");
	emitter._emitterConfig.timeToInit = _manager.GetFloat("Time to init");
	emitter._emitterConfig.particlesMinLifetime = _manager.GetFloat("Particle Min Lifetime");
	emitter._emitterConfig.particlesMaxLifetime = _manager.GetFloat("Particle Max Lifetime");
	emitter._emitterConfig.emitterMaxLifetime = _manager.GetFloat("Emitter Lifetime");
	emitter._emitterConfig.timeMaxBetweenParticles = _manager.GetFloat("Time Between Particles");

	_manager.Release();
	config.Release();
	RELEASE_ARRAY(buffer);
}

void ComponentParticleSystem::SaveParticleSettings(const char* _path)
{
	bool ret = true;

	GnJSONObj save_file;

	GnJSONArray gameObjects = save_file.AddArray("Particle Settings");

	//Aqui  guarda
	GnJSONObj _manager;

	_manager.AddString("Particles Name", emitter._particlesConfig.particlesName.c_str());
	_manager.AddInt("Animation Columns", emitter._particlesConfig.animationColumns);
	_manager.AddInt("Animation Rows", emitter._particlesConfig.animationRows);

	_manager.AddFloat4("Init State Color", emitter._particlesConfig.initStateColor);
	_manager.AddFloat4("Final State Color", emitter._particlesConfig.finalStateColor);

	//_manager.AddInt("Texture ID", emitter._particlesConfig._texture->GetID());
	//_manager.AddInt("Texture Gpu ID", emitter._particlesConfig._texture->GetGpuID());
	//_manager.AddInt("Texture Height", emitter._particlesConfig._texture->GetHeight());
	//_manager.AddInt("Texture Weight", emitter._particlesConfig._texture->GeWidth());

	_manager.AddFloat("Min Init Size Particle", emitter._particlesConfig.minInitSize);
	_manager.AddFloat("Max Init Size Particle", emitter._particlesConfig.maxInitSize);
	_manager.AddFloat("Min Final Size Particle", emitter._particlesConfig.minFinalSize);
	_manager.AddFloat("Max Final Size Particle", emitter._particlesConfig.maxFinalSize);

	gameObjects.AddObject(_manager);

	char* buffer = NULL;
	uint size = save_file.Save(&buffer);

	FileSystem::Save(_path, buffer, size);

	save_file.Release();
	RELEASE_ARRAY(buffer);
}

void ComponentParticleSystem::LoadParticleSettings(const char* _path)
{
	char* buffer = nullptr;

	uint size = FileSystem::Load(_path, &buffer);
	GnJSONObj config(buffer);

	GnJSONArray emitterArray(config.GetArray("Emitter Settings"));
	GnJSONObj _manager(emitterArray.GetObjectAt(0));

	emitter._particlesConfig.particlesName = _manager.GetString("Emitter Name", "");
	emitter._particlesConfig.animationColumns = _manager.GetInt("Animation Columns");
	emitter._particlesConfig.animationRows = _manager.GetInt("Animation Rows");

	emitter._particlesConfig.initStateColor = _manager.GetFloat4("Init State Color");
	emitter._particlesConfig.finalStateColor = _manager.GetFloat4("Final State Color");

	emitter._particlesConfig.minInitSize = _manager.GetFloat("Min Init Size Particle");
	emitter._particlesConfig.maxInitSize = _manager.GetFloat("Max Init Size Particle");
	emitter._particlesConfig.minFinalSize = _manager.GetFloat("Min Final Size Particle");
	emitter._particlesConfig.maxFinalSize = _manager.GetFloat("Max Final Size Particle");

	_manager.Release();
	config.Release();
	RELEASE_ARRAY(buffer);
}
