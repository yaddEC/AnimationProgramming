#include "Animation.h"
#include <string>

void Animation::Init(Skeleton skel)
{
	size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
	for (size_t i = 0; i < keyCount; i++)
	{
		Skeleton tempSkel;
		
		for (int j = 0; j < GetSkeletonBoneCount(); j++)
		{
			Bone tempBone;
			const char* boneName = GetSkeletonBoneName(j);
			if (std::string(boneName).find("ik_") != std::string::npos)
			{
				continue;
			}
			tempBone.id_ = j;
			tempSkel.skeletonBones.push_back(tempBone);

		}
		for (int j = 0; j < tempSkel.skeletonBones.size(); j++)
		{
			int parentIndex = GetSkeletonBoneParentIndex(j);

			if (parentIndex != -1)
			{
				tempSkel.skeletonBones[j].parent = &tempSkel.skeletonBones[parentIndex];
				tempSkel.skeletonBones[parentIndex].childrenBone.push_back(&tempSkel.skeletonBones[j]);
			}


		}

		for (int boneIndex = 0; boneIndex < tempSkel.skeletonBones.size(); ++boneIndex)
		{
			Quaternion temp;
			float posX, posY, posZ, quatW, quatX, quatY, quatZ;

			Vector3D pos;
			GetAnimLocalBoneTransform("ThirdPersonWalk.anim", boneIndex, keyCount / 30, posX, posY, posZ, quatW, quatX, quatY, quatZ);

			temp = Quaternion(quatW, Vector3D(quatX, quatY, quatZ));
			pos = Vector3D(posX, posY, posZ);
			Matrix4 localMatrix = identity4x4();
			Matrix4 worldMatrix = identity4x4();
			localMatrix =  localMatrix.CreateTransformMatrixWithQuaternion(temp, pos, { 1, 1, 1 });

			tempSkel.skeletonBones[boneIndex].localMatrix = skel.skeletonBones[boneIndex].localMatrix * localMatrix;

			if (tempSkel.skeletonBones[boneIndex].parent != NULL)
			{
				tempSkel.skeletonBones[boneIndex].worldMatrix = skel.skeletonBones[boneIndex].parent->worldMatrix * tempSkel.skeletonBones[boneIndex].localMatrix;
			}
			else
			{
				tempSkel.skeletonBones[boneIndex].worldMatrix = worldMatrix;
			}
		}

		tempSkel.skeletonBones[0].Update();
		animation.push_back(tempSkel);

	}
}
