#include "WindowParticles.h"
#include "Application.h"
#include "Editor.h"
#include <algorithm>
#include "FileSystem.h"
#include "ResourceTexture.h"

WindowParticles::WindowParticles()
{

}

WindowParticles::~WindowParticles()
{

}

void WindowParticles::Draw()
{
	if (visible == true) {
		ImVec2 windowSize = ImGui::GetWindowSize();
		float sizeUpChildsWidth = (windowSize.x-30) * 0.33f;
		float sizeUpChildsHeight = (windowSize.y-50) * 0.85f;
		float sizeDownChildsWidth = (windowSize.x-30) * 0.5f;
		float sizeDownChildsHeight = (windowSize.y-50) * 0.39f;

		/////////////// Particle Settings ///////////////
		ImGui::Begin("Particle Settings Window", (bool*)false, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);
		ImGui::Text("Particle Name: ");
		ImGui::SameLine();
		const char* bufParticleName = particlesConf->particlesName.c_str();
		if(ImGui::InputText("##particleName", (char*)bufParticleName, 64, ImGuiInputTextFlags_EnterReturnsTrue)) {
			particlesConf->particlesName = bufParticleName;
		}

		//Print First Module (Particle Animation Info)
		ImGui::BeginChild("Animation Particle", ImVec2(sizeUpChildsWidth, sizeUpChildsHeight), true, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking);
		DrawParticlesAnimationProperties();
		ImGui::EndChild();
		ImGui::SameLine();

		//Print Second Module (Particle Init State Info)
		ImGui::BeginChild("Particle Init State", ImVec2(sizeUpChildsWidth, sizeUpChildsHeight), true, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking);
		DrawParticlesInitStateProperties();
		ImGui::EndChild();
		ImGui::SameLine();

		//Print Third Module (Particle Final State Info)
		ImGui::BeginChild("Particle Final State", ImVec2(sizeUpChildsWidth, sizeUpChildsHeight), true, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking);
		DrawParticlesFinalStateProperties();
		ImGui::EndChild();

		/////////////// Emitter Settings ///////////////
		ImGui::Text("Emitter Name: ");
		ImGui::SameLine();
		const char* bufEmitterName = emitterConf->emitterName.c_str();
		if (ImGui::InputText("##emitterName", (char*)bufEmitterName, 64, ImGuiInputTextFlags_EnterReturnsTrue)) {
			emitterConf->emitterName = bufEmitterName;
		}

		//Print First Module (Emitter form info)
		ImGui::BeginChild("Emitter Form", ImVec2(sizeDownChildsWidth-170, sizeDownChildsHeight), true, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking);
		DrawEmitterFormSettings();
		ImGui::EndChild();
		ImGui::SameLine();

		//Print Seond Module (Emitter settings)
		ImGui::BeginChild("Emitter Settings", ImVec2(sizeDownChildsWidth+170, sizeDownChildsHeight), true, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking);
		DrawEmitterSettings();
		ImGui::EndChild();

		ImGui::End();


		if (openSelectionTex == true) {
			CreateWindowToSelectNewTexture();
		}
	}
}

