#include "ParticlesEmitter.h"
#include "ParticlesBase.h"
#include "MathGeoLib/include/Algorithm/Random/LCG.h"
#include "Glew\include\glew.h"
#include "Globals.h"
#include "Application.h"
#include "Time.h"
#include "MathGeoLib/include/Math/float3.h"
#include "ModuleInput.h"
#include"WindowParticles.h"

ParticlesEmitter::ParticlesEmitter()
{
	_particlesConfig._texture = dynamic_cast<ResourceTexture*>(App->resources->RequestResource(App->resources->Find("Assets/EngineAssets/ParticleBase.png")));
	ResetEmitterShape();

	WindowParticles* w_part = (WindowParticles*)App->editor->windows[PARTICLES_EDITOR_WINDOW];
	w_part->UpdateEmitterInWindow(*this);
	//InstantiateNewParticle();
}

ParticlesEmitter::~ParticlesEmitter()
{
	particles.clear();
	if (_particlesConfig._texture!= nullptr) {
		App->resources->ReleaseResource(_particlesConfig._texture->GetUID());
	}
	
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
		glVertex3f(((cos(angleToLines * i) * sphereRadius)+ GetEmitterPosition().x), GetEmitterPosition().y, ((sin(angleToLines * i) * sphereRadius))+ GetEmitterPosition().z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15; i++)
		glVertex3f(((cos(angleToLines * i) * sphereRadius)+ GetEmitterPosition().x), ((sin(angleToLines * i) * sphereRadius)+ GetEmitterPosition().y), GetEmitterPosition().z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 15; i++)
		glVertex3f(GetEmitterPosition().x, ((sin(angleToLines * i) * sphereRadius)+ GetEmitterPosition().y), ((cos(angleToLines * i) * sphereRadius))+ GetEmitterPosition().z);
	glEnd();

	glLineWidth(1.0f);
	glEnable(GL_LIGHTING);
}

void ParticlesEmitter::DrawSemiSphere()
{
	glLineWidth(1.3f);
	glDisable(GL_LIGHTING);

	float semisphereRadius = emitterBody._sphere.r;
	float angleToLines = 360.0f / 10;
	angleToLines *= DEGTORAD;

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 10; i++)
		glVertex3f(((cos(angleToLines * i) * semisphereRadius) + GetEmitterPosition().x), GetEmitterPosition().y, ((sin(angleToLines * i) * semisphereRadius))+ GetEmitterPosition().z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i <= 5; i++)
		glVertex3f(((cos(angleToLines * i) * semisphereRadius)+ GetEmitterPosition().x), ((sin(angleToLines * i) * semisphereRadius)+ GetEmitterPosition().y), GetEmitterPosition().z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i <= 5; i++)
		glVertex3f(GetEmitterPosition().x, ((sin(angleToLines * i) * semisphereRadius)+ GetEmitterPosition().y), ((cos(angleToLines * i) * semisphereRadius))+ GetEmitterPosition().z);
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
		glVertex3f(((cos(angleToLines * i) * coneRadiusDown)+ GetEmitterPosition().x), GetEmitterPosition().y, ((sin(angleToLines * i) * coneRadiusDown))+GetEmitterPosition().z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i <= 20; i++)
		glVertex3f((cos(angleToLines * i) * coneRadiusUp + GetEmitterPosition().x), (coneHeight + GetEmitterPosition().y), (sin(angleToLines * i) * coneRadiusUp) + GetEmitterPosition().z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f((GetEmitterPosition().x + coneRadiusDown), GetEmitterPosition().y, GetEmitterPosition().z);
	glVertex3f((GetEmitterPosition().x + coneRadiusUp), (GetEmitterPosition().y + coneHeight), GetEmitterPosition().z);
	glVertex3f((GetEmitterPosition().x -coneRadiusUp), (GetEmitterPosition().y + coneHeight), GetEmitterPosition().z);
	glVertex3f((GetEmitterPosition().x -coneRadiusDown), GetEmitterPosition().y, GetEmitterPosition().z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(GetEmitterPosition().x, GetEmitterPosition().y, (GetEmitterPosition().z - coneRadiusDown));
	glVertex3f(GetEmitterPosition().x, (GetEmitterPosition().y + coneHeight), (GetEmitterPosition().z - coneRadiusUp));
	glVertex3f(GetEmitterPosition().x, (GetEmitterPosition().y + coneHeight), (GetEmitterPosition().z + coneRadiusUp));
	glVertex3f(GetEmitterPosition().x, GetEmitterPosition().y, (GetEmitterPosition().z + coneRadiusDown));
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
		glVertex3f(((cos(angleToLines * i) * circleRadius)+ GetEmitterPosition().x), GetEmitterPosition().y, ((sin(angleToLines * i) * circleRadius))+ GetEmitterPosition().z);
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


void ParticlesEmitter::PutCorrectFrameAnimation()
{
	animframes.clear();
	int height = _particlesConfig._texture->GetHeight();
	int width = _particlesConfig._texture->GetWidth();
	float xincrement = width/_particlesConfig.animcolumn;
	float yincrement= height / _particlesConfig.animrow;
	float cx = 0;
	float cy = 0;
	for (size_t y = 0; y < _particlesConfig.animrow; y++)
	{
		for (size_t x = 0; x < _particlesConfig.animcolumn; x++)
		{
			ImVec4 topush = NormalizeCoords(ImVec4(cx, cy,xincrement,yincrement), ImVec2(width, height));
			animframes.push_back(topush);

			cx += xincrement;
		}

		cx = 0;
		cy += yincrement;
	}
	actualframe = animframes[0];
}

ImVec4 ParticlesEmitter::NormalizeCoords(ImVec4 input, ImVec2 size)
{

	return ImVec4(input.x/size.x, fabsf((input.y/size.y)-1), input.z/size.x, (input.w / size.y));
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

		ParticlesBase* _newParticle = new ParticlesBase(this, offset, Direction * particleSpeed, initSize, finalSize, particleLifeTime, _particlesConfig.initStateColor, _particlesConfig.finalStateColor, _particlesConfig._texture /*particlesMesh*/);
		particles.push_back(_newParticle);
	}
}

void ParticlesEmitter::UpdateEmitter(float dt)
{
	//Update Emitter Actual LifeTime
	emitterActualLifetime += dt;
	actualTimeBetweenParticles += dt;
	
	//GenerateTextureAnimation();
	if (_emitterConfig.emitterLoop == false && emitterActualLifetime >= _emitterConfig.emitterMaxLifetime) {
		isEmitterDead = true;
	}

	if (_emitterConfig.emitterLoop == true || isEmitterDead == false) {
		//Watch if emitter passed init time to do the things
		if (emitterActualLifetime >= _emitterConfig.timeToInit) {
			//Condition if we can put a new particle
			if (actualTimeBetweenParticles >= _emitterConfig.timeMaxBetweenParticles) {
				//If the time between spawn particles is 0, spawn all the particles in one frame
				Play();

				actualTimeBetweenParticles = 0;
			}
		}
	}
	//if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
	//	InstantiateNewParticle();
	//}

	std::multimap<float, ParticlesBase*> mapParticles;

	//Update the particles
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->UpdateParticle(dt);

		float distance = App->camera->GetCamera()->GetFrustum().pos.DistanceSq(particles[i]->particlePosition);
		mapParticles.emplace(distance, particles[i]);
	}

	//Draw the particles
	for (auto i = mapParticles.rbegin(); i != mapParticles.rend(); i++) {
		auto r = mapParticles.equal_range(i->first);
		for (auto k = r.first; k != r.second; k++) {
			k->second->DrawParticle();
		}
	}

	mapParticles.clear();

	//Delete the particles
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i]->isToDelete()) {
			particles.erase(particles.begin() + i);
		}
	}
	

	//Draw if emitter AABB show bool is true
	if (_emitterConfig.showEmitterAABB == true) {
		DrawEmitterAABB();
	}
	//Draw if emitter form show bool is true
	if (_emitterConfig.showEmitterForm == true) {
		DrawEmitter();
	}

	if (!animframes.empty() && Time::gameClock.deltaTime() != 0) {
		doraemon += Time::gameClock.deltaTime();
		if (doraemon >= _particlesConfig.animspeed) {
			(animframeID >= animframes.size() - 1) ? animframeID = 0 : animframeID++;
			actualframe = animframes[animframeID];
			doraemon = 0;
		}
	}
	
}

