#include "ParticlesEmitter.h"
#include "ParticlesBase.h"

ParticlesEmitter::ParticlesEmitter()
{

}

ParticlesEmitter::~ParticlesEmitter()
{

}

void ParticlesEmitter::DrawEmitter()
{

}

void ParticlesEmitter::DrawEmitterAABB()
{

}

void ParticlesEmitter::DrawSphere()
{

}

void ParticlesEmitter::DrawSemiSphere()
{

}

void ParticlesEmitter::DrawCone()
{

}

void ParticlesEmitter::DrawBox()
{

}

void ParticlesEmitter::DrawCircle()
{

}

void ParticlesEmitter::SetDefaultEmitterVariables()
{

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
		switch (_emitterConfig.emitterForm)
		{
		case(EmitterForm::EMITTER_FORM_BOX):
			DrawBox();
			break;
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
}

void ParticlesEmitter::PutNewConfigValues(EmitterConfig& eConfig, ParticlesConfig& pConfig)
{

}