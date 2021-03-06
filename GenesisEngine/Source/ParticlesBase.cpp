#include "ParticlesBase.h"
#include "glew/include/glew.h"
#include "ResourceTexture.h"
#include "MathGeoLib/include/Math/MathFunc.h"
#include "Application.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib") /* link Microsoft OpenGL lib   */

ParticlesBase::ParticlesBase()
{
	parent = nullptr;
	initSize = 0.0f;
	actualSize = 0.0f;
	finalSize = 0.0f;
	particlePosition = float3::zero;
	particleSpeedVector = float3::zero;
	particleLifetime = 0.0f;
	particleActualTime = 0;
	initStateColor = float4::zero;
	finalStateColor = float4::zero;
	particleRotation = Quat::identity;
	particleScale = float3::one;
	texture = nullptr;

	float4x4::FromTRS(particlePosition, particleRotation, particleScale * actualSize);
}

ParticlesBase::ParticlesBase(ParticlesEmitter* _parent, float3 _initialPosition, float3 _particleSpeedVector, float _initSize, float _finalSize, int _particleLifeTime, float4 _initStateColor, float4 _finalStateColor, ResourceTexture* _texture)
{
	//Put the variables well
	parent = _parent;
	initSize = _initSize;
	actualSize = initSize;
	finalSize = _finalSize;
	particlePosition = _initialPosition;
	particleSpeedVector = _particleSpeedVector;
	particleLifetime = _particleLifeTime;
	particleActualTime = 0;
	initStateColor = _initStateColor;
	finalStateColor = _finalStateColor;
	texture = _texture;
	particleRotation = Quat::identity;
	particleScale = float3::one;

	float4x4::FromTRS(particlePosition, particleRotation, particleScale * actualSize);
}

ParticlesBase::~ParticlesBase()
{
	//delete particleMesh;
	//particleMesh = nullptr;
}

void ParticlesBase::UpdateParticle(float dt)
{
	//Update all particle properties
	if (dt != 0) {
		particleActualTime += dt;
		InterpolatePosition(dt);
		InterpolateColor();
		InterpolateSize();
	}

	OrientateParticle();
	//Draw the particle
	//DrawParticle();

	//If the lifetime of the particle is reached, call to delete
	if (particleActualTime >= particleLifetime) {
		ToDelete();
	}
}

void ParticlesBase::DrawParticle()
{
	//Applicate Tint
	glColor4f(actualStateColor.x, actualStateColor.y, actualStateColor.z, actualStateColor.w);

	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//vertices
	//glBindBuffer(GL_ARRAY_BUFFER, particleMesh->id_vertices);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);

	//normals
	//glBindBuffer(GL_NORMAL_ARRAY, particleMesh->id_normals);
	//glNormalPointer(GL_FLOAT, 0, NULL);

	//textures
	//glBindBuffer(GL_ARRAY_BUFFER, particleMesh->id_texcoords);
	//glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	

	//indices
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, particleMesh->id_indices);

	glPushMatrix();

	localMatrix = float4x4::FromTRS(particlePosition, particleRotation, particleScale * actualSize);
	float4x4 ParticleMatrix = localMatrix.Transposed();
	glMultMatrixf(ParticleMatrix.ptr());

	glBindTexture(GL_TEXTURE_2D, texture->GetGpuID());

	
	glBegin(GL_QUADS);
	//glDrawElements(GL_QUADS, particleMesh->num_indices, GL_UNSIGNED_INT, NULL);

	glTexCoord2f(parent->actualframe.x, parent->actualframe.y);
	glVertex3f(0, 0, 0);
	glTexCoord2f(parent->actualframe.x+parent->actualframe.z, parent->actualframe.y);
	glVertex3f(1, 0, 0);
	glTexCoord2f(parent->actualframe.x+ parent->actualframe.z, parent->actualframe.y+ parent->actualframe.w);
	glVertex3f(1, 0, 1);
	glTexCoord2f(parent->actualframe.x, parent->actualframe.y+ parent->actualframe.w);
	glVertex3f(0, 0, 1);

	glEnd();

	glPopMatrix();

	//clean buffers
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_NORMAL_ARRAY, 0);
	//glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glDisable(GL_CULL_FACE);
	glDisable(GL_NORMALIZE);
	glDisable(GL_BLEND);
}

void ParticlesBase::OrientateParticle()
{
	float3 Direction = (particlePosition - App->camera->GetCamera()->GetPosition()).Normalized();
	particleRotation = Quat::LookAt(float3(0.f, 1.f, 0.f), Direction, float3(1.0f, 0.0f, 0.0f), float3(0.0f, 1.0f, 0.0f));
	//localMatrix.setrota = 
}

void ParticlesBase::InterpolateSize()
{
	float percent = particleActualTime / particleLifetime;

	actualSize = Lerp(initSize, finalSize, percent);
}

void ParticlesBase::InterpolatePosition(float dt)
{
	particlePosition += particleSpeedVector * dt;
}

void ParticlesBase::InterpolateColor()
{
	float percent = particleActualTime / particleLifetime;

	float firstValue = Lerp(initStateColor.x, finalStateColor.x, percent);
	float secondValue = Lerp(initStateColor.y, finalStateColor.y, percent);
	float thirdValue = Lerp(initStateColor.z, finalStateColor.z, percent);
	float alphaValue = Lerp(initStateColor.w, finalStateColor.w, percent);

	actualStateColor = float4(firstValue, secondValue, thirdValue, alphaValue);
}