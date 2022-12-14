#include "Skeleton.h"
#include <string>

void Skeleton::Init()
{
	
	for (int i = 0; i < 64; i++)
	{
		Bone tempBone;

		/*const char* boneName = GetSkeletonBoneName(i);
		if (std::string(boneName).find("ik_") != std::string::npos)
		{ 
			continue;
		}*/

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
	for (int boneIndex = 0; boneIndex < 64; ++boneIndex)
	{
		Vector3D pos;
		Quaternion tempRot;
		float x1, y1, z1, qx1, qy1, qz1, qw1;
		//Vector3D posAnim;
		//Quaternion tempRotAnim;
		//float x2, y2, z2, qx2, qy2, qz2, qw2;

		//size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		
		GetSkeletonBoneLocalBindTransform(skeletonBones[boneIndex].id_, x1, y1, z1, qw1, qx1, qy1, qz1);
		//GetAnimLocalBoneTransform("ThirdPersonWalk.anim", skeletonBones[boneIndex].id_, keyCount / 30, x2, y2, z2, qx2, qy2, qz2, qw2);

		pos = Vector3D(x1, y1, z1);
		tempRot = Quaternion(qw1, Vector3D(qx1, qy1, qz1));
		//posAnim = Vector3D(x2, y2, z2);
		//tempRotAnim = Quaternion(qw2, Vector3D(qx2, qy2, qz2));

		Matrix4 localMatrix = identity4x4();
		Matrix4 worldMatrix = identity4x4();

		localMatrix = localMatrix.CreateTransformMatrixWithQuaternion(tempRot, pos, { 1, 1, 1 });

		/*if (skeletonBones[boneIndex].parent != NULL)
		{
			localMatrix = localMatrix * skeletonBones[boneIndex].parent->worldMatrix * localMatrix.CreateTransformMatrixWithQuaternion(tempRotAnim, posAnim, { 1, 1, 1 });
		}*/
		skeletonBones[boneIndex].localMatrix = localMatrix;
		skeletonBones[boneIndex].worldMatrix = worldMatrix;
	}
	skeletonBones[0].Update();
}