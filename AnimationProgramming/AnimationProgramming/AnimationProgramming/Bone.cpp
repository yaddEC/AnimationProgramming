#include "Bone.h"

Matrix4 Bone::AnimBones(int keyframe)
{
	Matrix4 localMatrixTemp = localMatrixTemp.CreateTransformMatrixWithQuaternion(animTransform[keyframe].rot, animTransform[keyframe].pos, { 1, 1, 1 });
	localMatrixTemp = localMatrix * localMatrixTemp;
	Bone* temp = parent;
	Matrix4 tempMat = identity4x4();
	while(temp != NULL)
	{
		Matrix4 tempMat2;
		tempMat2 = tempMat2.CreateTransformMatrixWithQuaternion(temp->animTransform[keyframe].rot, temp->animTransform[keyframe].pos, { 1, 1, 1 });
		tempMat2 = temp->localMatrix * tempMat2;
		tempMat =  tempMat2*tempMat;
		temp = temp->parent;
	}

		return tempMat * localMatrixTemp ;
	
}

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