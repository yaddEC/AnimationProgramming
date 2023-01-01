#include "Bone.h"

Matrix4 Bone::AnimBones(int keyframe, float percent, size_t animSize)
{
	Vector3D lerp;
	Quaternion slerp;
	if (keyframe == animSize - 1)
	{
		lerp = PosLerp(animTransform[keyframe].pos, animTransform[0].pos, percent);
		slerp = Slerp(animTransform[keyframe].rot, animTransform[0].rot, percent);
	}
	else
	{
		lerp = PosLerp(animTransform[keyframe].pos, animTransform[keyframe + 1].pos, percent);
		slerp = Slerp(animTransform[keyframe].rot, animTransform[keyframe + 1].rot, percent);
	}
	Matrix4 localMatrixTemp = localMatrixTemp.CreateTransformMatrixWithQuaternion(slerp, lerp, { 1, 1, 1 });
	localMatrixTemp = localMatrix * localMatrixTemp;
	Bone* temp = parent;
	Matrix4 tempMat = identity4x4();
	while (temp != NULL)
	{
		if (keyframe == animSize - 1)
		{
			lerp = PosLerp(temp->animTransform[keyframe].pos, temp->animTransform[0].pos, percent);
			slerp = Slerp(temp->animTransform[keyframe].rot, temp->animTransform[0].rot, percent);
		}
		else
		{
			lerp = PosLerp(temp->animTransform[keyframe].pos, temp->animTransform[keyframe + 1].pos, percent);
			slerp = Slerp(temp->animTransform[keyframe].rot, temp->animTransform[keyframe + 1].rot, percent);
		}
		Matrix4 tempMat2;
		tempMat2 = tempMat2.CreateTransformMatrixWithQuaternion(slerp, lerp, { 1, 1, 1 });
		tempMat2 = temp->localMatrix * tempMat2;
		tempMat = tempMat2 * tempMat;
		temp = temp->parent;
	}

	return tempMat * localMatrixTemp;
}

void Bone::Update()
{
	//test3.normalize();
	if (parent != NULL)
	{
		worldMatrix = parent->worldMatrix * localMatrix;
		invWorldMatrix = parent->invWorldMatrix * invLocalMatrix;
	}
	else
	{
		worldMatrix = localMatrix;
		invWorldMatrix = invLocalMatrix;
	}

	for (int i = 0; i < childrenBone.size(); i++)
	{
		childrenBone[i]->Update();
	}
}