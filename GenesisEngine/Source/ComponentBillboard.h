#ifndef __C_BILLBOARD_H__
#define __C_BILLBOARD_H__

#include "Component.h"
#include "MathGeoLib/include/Math/float3.h"
#include <vector>

class Camera;
class Transform;

enum AlignmentTypes
{
	SCREEN_ALIGNED,
	CAMERA_ALIGNED,
	AXIS_X_ALIGNED,
	AXIS_Y_ALIGNED,
	AXIS_Z_ALIGNED,
	UKNOWN_ALIGNED
};

class ComponentBillboard : public Component
{
public:
	ComponentBillboard(GameObject* gameObject);
	ComponentBillboard();
	~ComponentBillboard();

	void Update(float dt) override;
	virtual void OnEditor() override;
	void PutTransformsFromVectors(Transform& transform, Transform& cameraTransform, float3& right, float3& up, float3& fwd) const;

public:
	AlignmentTypes alignment = AlignmentTypes::CAMERA_ALIGNED;

private:
	const Camera* sceneCamera = nullptr;
	std::vector<char*> alignmentOptions;
};

#endif // !
