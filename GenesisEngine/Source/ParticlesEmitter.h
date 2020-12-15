#pragma once

#include <vector>
#include <string>
#include "MathGeoLib/include/Geometry/AABB.h"
#include "MathGeoLib/include/Math/float4.h"
class ParticlesBase;

enum EmitterForm {
	EMITTER_FORM_SPHERE,
	EMITTER_FORM_SEMISPHERE,
	EMITTER_FORM_CONE,
	EMITTER_FORM_BOX,
	EMITTTER_FORM_CIRCLE
};

struct EmitterConfig {
	std::string emitterName = "Defalut Emitter Name";
	bool emitterLoop = true;
	bool showEmitterAABB = false;
	bool showEmitterForm = true;

	EmitterForm emitterForm = EmitterForm::EMITTER_FORM_CONE;
	AABB _emitterAABB;

	int particleMaxSpawn = 5;
	float particleMinSpeed, particleMaxSpeed = 0.f;
	float timeToInit = 0.f;
	float emitterMaxLifetime = -1;
	float emitterActualLifetime = 0;
	float timeMaxBetweenParticles = 0.5f;
	float actualTimeBetweenParticles = 0.f;
};

struct ParticlesConfig {
	std::string particlesName = "Defalut Particle Name";
	int animationColumns, animationRows = 1;
	float minSize, maxSize;
	float4 initStateColor, finalStateColor;
};

class ParticlesEmitter {
public:
	ParticlesEmitter();
	~ParticlesEmitter();

	void DrawEmitter();
	void DrawEmitterAABB();
	void DrawSphere();
	void DrawSemiSphere();
	void DrawCone();
	void DrawBox();
	void DrawCircle();

	void SetDefaultEmitterVariables();
	void InstantiateNewParticle();
	void Play(float dt);
	void UpdateEmitter(float dt);

	void PutNewConfigValues(EmitterConfig& eConfig, ParticlesConfig& pConfig);

public:
	EmitterConfig _emitterConfig;
	ParticlesConfig _particlesConfig;

	std::vector<ParticlesBase*> particles;
};