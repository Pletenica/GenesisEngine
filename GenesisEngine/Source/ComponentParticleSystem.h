#pragma once
#include "Globals.h"
#include "Component.h"
#include <vector>;
#include "Material.h"

#include "MathGeoLib/include/MathGeoLib.h"
#include "WindowEmitter.h"
#include "WindowParticles.h"

class ResourceMesh;

typedef float GLfloat;
typedef unsigned short GLushort;
typedef unsigned char GLubyte;

class ComponentParticleSystem : public Component {
public:
	ComponentParticleSystem();
	ComponentParticleSystem(GameObject* gameObject);
	virtual ~ComponentParticleSystem();

	virtual void Update() override;
	void Reset();
	virtual void OnEditor() override;

	void SetResourceUID(uint UID) override;
	Resource* GetResource(ResourceType type) override;

public:
	std::string emitterName;
	std::string particleName;

private:
	ResourceMesh* _resource;
	WindowEmitter* emiterWindow;
	WindowParticles* particlesWindow;
};