#include "ComponentParticleSystem.h"
#include "glew/include/glew.h"
#include "ImGui/imgui.h"
#include "Application.h"
#include "WindowParticles.h"
#include "GnJSON.h"
#include "FileSystem.h"
#include <algorithm>
#include "GameObject.h"
#include "Transform.h"
#include "Time.h"

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
	float deltaTime = Time::gameClock.deltaTime();
	emitter.UpdateEmitter(deltaTime);
	Transform* _trans= (Transform*)_gameObject->GetComponent(ComponentType::TRANSFORM);
	if (_trans != nullptr) {
		emitter.SetEmitterTransform(_trans->GetLocalTransform());
	}
	
}

void ComponentParticleSystem::Reset()
{
}

void ComponentParticleSystem::OnEditor()
{
	ImVec4 textColor = ImVec4(0.7f, 0, 1, 1);
	if (ImGui::CollapsingHeader("Particle System", ImGuiTreeNodeFlags_DefaultOpen)){
		ImGui::Indent();
		ImGui::Text("Enabled");
		if (ImGui::Checkbox("##EnabledComponentParticleSystem", &enabled)) {}
		
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
			toLoadEmitter = true;
			openLoadWindow = true;
		}

		if (ImGui::Button("Save Particles", ImVec2(150, 20))) {
			std::string _path = "Library/Particles/Base Particles/" + emitter._particlesConfig.particlesName + PARTICLESAVEEXTENSION;
			SaveParticleSettings(_path.c_str());
		}
		ImGui::SameLine();
		if (ImGui::Button("Load Particles", ImVec2(150, 20))) {
			toLoadEmitter = false;
			openLoadWindow = true;
		}

		ImGui::Unindent();
	}

	if (openLoadWindow == true) {
		CreateWindowToLoad(toLoadEmitter);
	}
}

void ComponentParticleSystem::CreateWindowToLoad(bool _isEmitterSettings)
{
	const char* from_dir = "";
	if (_isEmitterSettings == true) {
		from_dir = "Library/Particles/Emitters/";
	}
	else {
		from_dir = "Library/Particles/Base Particles/";
	}

	selected_file[0] = '\0';

	ImGui::OpenPopup("Load File");

	if (ImGui::BeginPopupModal("Load File", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize))
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("File Browser", ImVec2(0, 180), true);
		DrawDirectoryRecursive(from_dir, _isEmitterSettings);
		ImGui::EndChild();
		ImGui::PopStyleVar();

		if (ImGui::Button("Cancel", ImVec2(50, 20)))
			openLoadWindow = false;

		ImGui::EndPopup();
	}
}

void ComponentParticleSystem::DrawDirectoryRecursive(const char* directory, bool _isEmitterSettings)
{
	std::vector<std::string> files;
	std::vector<std::string> dirs;
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;

	std::string dir((directory) ? directory : "");

	FileSystem::DiscoverFiles(dir.c_str(), files, dirs);

	for (std::vector<std::string>::const_iterator it = dirs.begin(); it != dirs.end(); ++it)
	{
		std::string folder = (dir + (*it)).c_str();

		if (ImGui::TreeNodeEx(folder.c_str(), flags, "%s/", (*it).c_str()))
		{
			flags = ImGuiTreeNodeFlags_None;

			DrawDirectoryRecursive((dir + (*it)).c_str(), _isEmitterSettings);
			ImGui::TreePop();
		}

		flags = ImGuiTreeNodeFlags_None;
	}

	std::sort(files.begin(), files.end());

	for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); ++it)
	{
		const std::string& str = *it;

		bool ok = true;

		flags = ImGuiTreeNodeFlags_Leaf;

		std::string complete_path = std::string(directory) + "/" + str;
		if (strcmp(selected_file, complete_path.c_str()) == 0)
			flags |= ImGuiTreeNodeFlags_Selected;


		if (_isEmitterSettings == true) {
			std::string lastExtension = "";
			lastExtension = complete_path.substr(complete_path.find_last_of("."));
			if (lastExtension != "") {
				if (lastExtension != ".emittersettings") ok = false;
			}
		}
		else if (_isEmitterSettings == false) {
			std::string lastExtension = "";
			lastExtension = complete_path.substr(complete_path.find_last_of("."));
			if (lastExtension != "") {
				if (lastExtension != ".particlessettings") ok = false;
			}
		}

		if (ok && ImGui::TreeNodeEx(str.c_str(), flags))
		{
			if (ImGui::IsItemClicked()) {
				sprintf_s(selected_file, 256, "%s/%s", dir.c_str(), str.c_str());

				if (ImGui::IsMouseDoubleClicked(0))
				{
					if (_isEmitterSettings == true) {
						LoadEmitterSettings(selected_file);
					}
					else {
						LoadParticleSettings(selected_file);
					}
					openLoadWindow = false;
				}
			}

			ImGui::TreePop();
		}
	}
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

	_manager.AddFloat("Emitter Cone Height", emitter.emitterBody._cone.height);
	_manager.AddFloat("Emitter Cone Circle Up Radius", emitter.emitterBody._cone.circleUp.r);
	_manager.AddFloat("Emitter Cone Circle Down Radius", emitter.emitterBody._cone.circleDown.r);

	_manager.AddFloat("Emitter Circle Radius", emitter.emitterBody._circle.r);

	_manager.AddFloat("Emitter Sphere Radius", emitter.emitterBody._sphere.r);

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

	emitter.emitterBody._cone.height = _manager.GetFloat("Emitter Cone Height");
	emitter.emitterBody._cone.circleUp.r = _manager.GetFloat("Emitter Cone Circle Up Radius");
	emitter.emitterBody._cone.circleDown.r = _manager.GetFloat("Emitter Cone Circle Down Radius");
	emitter.emitterBody._circle.r = _manager.GetFloat("Emitter Circle Radius");
	emitter.emitterBody._sphere.r = _manager.GetFloat("Emitter Sphere Radius");

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

	_manager.AddInt("Texture UID", emitter._particlesConfig._texture->GetUID());

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

	GnJSONArray emitterArray(config.GetArray("Particle Settings"));
	GnJSONObj _manager(emitterArray.GetObjectAt(0));

	emitter._particlesConfig.particlesName = _manager.GetString("Particles Name", "");
	emitter._particlesConfig.animationColumns = _manager.GetInt("Animation Columns");
	emitter._particlesConfig.animationRows = _manager.GetInt("Animation Rows");

	emitter._particlesConfig.initStateColor = _manager.GetFloat4("Init State Color");
	emitter._particlesConfig.finalStateColor = _manager.GetFloat4("Final State Color");

	emitter._particlesConfig.minInitSize = _manager.GetFloat("Min Init Size Particle");
	emitter._particlesConfig.maxInitSize = _manager.GetFloat("Max Init Size Particle");
	emitter._particlesConfig.minFinalSize = _manager.GetFloat("Min Final Size Particle");
	emitter._particlesConfig.maxFinalSize = _manager.GetFloat("Max Final Size Particle");

	emitter._particlesConfig._texture = dynamic_cast<ResourceTexture*>(App->resources->RequestResource(_manager.GetInt("Texture UID", 0)));

	_manager.Release();
	config.Release();
	RELEASE_ARRAY(buffer);
}
