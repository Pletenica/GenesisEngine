#pragma once

#include "EditorWindow.h"
#include "ParticlesEmitter.h"
#include "ParticlesBase.h"
#include "ImGui/imgui.h"

class WindowParticles : public EditorWindow {
public:
	WindowParticles();
	~WindowParticles();
	void Draw() override;

	void DrawParticlesAnimationProperties();
	void DrawParticlesInitStateProperties();
	void DrawParticlesFinalStateProperties();
	void DrawEmitterFormSettings();
	void DrawEmitterSettings();

	void UpdateEmitterInWindow(ParticlesEmitter& _emitter);

private:
	EmitterConfig* emitterConf;
	ParticlesConfig* particlesConf;
	ParticlesEmitter* particleEmitter;


	ImVec4 textColor = ImVec4(0.5f, 0.5f, 1, 1);
};