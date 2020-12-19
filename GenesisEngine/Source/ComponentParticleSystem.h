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
	void CreateWindowToLoad(bool _isEmitterSettings);
	void DrawDirectoryRecursive(const char* directory, bool _isEmitterSettings);

	void SaveEmitterSettings(const char* _path);
	void LoadEmitterSettings(const char* _path);
	void SaveParticleSettings(const char* _path);
	void LoadParticleSettings(const char* _path);

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

public:
	ParticlesEmitter emitter;

private:
	ResourceMesh* _resource;
	char selected_folder[256];
	char selected_file[256];
	bool openLoadWindow = false;
	bool toLoadEmitter = false;
};