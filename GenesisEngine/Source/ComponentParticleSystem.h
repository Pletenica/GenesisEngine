#pragma once
#include "Globals.h"
#include "Component.h"
#include <vector>;
#include "Material.h"

#include "MathGeoLib/include/MathGeoLib.h"
#include "ParticlesEmitter.h"
#include "ParticlesBase.h"
#include "WindowParticles.h"

#define EMITTERSAVEEXTENSION ".emittersettings"
#define PARTICLESAVEEXTENSION ".particlessettings"

class ResourceMesh;

typedef float GLfloat;
typedef unsigned short GLushort;
typedef unsigned char GLubyte;

class ComponentParticleSystem : public Component {
public:
	ComponentParticleSystem();
	ComponentParticleSystem(GameObject* gameObject);
	virtual ~ComponentParticleSystem();

	virtual void Update(float dt) override;
	void Reset();
	virtual void OnEditor() override;

	void SetResourceUID(uint UID) override;
	Resource* GetResource(ResourceType type) override;

	void SaveEmitterSettings(const char* _path);
	void LoadEmitterSettings(const char* _path);
	void SaveParticleSettings(const char* _path);
	void LoadParticleSettings(const char* _path);

public:
	ParticlesEmitter emitter;

private:
	ResourceMesh* _resource;
};