#include "Skeleton.h"
#include <string>

void Skeleton::Init()
{
	
	for (int i = 0; i < 64; i++)
	{
		Bone tempBone;

		const char* boneName = GetSkeletonBoneName(i);
		if (std::string(boneName).find("ik_") != std::string::npos)
		{ 
			continue;
		}

		tempBone.id_ = i;
		skeletonBones.push_back(tempBone);

	}

	for (int j = 0; j < skeletonBones.size(); j++)
	{
		int parentIndex = GetSkeletonBoneParentIndex(j);

		if (parentIndex != -1)
		{
			skeletonBones[j].parent = &skeletonBones[parentIndex];
			skeletonBones[parentIndex].childrenBone.push_back(&skeletonBones[j]);
		}

	}
	for (int boneIndex = 0; boneIndex < skeletonBones.size(); ++boneIndex)
	{
		Vector3D pos;
		Quaternion tempRot;
		Quaternion invTempRot;
		float x1, y1, z1, qx1, qy1, qz1, qw1;
		
		GetSkeletonBoneLocalBindTransform(skeletonBones[boneIndex].id_, x1, y1, z1, qw1, qx1, qy1, qz1);
		pos = Vector3D(x1, y1, z1);
		tempRot = Quaternion(qw1, Vector3D(qx1, qy1, qz1));
		invTempRot = Quaternion(-qw1, Vector3D(qx1, qy1, qz1));
		Matrix4 localMatrix = identity4x4();
		Matrix4 worldMatrix = identity4x4();
		Matrix4 invLocalMatrix = identity4x4();
		localMatrix = localMatrix.CreateTransformMatrixWithQuaternion(tempRot, pos, { 1, 1, 1 });
		invLocalMatrix = invLocalMatrix.CreateTransformMatrixWithQuaternion(invTempRot, pos*-1, { 1, 1, 1 });
		skeletonBones[boneIndex].localMatrix = localMatrix;
		skeletonBones[boneIndex].invLocalMatrix = invLocalMatrix;
		skeletonBones[boneIndex].worldMatrix = worldMatrix;
		skeletonBones[boneIndex].invWorldMatrix = worldMatrix;
	}

}


void Skeleton::Update()
{
	skeletonBones[0].Update();
}


void Skeleton::AnimInit(const char* a)
{
	size_t keyCount = GetAnimKeyCount(a);

	for (int boneIndex = 0; boneIndex < skeletonBones.size(); boneIndex++)
	{
		skeletonBones[boneIndex].animTransform.resize(keyCount);
		for (size_t i = 0; i < keyCount; i++)
		{
			GetAnimLocalBoneTransform(a, boneIndex, i, 
				skeletonBones[boneIndex].animTransform[i].pos.x,
				skeletonBones[boneIndex].animTransform[i].pos.y,
				skeletonBones[boneIndex].animTransform[i].pos.z,
				skeletonBones[boneIndex].animTransform[i].rot.s,
				skeletonBones[boneIndex].animTransform[i].rot.v.x,
				skeletonBones[boneIndex].animTransform[i].rot.v.y,
				skeletonBones[boneIndex].animTransform[i].rot.v.z);

		}

	}
}