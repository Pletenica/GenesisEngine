#pragma once

#include "EditorWindow.h"
#include "ParticlesEmitter.h"
#include "ParticlesBase.h"

class WindowParticles : public EditorWindow {
public:
	WindowParticles();
	~WindowParticles();
	void Draw() override;

	void DrawParticlesAnimationProperties();
	void DrawParticlesInitStateProperties();
	void DrawParticlesFinalStateProperties();
	void DrawEmitterSettings();

	void UpdateEmitterInWindow(ParticlesEmitter& _emitter);

private:
	EmitterConfig* emitterConf;
	ParticlesConfig* particlesConf;
};