void ParticlesEmitter::Play()
{
	if (_emitterConfig.timeMaxBetweenParticles == 0) {
		for (int i = 0; i < _emitterConfig.particleMaxSpawn - particles.size(); i++) {
			InstantiateNewParticle();
		}
	}
	//if not, spawn one particle
	else {
		InstantiateNewParticle();
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
	if (_emitterConfig.emitterForm == EmitterForm::EMITTER_FORM_SEMISPHERE) {
		//Calculate Position
		_position = float3::zero;
		//Calculate Direction
		float pointx = randomizer.Float(-360 * DEGTORAD, 360 * DEGTORAD);
		float pointy = randomizer.Float(-180 * DEGTORAD, 180 * DEGTORAD);
		float pointz = randomizer.Float(-360 * DEGTORAD, 360 * DEGTORAD);
		_direction = float3(pointx, pointy, pointz);
	}
	if (_emitterConfig.emitterForm == EmitterForm::EMITTER_FORM_SPHERE) {
		//Calculate Position
		_position = float3::zero;
		//Calculate Direction
		float pointx = randomizer.Float(-360 * DEGTORAD, 360 * DEGTORAD);
		float pointy = randomizer.Float(-360 * DEGTORAD, 360 * DEGTORAD);
		float pointz = randomizer.Float(-360 * DEGTORAD, 360 * DEGTORAD);
		_direction = float3(pointx, pointy, pointz);
	}
	if (_emitterConfig.emitterForm == EmitterForm::EMITTTER_FORM_CIRCLE) {
		//Calculate Direction
		float pointy = randomizer.Float(0.f, 180 * DEGTORAD);
		_direction = float3(0, pointy, 0);
		//Calculate position
		float posx = randomizer.Float(-emitterBody._circle.r, emitterBody._circle.r);
		float posz = randomizer.Float(-emitterBody._circle.r, emitterBody._circle.r);
		_position = float3(posx,0,posz);
	}

	float3 pos, scale;
	Quat rot;
	transform.Transposed().Decompose(pos, rot, scale);

	Quat rot2 = rot * Quat(_direction, 1.f) * rot.Conjugated();
	_direction = float3(rot2.x, rot2.y, rot2.z);

	_position.x += GetEmitterPosition().x;
	_position.y += GetEmitterPosition().y;
	_position.z += GetEmitterPosition().z;
}
