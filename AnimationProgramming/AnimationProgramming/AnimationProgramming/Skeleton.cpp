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
	for (int boneIndex = 0; boneIndex < skeletonBones.size(); ++boneIndex)
	{
		Quaternion temp;
		float x1, y1, z1, qx1, qy1, qz1, qw1;
		Vector3D pos;

		GetSkeletonBoneLocalBindTransform(skeletonBones[boneIndex].id_, x1, y1, z1, qw1, qx1, qy1, qz1);
		
		temp = Quaternion(qw1, Vector3D(qx1,qy1,qz1));
		pos = Vector3D(x1, y1, z1);
		Matrix4 localMatrix = identity4x4();
		Matrix4 worldMatrix = identity4x4();
		localMatrix = localMatrix.CreateTranslationMatrix(pos);
		localMatrix = localMatrix * temp.transformQuaternionToMatrix4();

		//localMatrix.CreateScaleMatrix({10,10,10});
		skeletonBones[boneIndex].localMatrix = localMatrix;
		skeletonBones[boneIndex].worldMatrix = worldMatrix;
		
		
	}
	skeletonBones[0].Update();

}