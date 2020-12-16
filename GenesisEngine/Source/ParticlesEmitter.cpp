#include "ParticlesEmitter.h"
#include "ParticlesBase.h"
#include "MathGeoLib/include/Algorithm/Random/LCG.h"
#include "Glew\include\glew.h"
#include "Globals.h"

ParticlesEmitter::ParticlesEmitter()
{
	ResetEmitterShape();
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
	ParticlesBase* _newParticle = new ParticlesBase();

	particles.push_back(_newParticle);
}

void ParticlesEmitter::Play(float dt)
{

}

void ParticlesEmitter::UpdateEmitter(float dt)
{
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

void ParticlesEmitter::PutNewConfigValues(EmitterConfig& eConfig, ParticlesConfig& pConfig)
{

}