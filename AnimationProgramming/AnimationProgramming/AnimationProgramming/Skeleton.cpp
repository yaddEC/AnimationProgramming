#include "Skeleton.h"

void Skeleton::Init()
{
	for (int i = 0; i < GetSkeletonBoneCount(); i++)
	{
		Bone tempBone;
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
}