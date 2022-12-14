#include "Bone.h"

void Bone::Update()
{
	//test3.normalize();
	if (parent != NULL)
	{
		worldMatrix =  parent->worldMatrix * localMatrix;
	}
	else
	{
		worldMatrix = localMatrix;
	}

	for (int i = 0; i < childrenBone.size(); i++)
	{
		childrenBone[i]->Update();
	}
}