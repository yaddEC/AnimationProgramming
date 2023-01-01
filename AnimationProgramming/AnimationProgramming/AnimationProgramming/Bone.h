#pragma once

#include "Engine.h"
#include "Maths.h"
#include "Transform.h"
#include <vector>

class Bone
{
public:

	int id_;
	Matrix4 worldMatrix;
	Matrix4 localMatrix;
	Matrix4 invWorldMatrix;
	Matrix4 invLocalMatrix;
	Bone* parent;
	std::vector<Bone*> childrenBone;
	std::vector<Transform> animTransform;
	Matrix4 AnimBones(int keyframe, float percent, size_t animSize);
	void Update();
};