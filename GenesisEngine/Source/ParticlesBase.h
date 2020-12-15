#pragma once

#include <vector>
#include <string>
#include "MathGeoLib/include/Geometry/AABB.h"
class ParticleMesh;

class ParticlesBase {
public:
	ParticlesBase();
	~ParticlesBase();

	void UpdateParticle(float dt);
	void DrawParticle();
	void ResetAnimation(int _columns, int _rows);
	void ChangeMesh(ParticleMesh* _pMesh);
	void SetDefaultParticle();
	void ChangeTexture(int _textureID);
	void ToDelete() { _toDelete = true; };
	bool isToDelete() { return _toDelete; };

public:


private:
	bool _toDelete = false;
};