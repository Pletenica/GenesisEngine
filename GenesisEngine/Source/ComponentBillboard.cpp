#include "ComponentBillboard.h"
#include "glew/include/glew.h"
#include "ImGui/imgui.h"
#include "Application.h"
#include "Transform.h"
#include "GameObject.h"

ComponentBillboard::ComponentBillboard(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::BILLBOARD;
	_gameObject = gameObject;

	alignmentOptions.push_back("Screen");
	alignmentOptions.push_back("Camera");
	alignmentOptions.push_back("Axis X");
	alignmentOptions.push_back("Axis Y");
	alignmentOptions.push_back("Axis Z");
}

ComponentBillboard::~ComponentBillboard()
{

}

void ComponentBillboard::Update(float dt)
{
	//TODO: enough for now, change it to assign a camera in the inspector
	if (sceneCamera == nullptr)
	{
		sceneCamera = App->scene->GetActualCamera(App->scene->GetRoot()); //If the camera is null, check other time to camera in scene
	}
	if (sceneCamera == nullptr) {
		return; //If the camera still null do nothing
	}

	float3 right, up, fwd;
	Transform& transform = *(Transform*)_gameObject->GetComponent(ComponentType::TRANSFORM);
	Transform& cameraTransform = *(Transform*)sceneCamera->_gameObject->GetComponent(ComponentType::TRANSFORM);

	PutTransformsFromVectors(transform, cameraTransform, right, up, fwd);
}

void ComponentBillboard::OnEditor()
{
	if (ImGui::CollapsingHeader("Billboard", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Indent();

		int currentAlignmentOption = (int)alignment;
		if (ImGui::Combo("Alignment", &currentAlignmentOption, alignmentOptions.data(), (int)AlignmentTypes::UKNOWN_ALIGNED))
		{
			alignment = (AlignmentTypes)currentAlignmentOption;
		}

		ImGui::Unindent();
	}
}

void ComponentBillboard::PutTransformsFromVectors(Transform& transform, Transform& cameraTransform, float3& right, float3& up, float3& fwd) const
{
	float3 direction = float3(cameraTransform.GetGlobalPosition() - transform.GetGlobalPosition()).Normalized();

	switch (alignment)
	{
	case(AlignmentTypes::SCREEN_ALIGNED):
		fwd = cameraTransform.GetGlobalTransform().WorldZ().Normalized().Neg();
		up = cameraTransform.GetGlobalTransform().WorldY().Normalized();
		right = up.Cross(fwd).Normalized();
		break;
	case(AlignmentTypes::CAMERA_ALIGNED):
		fwd = float3(cameraTransform.GetGlobalPosition() - transform.GetGlobalPosition()).Normalized();
		right = cameraTransform.GetGlobalTransform().WorldY().Normalized().Cross(fwd).Normalized();
		up = fwd.Cross(right).Normalized();
		break;
	case(AlignmentTypes::AXIS_X_ALIGNED):
		right = float3::unitX;
		up = direction.Cross(right).Normalized();
		fwd = right.Cross(up).Normalized();
		break;
	case(AlignmentTypes::AXIS_Y_ALIGNED):
		up = float3::unitY;
		right = up.Cross(direction).Normalized();
		fwd = right.Cross(up).Normalized();
		break;
	case(AlignmentTypes::AXIS_Z_ALIGNED):
		fwd = float3::unitZ;
		right = direction.Cross(fwd).Normalized();
		up = fwd.Cross(right).Normalized();
		break;
	}

	float4x4 resultMatrix(right.ToDir4(), up.ToDir4(), fwd.ToDir4(), transform.GetGlobalPosition().ToPos4());
	transform.SetGlobalTransform(resultMatrix);
}