void WindowParticles::DrawParticlesAnimationProperties()
{
	ImGui::TextColored(textColor, "PARTICLE TEXTURE");
	//Button to import another Particle Image
	if (ImGui::Button("Import Texture", ImVec2(130, 30))) {
		openSelectionTex = true;
	}

	//Draw Image
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 canvasPosition = ImGui::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
	ImVec2 contentRegion = ImGui::GetContentRegionAvail();
	float textureWeight = 250.0f;
	float textureHeight = 250.0f;
	float textureScale = 1.0f;
	if (particlesConf->textureWeight > 0.0f && particlesConf->textureHeight > 0.0f)
	{
		textureScale = contentRegion.x / particlesConf->textureWeight;
		textureWeight = contentRegion.x;
		textureHeight = particlesConf->textureHeight * textureScale;
	}
	if (particlesConf->_texture != nullptr) {
		ImGui::Image((ImTextureID)particlesConf->_texture->GetGpuID(), ImVec2(textureWeight, textureHeight));
	}
	else {
		ImGui::Image(0, ImVec2(textureWeight, textureHeight));
	}

	//Print Column and Row Lines
	ImVec2 canvas_size = ImVec2(textureWeight, textureHeight);
	for (int i = 1; i < particlesConf->animationColumns; i++)
		draw_list->AddLine(ImVec2(canvasPosition.x + (canvas_size.x / particlesConf->animationColumns) * i, canvasPosition.y), ImVec2(canvasPosition.x + (canvas_size.x / particlesConf->animationColumns) * i, canvasPosition.y + canvas_size.y), IM_COL32(150, 150, 255, 255));
	for (int i = 1; i < particlesConf->animationRows; i++)
		draw_list->AddLine(ImVec2(canvasPosition.x, canvasPosition.y + (canvas_size.y / particlesConf->animationRows) * i), ImVec2(canvasPosition.x + canvas_size.x, canvasPosition.y + (canvas_size.y / particlesConf->animationRows) * i), IM_COL32(150, 150, 255, 255));

	//Columns and Rows Info
	ImGui::PushItemWidth(95);
	if (ImGui::SliderInt("Columns", &particlesConf->animationColumns, 1, 10))
	{

	}
	if (ImGui::SliderInt("Rows", &particlesConf->animationRows, 1, 10))
	{

	}
	ImGui::PopItemWidth();

	ImGui::TextColored(textColor, "Total frames: ");
	ImGui::SameLine();
	ImGui::Text("%i", particlesConf->animationColumns * particlesConf->animationRows);
}

void WindowParticles::DrawParticlesInitStateProperties()
{
	ImGui::TextColored(textColor, "INITIAL STATE");
	ImGuiColorEditFlags flags = ImGuiColorEditFlags_AlphaBar;
	ImGui::ColorPicker4("Color##InitColor", (float*)&particlesConf->initStateColor, flags);

	ImGui::Separator();

	ImGui::TextColored(textColor, "Min Size Particle");
	ImGui::SameLine();
	ImGui::PushItemWidth(80);
	ImGui::DragFloat("##particleMinSizeInit", &particlesConf->minInitSize, 0.001f, 0.0f, 100.0f);
	ImGui::PopItemWidth();

	ImGui::TextColored(textColor, "Max Size Particle");
	ImGui::SameLine();
	ImGui::PushItemWidth(80);
	ImGui::DragFloat("##particleMaxSizeInit", &particlesConf->maxInitSize, 0.001f, 0.0f, 100.0f);
	ImGui::PopItemWidth();
}

void WindowParticles::DrawParticlesFinalStateProperties()
{
	ImGui::TextColored(textColor, "FINAL STATE");
	ImGuiColorEditFlags flags = ImGuiColorEditFlags_AlphaBar;
	ImGui::ColorPicker4("Color##FinalColor", (float*)&particlesConf->finalStateColor, flags);

	ImGui::Separator();

	ImGui::TextColored(textColor, "Min Size Particle");
	ImGui::SameLine();
	ImGui::PushItemWidth(80);
	ImGui::DragFloat("##particleMinSizeFinal", &particlesConf->minFinalSize, 0.001f, 0.0f, 100.0f);
	ImGui::PopItemWidth();

	ImGui::TextColored(textColor, "Max Size Particle");
	ImGui::SameLine();
	ImGui::PushItemWidth(80);
	ImGui::DragFloat("##particleMaxSizeFinal", &particlesConf->maxFinalSize, 0.001f, 0.0f, 100.0f);
	ImGui::PopItemWidth();
}

