#pragma once

#include <vector>
#include <string>
#include "MathGeoLib/include/Geometry/AABB.h"
#include "MathGeoLib/include/Math/float4.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/Quat.h"
#include "Globals.h"
#include "ParticlesEmitter.h"

class ParticlesEmitter;
class ResourceTexture;
class ParticlePlane;

class ParticlesBase {
public:
	ParticlesBase();
	ParticlesBase(ParticlesEmitter* _parent, float3 _initialPosition, float3 _particleSpeedVector, float _initSize, float _finalSize,  int _particleLifeTime, float4 _initStateColor, float4 _finalStateColor, ResourceTexture* _texture, ParticlePlane& _particleMesh);
	~ParticlesBase();

	void UpdateParticle(float dt);
	void DrawParticle();
	void ResetAnimation(int _columns, int _rows);

	void ToDelete() { _toDelete = true; };
	bool isToDelete() { return _toDelete; };

public:
	float initSize = 1;
	float actualSize = 1;
	float finalSize = 1;

	float3 particleSpeedVector = float3::zero;
	float3 particlePosition = float3::zero;
	float3 particleScale = float3::one;
	Quat particleRotation = Quat::identity;

	float particleLifetime = 5;
	float particleActualTime = 5;

	float4 initStateColor = float4(1, 1, 1, 1);
	float4 finalStateColor = float4(1, 1, 1, 1);

	ResourceTexture* texture = nullptr;
	ParticlesEmitter* parent;

	ParticlePlane* particleMesh;

private:
	bool _toDelete = false;
};