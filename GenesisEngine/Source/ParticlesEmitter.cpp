#include "ParticlesEmitter.h"
#include "ParticlesBase.h"
#include "MathGeoLib/include/Algorithm/Random/LCG.h"
#include "Glew\include\glew.h"
#include "Globals.h"
#include "Application.h"
#include "Time.h"
#include "MathGeoLib/include/Math/float3.h"
#include "ModuleInput.h"

ParticlesEmitter::ParticlesEmitter()
{
	_particlesConfig._texture = dynamic_cast<ResourceTexture*>(App->resources->RequestResource(App->resources->Find("Assets/EngineAssets/ParticleBase.png")));
	ResetEmitterShape();
	//InstantiateNewParticle();
}

ParticlesEmitter::~ParticlesEmitter()
{

}

void ParticlesEmitter::DrawEmitter()
{
	switch (_emitterConfig.emitterForm)
	{
	case(EmitterForm::EMITTER_FORM_CONE):
		DrawCone();
		break;
	case(EmitterForm::EMITTER_FORM_SEMISPHERE):
		DrawSemiSphere();
		break;
	case(EmitterForm::EMITTER_FORM_SPHERE):
		DrawSphere();
		break;
	case(EmitterForm::EMITTTER_FORM_CIRCLE):
		DrawCircle();
		break;
	}
}

void ParticlesEmitter::DrawEmitterAABB()
{

}

void ParticlesEmitter::DrawSphere()
{
	glLineWidth(1.3f);
	glDisable(GL_LIGHTING);

	float sphereRadius = emitterBody._sphere.r;
	float angleToLines = 360.0f / 15;
	angleToLines *= DEGTORAD;

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15; i++)
		glVertex3f(cos(angleToLines * i) * sphereRadius, 0.0f, sin(angleToLines * i) * sphereRadius);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15; i++)
		glVertex3f(cos(angleToLines * i) * sphereRadius, sin(angleToLines * i) * sphereRadius, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15; i++)
		glVertex3f(0.0f, sin(angleToLines * i) * sphereRadius, cos(angleToLines * i) * sphereRadius);
	glEnd();

	glLineWidth(1.0f);
	glEnable(GL_LIGHTING);
}

void ParticlesEmitter::DrawSemiSphere()
{
	glLineWidth(1.3f);
	glDisable(GL_LIGHTING);

	float semisphereRadius = emitterBody._sphere.r;
	float angleToLines = 360.0f / 15;
	angleToLines *= DEGTORAD;

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15; i++)
		glVertex3f(cos(angleToLines * i) * semisphereRadius, 0.0f, sin(angleToLines * i) * semisphereRadius);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15 * 0.5f; i++)
		glVertex3f(cos(angleToLines * i) * semisphereRadius, sin(angleToLines * i) * semisphereRadius, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15*0.5f; i++)
		glVertex3f(0.0f, sin(angleToLines * i) * semisphereRadius, cos(angleToLines * i) * semisphereRadius);
	glEnd();

	glLineWidth(1.0f);
	glEnable(GL_LIGHTING);
}

void ParticlesEmitter::DrawCone()
{
	glLineWidth(1.3f);
	glDisable(GL_LIGHTING);

	float coneRadiusDown = emitterBody._cone.circleDown.r;
	float coneRadiusUp = emitterBody._cone.circleUp.r;
	float coneHeight = emitterBody._cone.height;
	float angleToLines = 360.0f / 20;
	angleToLines *= DEGTORAD;

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 20; i++)
		glVertex3f(cos(angleToLines * i) * coneRadiusDown, 0.0f, sin(angleToLines * i) * coneRadiusDown);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i <= 20; i++)
		glVertex3f(cos(angleToLines * i) * coneRadiusUp, coneHeight, sin(angleToLines * i) * coneRadiusUp);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(coneRadiusDown, 0.0f, 0.0f);
	glVertex3f(coneRadiusUp, coneHeight, 0.0f);
	glVertex3f(-coneRadiusUp, coneHeight, 0.0f);
	glVertex3f(-coneRadiusDown, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, -coneRadiusDown);
	glVertex3f(0.0f, coneHeight, -coneRadiusUp);
	glVertex3f(0.0f, coneHeight, coneRadiusUp);
	glVertex3f(0.0f, 0.0f, coneRadiusDown);
	glEnd();

	glLineWidth(1.0f);
	glEnable(GL_LIGHTING);
}