void WindowParticles::DrawEmitterFormSettings()
{
	ImGui::TextColored(textColor, "Emitter Form: ");
	ImGui::PushItemWidth(100);
	if (ImGui::Combo("##EmitterFormCombo", (int*)&emitterConf->emitterForm, "Sphere\0SemiSphere\0Cone\0Circle")) {
		particleEmitter->ResetEmitterShape();
	}
	ImGui::PopItemWidth();
	
	switch (emitterConf->emitterForm)
	{
	case(EmitterForm::EMITTER_FORM_CONE):
		ImGui::PushItemWidth(100);
		ImGui::DragFloat("Aperture Radius", (float*)&particleEmitter->emitterBody._cone.circleUp.r, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Base Radius", (float*)&particleEmitter->emitterBody._cone.circleDown.r, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Cone Heigth", (float*)&particleEmitter->emitterBody._cone.height, 0.1f, 0.0f, 100.0f);
		ImGui::PopItemWidth();
		break;
	case(EmitterForm::EMITTER_FORM_SEMISPHERE):
		ImGui::PushItemWidth(100);
		ImGui::DragFloat("SemiSphere Radius", (float*)&particleEmitter->emitterBody._sphere.r, 0.1f, 0.0f, 100.0f);
		ImGui::PopItemWidth();
		break;
	case(EmitterForm::EMITTER_FORM_SPHERE):
		ImGui::PushItemWidth(100);
		ImGui::DragFloat("Sphere Radius", (float*)&particleEmitter->emitterBody._sphere.r, 0.1f, 0.0f, 100.0f);
		ImGui::PopItemWidth();
		break;
	case(EmitterForm::EMITTTER_FORM_CIRCLE):
		ImGui::PushItemWidth(100);
		ImGui::DragFloat("Circle Radius", (float*)&particleEmitter->emitterBody._circle.r, 0.1f, 0.0f, 100.0f);
		ImGui::PopItemWidth();
		break;
	}
}

void WindowParticles::DrawEmitterSettings()
{
	ImGui::Columns(2, "##emittereditorcolumn", false);
	//Emitter Loop Setting
	ImGui::TextColored(textColor, "Loop: ");
	ImGui::SameLine();
	ImGui::Checkbox("##EmmitterLoopBool", &emitterConf->emitterLoop);
	ImGui::PushItemWidth(70);

	ImGui::Text("Emitter Seconds to Init: ");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##EmitterSecondstoInit", &emitterConf->timeToInit, 0, 50))
	{

	}


	//Emitter Duration
	if (emitterConf->emitterLoop == false) {
		ImGui::Text("Emitter Duration: ");
		ImGui::TextColored(textColor, "Max:");
		ImGui::SameLine();
		if (ImGui::SliderFloat("##EmitterMaxDuration", &emitterConf->emitterMaxLifetime, 1, 50))
		{

		}
		ImGui::SameLine();
		ImGui::TextColored(textColor, "Actual:");
		ImGui::SameLine();
		ImGui::Text("%f", particleEmitter->emitterActualLifetime);
	}

	ImGui::TextColored(textColor, "---------------------");

	//Emitter Particle Time Between then
	ImGui::Text("Seconds between particles: ");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##ParticlesPerSecondEmitter", &emitterConf->timeMaxBetweenParticles, 1, 10))
	{

	}

	ImGui::TextColored(textColor, "---------------------");

	//Emitter Particle Lifetimes
	ImGui::Text("Particle Lifetime:");
	ImGui::TextColored(textColor, "Min:");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##ParticlesMinDuration", &emitterConf->particlesMinLifetime, 0, 50))
	{

	}
	ImGui::SameLine();
	ImGui::TextColored(textColor, "Max:");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##ParticlesMaxDuration", &emitterConf->particlesMaxLifetime, 1, 50))
	{

	}


	ImGui::PopItemWidth();
	ImGui::NextColumn();
	ImGui::PushItemWidth(70);

	ImGui::Text("Show Emitter AABB: ");
	ImGui::SameLine();
	ImGui::Checkbox("##EmmitterAABBBool", &emitterConf->showEmitterAABB);

	ImGui::Text("Show Emitter Form: ");
	ImGui::SameLine();
	ImGui::Checkbox("##EmmitterShowFormBool", &emitterConf->showEmitterForm);

	ImGui::TextColored(textColor, "---------------------");

	//Num particles in emitter
	ImGui::Text("Emitter Max Particles:");
	ImGui::SameLine();
	if (ImGui::SliderInt("##ParticlesMaxSpawnEmitter", &emitterConf->particleMaxSpawn, 1, 200))
	{

	}
	ImGui::TextColored(textColor, "Actual particles count:");
	ImGui::SameLine();
	ImGui::Text("%i", particleEmitter->particles.size());

	ImGui::TextColored(textColor, "---------------------");

	//Speed Particles
	ImGui::Text("Spawn Speed Particles:");
	ImGui::TextColored(textColor, "Min:");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##MinSpawnSpeedParticles", &emitterConf->particleMaxSpeed, 0, 200))
	{

	}
	ImGui::SameLine();
	ImGui::TextColored(textColor, "Max:");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##MaxSpawnSpeedParticles", &emitterConf->particleMinSpeed, 0, 200))
	{

	}

	ImGui::PopItemWidth();
}

