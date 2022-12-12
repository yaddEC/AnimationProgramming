#pragma once

#include "Engine.h"
#include <vector>

class Bone
{
public:

	int id_;
	Bone* parent;
	std::vector<Bone*> childrenBone;
};