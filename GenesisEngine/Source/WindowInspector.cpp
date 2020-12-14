#include "WindowInspector.h"
#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"

WindowInspector::WindowInspector() : EditorWindow()
{
	type = WindowType::INSPECTOR_WINDOW;
}

WindowInspector::~WindowInspector()
{
}

void WindowInspector::Draw()
{
	if (ImGui::Begin("Inspector", &visible))
	{
		if (App->scene->selectedGameObject != nullptr)
		{
			App->scene->selectedGameObject->OnEditor();
			DoAddComponentOption();
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		//Draw Debug Information
		if (ImGui::CollapsingHeader("Debugging Information"))
		{
			if (App->scene->selectedGameObject->GetParent() != nullptr)
				ImGui::Text("Parent: %s", App->scene->selectedGameObject->GetParent()->GetName());
			else
				ImGui::Text("No parent");

			ImGui::Text("UUID: %d", App->scene->selectedGameObject->UUID);
		}

		//Draw Resources Information
		if (ImGui::CollapsingHeader("Resources")) {
			App->resources->OnEditor();
		}
	}
	ImGui::End();
}

void WindowInspector::DoAddComponentOption()
{
	ImGui::Dummy(ImVec2(0.0f, 10.0f));
	if (ImGui::Button("Add Component", ImVec2(200, 0)))
	{
		ImGui::OpenPopup("Add Component Popup");
	}


	if (ImGui::BeginPopup("Add Component Popup"))
	{
		if (ImGui::MenuItem("Mesh"))
		{
			App->scene->selectedGameObject->AddComponent(ComponentType::MESH);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Material"))
		{
			App->scene->selectedGameObject->AddComponent(ComponentType::MATERIAL);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Camera"))
		{
			App->scene->selectedGameObject->AddComponent(ComponentType::CAMERA);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Particle System"))
		{
			App->scene->selectedGameObject->AddComponent(ComponentType::PARTICLE);
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("Billboarding"))
		{
			App->scene->selectedGameObject->AddComponent(ComponentType::BILLBOARD);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}
