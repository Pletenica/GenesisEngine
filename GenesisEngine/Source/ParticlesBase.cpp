#include "ParticlesBase.h"
#include "glew/include/glew.h"
#include "ResourceTexture.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib") /* link Microsoft OpenGL lib   */

ParticlesBase::ParticlesBase()
{

}

ParticlesBase::ParticlesBase(ParticlesEmitter* _parent, float3 _initialPosition, float3 _particleSpeedVector, float _initSize, float _finalSize, int _particleLifeTime, float4 _initStateColor, float4 _finalStateColor, ResourceTexture* _texture, ParticlePlane& _particleMesh)
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
	particleMesh = &_particleMesh;
}

ParticlesBase::~ParticlesBase()
{
	delete particleMesh;
	particleMesh = nullptr;
}

void ParticlesBase::UpdateParticle(float dt)
{
	//Update all particle properties
	if (dt != 0) {
		particleActualTime += dt;
		InterpolatePosition(dt);
		//InterpolateSize();
	}

	//Draw the particle
	DrawParticle();

	//If the lifetime of the particle is reached, call to delete
	if (particleActualTime >= particleLifetime) {
		ToDelete();
	}
}

void ParticlesBase::DrawParticle()
{
	//Applicate Tint
	glColor4f(initStateColor.x, initStateColor.y, initStateColor.z, initStateColor.w);

	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//vertices
	glBindBuffer(GL_ARRAY_BUFFER, particleMesh->id_vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//normals
	glBindBuffer(GL_NORMAL_ARRAY, particleMesh->id_normals);
	glNormalPointer(GL_FLOAT, 0, NULL);

	//textures
	glBindBuffer(GL_ARRAY_BUFFER, particleMesh->id_texcoords);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, particleMesh->id_indices);

	glPushMatrix();
	float4x4 ParticleMatrix = float4x4::FromTRS(particlePosition, particleRotation, particleScale * actualSize).Transposed();
	glMultMatrixf(ParticleMatrix.ptr());

	glBindTexture(GL_TEXTURE_2D, texture->GetGpuID());

	glDrawElements(GL_TRIANGLES, particleMesh->num_indices, GL_UNSIGNED_INT, NULL);

	glPopMatrix();

	//clean buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_NORMAL_ARRAY, 0);
	glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_CULL_FACE);
	glDisable(GL_NORMALIZE);
	glDisable(GL_BLEND);
}

void ParticlesBase::ResetAnimation(int _columns, int _rows)
{

}

void ParticlesBase::InterpolateSize()
{
	float firstpercent = particleActualTime / particleLifetime;
	float secondpercent = 1 - firstpercent;
}

void ParticlesBase::InterpolatePosition(float dt)
{
	particlePosition += particleSpeedVector * dt;
}

void ParticlesBase::InterpolateColor()
{

}