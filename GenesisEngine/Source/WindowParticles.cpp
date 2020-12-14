#include "WindowParticles.h"
#include "ImGui/imgui.h"

WindowParticles::WindowParticles()
{

}

WindowParticles::~WindowParticles()
{

}

void WindowParticles::Draw()
{
	if (visible == true) {
		ImGui::Begin("Particle Settings Window");

		ImGui::End();
	}
}