void WindowParticles::UpdateEmitterInWindow(ParticlesEmitter& _emitter)
{
	emitterConf = &_emitter._emitterConfig;
	particlesConf = &_emitter._particlesConfig;
	particleEmitter = &_emitter;
}

void WindowParticles::CreateWindowToSelectNewTexture()
{
	const char* filter_extension = ".dds";
	const char* from_dir = "Library/";
	selected_file[0] = '\0';
	selected_folder[0] = '\0';

	ImGui::OpenPopup("Load File");
	if (ImGui::BeginPopupModal("Load File", nullptr))
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("File Browser", ImVec2(0, 300), true);
		DrawDirectoryRecursive(from_dir, filter_extension);
		ImGui::EndChild();
		ImGui::PopStyleVar();

		if (ImGui::Button("Ok", ImVec2(50, 20))) {
			particlesConf->_texture = dynamic_cast<ResourceTexture*>(App->resources->RequestResource(App->resources->Find(selected_file)));
			openSelectionTex = false;
		}
		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(50, 20)))
			openSelectionTex = false;

		ImGui::EndPopup();
	}
}

void WindowParticles::DrawDirectoryRecursive(const char* directory, const char* filter_extension)
{
	std::vector<std::string> files;
	std::vector<std::string> dirs;
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;

	std::string dir((directory) ? directory : "");

	FileSystem::DiscoverFiles(dir.c_str(), files, dirs);

	for (std::vector<std::string>::const_iterator it = dirs.begin(); it != dirs.end(); ++it)
	{
		std::string folder = (dir + (*it)).c_str();
		if (strcmp(folder.c_str(), selected_folder) == 0)
			flags = ImGuiTreeNodeFlags_Selected;

		if (ImGui::TreeNodeEx(folder.c_str(), flags, "%s/", (*it).c_str()))
		{
			flags = ImGuiTreeNodeFlags_None;

			if (ImGui::IsItemClicked())
				sprintf_s(selected_folder, 256, "%s%s", directory, (*it).c_str());

			DrawDirectoryRecursive((dir + (*it)).c_str(), filter_extension);
			ImGui::TreePop();
		}

		flags = ImGuiTreeNodeFlags_None;
	}

	std::sort(files.begin(), files.end());

	for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); ++it)
	{
		const std::string& str = *it;

		bool ok = true;

		if (filter_extension && str.find(filter_extension) == std::string::npos)
			ok = false;

		flags = ImGuiTreeNodeFlags_Leaf;

		std::string complete_path = std::string(directory) + "/" + str;
		if (strcmp(selected_file, complete_path.c_str()) == 0)
			flags |= ImGuiTreeNodeFlags_Selected;

		if (ok && ImGui::TreeNodeEx(str.c_str(), flags))
		{
			if (ImGui::IsItemClicked()) {
				sprintf_s(selected_file, 256, "%s/%s", dir.c_str(), str.c_str());

				if (ImGui::IsMouseDoubleClicked(0))
				{
					particlesConf->_texture = dynamic_cast<ResourceTexture*>(App->resources->RequestResource(App->resources->Find(selected_file)));
					openSelectionTex = false;
				}
			}

			ImGui::TreePop();
		}
	}
}