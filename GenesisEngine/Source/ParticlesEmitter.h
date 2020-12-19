#pragma once

#include <vector>
#include <string>
#include "MathGeoLib/include/Geometry/AABB.h"
#include "MathGeoLib/include/Math/float4.h"
#include "MathGeoLib/include/Geometry/Sphere.h"
#include "MathGeoLib/include/Geometry/Circle.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "MathGeoLib/include/Math/float2.h"
#include "ResourceTexture.h"
#include "ComponentBillboard.h"

class ParticlesBase;

enum EmitterForm {
	EMITTER_FORM_SPHERE,
	EMITTER_FORM_SEMISPHERE,
	EMITTER_FORM_CONE,
	EMITTTER_FORM_CIRCLE
};

struct EmitterCone {
	Circle circleUp, circleDown;
	float height = 1.f;
};

struct EmitterBody {
	EmitterCone _cone;
	Circle _circle;
	Sphere _sphere;
};

struct EmitterConfig {
	std::string emitterName = "Default Emitter Name";
	bool emitterLoop = true;
	bool showEmitterAABB = false;
	bool showEmitterForm = true;

	EmitterForm emitterForm = EmitterForm::EMITTER_FORM_CONE;
	AABB _emitterAABB;

	int particleMaxSpawn = 5;
	float particleMinSpeed = 0.5f;
	float particleMaxSpeed = 3.f;
	float timeToInit = 0.f;

	float particlesMinLifetime = 2;
	float particlesMaxLifetime = 7;
	float emitterMaxLifetime = 5;
	
	float timeMaxBetweenParticles = 0.5f;
};

struct ParticlesConfig {
	std::string particlesName = "Default Particle Name";

	float minInitSize = 0;
	float maxInitSize = 1;
	float minFinalSize = 0;
	float maxFinalSize = 1;
	float4 initStateColor = float4(1, 1, 1, 1);
	float4 finalStateColor = float4(1, 1, 1, 1);

	int textureHeight = 0;
	int textureWeight = 0;
	int textureID = 0;
	ResourceTexture* _texture = nullptr;
};

class ParticlePlane {
public:
	ParticlePlane();
	~ParticlePlane();

	void GenerateBuffers();
	void DeleteBuffers();

	uint id_vertices = 0;
	uint num_vertices = 0;
	float* vertices = nullptr;

	uint id_indices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals;

	uint id_texcoords = 0;
	uint num_texcoords = 0;
	float* texcoords;

};

class ParticlesEmitter {
public:
	ParticlesEmitter();
	~ParticlesEmitter();

	//Debug Emitter Draw
	void DrawEmitter();
	void DrawEmitterAABB();
	void DrawSphere();
	void DrawSemiSphere();
	void DrawCone();
	void DrawCircle();

	//Emitter Set Values
	void SetDefaultEmitterVariables();
	void SetNewTextureParticles(int _textureID);

	//Emitter Actions
	void InstantiateNewParticle();
	void UpdateEmitter(float dt);

	void ResetEmitterShape();
	void SetEmitterTransform(float4x4 _transform);
	float3 GetEmitterPosition();
	Quat GetEmitterRotation();
	float3 GetEmitterScale();

private:
	void RandomizeNewPositionAndDirection(float3& _position, float3& _direction);

public:
	EmitterConfig _emitterConfig;
	ParticlesConfig _particlesConfig;

	EmitterBody emitterBody;
	std::vector<ParticlesBase*> particles;
	float4x4 transform = float4x4::identity;

	float emitterActualLifetime = 0;
	float actualTimeBetweenParticles = 0.f;

	ParticlePlane particlesMesh = ParticlePlane();
	bool isEmitterDead = false;
};