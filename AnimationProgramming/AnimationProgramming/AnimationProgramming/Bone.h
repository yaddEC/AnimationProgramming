#pragma once

#include "Engine.h"
#include "Maths.h"
#include <vector>

class Bone
{
public:

	int id_;
	Matrix4 worldMatrix;
	Matrix4 localMatrix;
	Bone* parent;
	std::vector<Bone*> childrenBone;
	void Update();
};