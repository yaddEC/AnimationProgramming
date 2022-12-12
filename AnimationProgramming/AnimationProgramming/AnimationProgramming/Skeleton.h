#pragma once
#include "Engine.h"
#include "Bone.h"

class Skeleton
{
public:
	Skeleton();

	std::vector<Bone>& skeletonBones;
	void Init();
	void setBoneID();
};