#include "WindowEmitter.h"
#include "ImGui/imgui.h"

WindowEmitter::WindowEmitter()
{

}

WindowEmitter::~WindowEmitter()
{

}

void WindowEmitter::Draw()
{
	if (visible == true) {
		ImGui::Begin("Emitter Settings Window");

		ImGui::End();
	}
}