void ParticlesEmitter::DrawCircle()
{
	glLineWidth(1.3f);
	glDisable(GL_LIGHTING);

	float circleRadius = emitterBody._circle.r;
	float angleToLines = 360.0f / (float)15;
	angleToLines *= DEGTORAD;

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15; i++)
		glVertex3f(cos(angleToLines * i) * circleRadius, 0.0f, sin(angleToLines * i) * circleRadius);
	glEnd();

	glLineWidth(1.0f);
	glEnable(GL_LIGHTING);
}

void ParticlesEmitter::SetDefaultEmitterVariables()
{

}

void ParticlesEmitter::SetNewTextureParticles(int _textureID)
{
	_particlesConfig.textureID = _textureID;
}

void ParticlesEmitter::InstantiateNewParticle()
{
	if (particles.size() < _emitterConfig.particleMaxSpawn) {
		//Randomize all min and max variables and create a new variable with the new values
		LCG randomizer;
		float initSize = randomizer.Float(_particlesConfig.minInitSize, _particlesConfig.maxInitSize);
		float finalSize = randomizer.Float(_particlesConfig.minFinalSize, _particlesConfig.maxFinalSize);
		float particleSpeed = randomizer.Float(_emitterConfig.particleMinSpeed, _emitterConfig.particleMaxSpeed);
		float particleLifeTime = randomizer.Float(_emitterConfig.particlesMinLifetime, _emitterConfig.particlesMaxLifetime);

		float3 Direction = float3::zero;
		float3 offset = float3::zero;

		RandomizeNewPositionAndDirection(offset, Direction);

		ParticlesBase* _newParticle = new ParticlesBase(this, offset, Direction * particleSpeed, initSize, finalSize, particleLifeTime, _particlesConfig.initStateColor, _particlesConfig.finalStateColor, _particlesConfig._texture, particlesMesh);
		particles.push_back(_newParticle);
	}
}

void ParticlesEmitter::Play(float dt)
{

}

void ParticlesEmitter::UpdateEmitter(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		InstantiateNewParticle();
	}

	float deltaTime = Time::gameClock.deltaTime();
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->UpdateParticle(dt);
	}

	//Draw if emitter AABB show bool is true
	if (_emitterConfig.showEmitterAABB == true) {
		DrawEmitterAABB();
	}
	//Draw if emitter form show bool is true
	if (_emitterConfig.showEmitterForm == true) {
		DrawEmitter();
	}
}

void ParticlesEmitter::ResetEmitterShape()
{
	//Reset Cone Variables
	emitterBody._cone.circleUp.r = 1.5f;
	emitterBody._cone.circleUp.pos = float3::zero;
	emitterBody._cone.circleUp.normal = float3(0.f,1.f,0.f);
	emitterBody._cone.circleDown.r = 1.f;
	emitterBody._cone.circleDown.pos = float3::zero;
	emitterBody._cone.circleDown.normal = float3(0.f, 1.f, 0.f);
	emitterBody._cone.height = 1.f;

	//Reset Sphere & SemiSphere Variable
	emitterBody._sphere.r = 1.f;

	//Reset Circle Variable
	emitterBody._circle.r = 1.f;
}

void ParticlesEmitter::SetEmitterTransform(float4x4 _transform)
{
	transform = _transform;
}



float3 ParticlesEmitter::GetEmitterPosition()
{
	float3 pos, scale;
	Quat rot;
	transform.Decompose(pos, rot, scale);
	return pos;
}

Quat ParticlesEmitter::GetEmitterRotation()
{
	float3 pos, scale;
	Quat rot;
	transform.Decompose(pos, rot, scale);
	return rot;
}

float3 ParticlesEmitter::GetEmitterScale()
{
	float3 pos, scale;
	Quat rot;
	transform.Decompose(pos, rot, scale);
	return scale;
}

