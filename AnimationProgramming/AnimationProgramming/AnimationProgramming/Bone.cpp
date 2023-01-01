#include "Bone.h"

Matrix4 Bone::AnimBones(int keyframe, float percent, size_t animSize)
{
	Vector3D lerp;
	Quaternion slerp;
	if (keyframe == animSize - 1)
	{
		slerp = animTransform[keyframe].rot;
		if (slerp.Dot(animTransform[0].rot) < 0)
		{
			slerp.Negate();
		}
		slerp = Slerp(slerp, animTransform[0].rot, percent);
		lerp = PosLerp(animTransform[keyframe].pos, animTransform[0].pos, percent);
	}
	else
	{
		slerp = animTransform[keyframe].rot;
		if (slerp.Dot(animTransform[keyframe + 1].rot) < 0)
		{
			slerp.Negate();
		}
		slerp = Slerp(slerp, animTransform[keyframe + 1].rot, percent);
		lerp = PosLerp(animTransform[keyframe].pos, animTransform[keyframe + 1].pos, percent);
	}
	Matrix4 localMatrixTemp = localMatrixTemp.CreateTransformMatrixWithQuaternion(slerp, lerp, { 1, 1, 1 });
	localMatrixTemp = localMatrix * localMatrixTemp;
	Bone* temp = parent;
	Matrix4 tempMat = identity4x4();
	while (temp != NULL)
	{
		if (keyframe == animSize - 1)
		{
			slerp = temp->animTransform[keyframe].rot;
			if (slerp.Dot(temp->animTransform[0].rot) < 0)
			{
				slerp.Negate();
			}
			slerp = Slerp(slerp, temp->animTransform[0].rot, percent);
			lerp = PosLerp(temp->animTransform[keyframe].pos, temp->animTransform[0].pos, percent);
		}
		else
		{
			slerp = temp->animTransform[keyframe].rot;
			if (slerp.Dot(temp->animTransform[keyframe + 1].rot) < 0)
			{
				slerp.Negate();
			}
			slerp = Slerp(slerp, temp->animTransform[keyframe + 1].rot, percent);
			lerp = PosLerp(temp->animTransform[keyframe].pos, temp->animTransform[keyframe + 1].pos, percent);
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