#include "WindowParticles.h"
#include "ImGui/imgui.h"

WindowParticles::WindowParticles()
{

}

WindowParticles::~WindowParticles()
{

}

void WindowParticles::Draw()
{
	if (visible == true) {
		ImGui::Begin("Particle Settings Window");
		ImGui::Text("Emitter Name: ");
		ImGui::SameLine();
		char* bufEmitterName = (char*)emitterConf->emitterName.c_str();
		ImGui::InputText("##emitterName", bufEmitterName, 64, ImGuiInputTextFlags_EnterReturnsTrue);

		ImGui::Text("Particle Name: ");
		ImGui::SameLine();
		char* bufParticleName = (char*)particlesConf->particlesName.c_str();
		ImGui::InputText("##particleName", bufParticleName, 64, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::End();
	}
}

void WindowParticles::DrawParticlesAnimationProperties()
{
}

void WindowParticles::DrawParticlesInitStateProperties()
{
}

void WindowParticles::DrawParticlesFinalStateProperties()
{
}

void WindowParticles::DrawEmitterSettings()
{
}

void WindowParticles::UpdateEmitterInWindow(ParticlesEmitter& _emitter)
{
	emitterConf = &_emitter._emitterConfig;
	particlesConf = &_emitter._particlesConfig;
}