void ParticlesEmitter::RandomizeNewPositionAndDirection(float3& _position, float3& _direction)
{
	LCG randomizer;

	if (_emitterConfig.emitterForm == EmitterForm::EMITTER_FORM_CONE) {
		float3 upperPoint = float3::zero;
		float3 bottomPoint = float3(0.0f, emitterBody._cone.height, 0.0f);

		if (emitterBody._cone.circleDown.r > 0.0f)
		{
			float radius = randomizer.Float(0, emitterBody._cone.circleDown.r);
			float angle = randomizer.Float(0, 360) * DEGTORAD;
			upperPoint = float3(cos(angle) * radius, 0, sin(angle) * radius);
		}

		if (emitterBody._cone.circleUp.r > 0.0f) {
			bottomPoint = (emitterBody._cone.circleUp.r * upperPoint) / emitterBody._cone.circleDown.r;
		}

		bottomPoint.y = emitterBody._cone.height;

		_position = upperPoint;
		_direction = bottomPoint - upperPoint;
	}
	else if (_emitterConfig.emitterForm == EmitterForm::EMITTER_FORM_SEMISPHERE) {
		_direction = emitterBody._sphere.RandomPointOnSurface(randomizer);
		_direction.y = abs(_direction.y);
	}
	else if (_emitterConfig.emitterForm == EmitterForm::EMITTER_FORM_SPHERE) {
		_direction = emitterBody._sphere.RandomPointOnSurface(randomizer);
	}
	else if (_emitterConfig.emitterForm == EmitterForm::EMITTTER_FORM_CIRCLE) {
		float point = randomizer.Float(0.f, 360 * DEGTORAD);
		_direction = emitterBody._circle.GetPoint(point);
	}

	float3 pos, scale;
	Quat rot;
	transform.Transposed().Decompose(pos, rot, scale);

	Quat rot2 = rot * Quat(_direction, 1.f) * rot.Conjugated();
	_direction = float3(rot2.x, rot2.y, rot2.z);
}

ParticlePlane::ParticlePlane()
{
	vertices = new float[12]{
	0.0f ,0.0f, 0.0f,
	1.0f ,0.0f, 0.0f,
	1.0f ,0.0f, 1.0f,
	0.0f ,0.0f, 1.0f,
	};
	num_vertices = 4;

	indices = new uint[6]{
		0, 3, 2,
		2, 1 ,0
	};
	num_indices = 6;

	normals = new float[num_vertices * 3]{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};
	num_normals = 4;

	GenerateBuffers();
}

ParticlePlane::~ParticlePlane() {

	glDeleteBuffers(1, &id_vertices);
	RELEASE_ARRAY(vertices);
	num_indices = 0;

	glDeleteBuffers(1, &id_indices);
	RELEASE_ARRAY(indices);

	glDeleteBuffers(1, &id_normals);
	RELEASE_ARRAY(normals)
	//if (vertices != nullptr)
	//{
	//	if (id_vertices > 0)
	//		glDeleteBuffers(1, &id_vertices);
	//	id_vertices = 0;
	//	RELEASE_ARRAY(vertices);
	//}
	//num_indices = 0;
	//if (indices != nullptr)
	//{
	//	if (id_indices > 0)
	//		glDeleteBuffers(1, &id_indices);
	//	id_indices = 0;
	//	RELEASE_ARRAY(indices);
	//}
	//if (normals != nullptr)
	//{
	//	if (id_normals > 0)
	//		glDeleteBuffers(1, &id_normals);
	//	id_normals = 0;
	//	RELEASE_ARRAY(normals);
	//}
}

void ParticlePlane::GenerateBuffers()
{
	//vertices
	glGenBuffers(1, (GLuint*)&(id_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) *num_vertices * 3, vertices, GL_STATIC_DRAW);

	//indices
	glGenBuffers(1, (GLuint*)&(id_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_indices, indices, GL_STATIC_DRAW);

	//normals
	glGenBuffers(1, (GLuint*)&(id_normals));
	glBindBuffer(GL_NORMAL_ARRAY, id_normals);
	glBufferData(GL_NORMAL_ARRAY, sizeof(float) * num_vertices * 3, normals, GL_STATIC_DRAW);

	//textures
	//glGenBuffers(1, (GLuint*)&(id_textures));
	//glBindBuffer(GL_ARRAY_BUFFER, id_textures);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * 2, texcoords, GL_STATIC_DRAW);

}

void ParticlePlane::DeleteBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &id_vertices);
	id_vertices = 0;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &id_indices);
	id_indices = 0;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &id_normals);
	id_normals = 0;

	//glBindTexture(GL_TEXTURE_2D, 0);
	//glDeleteBuffers(1, &id_textures);
	//id_textures = 0;
}
