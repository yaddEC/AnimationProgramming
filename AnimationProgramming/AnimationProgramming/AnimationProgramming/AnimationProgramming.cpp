// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Skeleton.h"
#include "Maths.h"
#include "Engine.h"
#include "Simulation.h"
#include "Animation.h"

class CSimulation : public ISimulation
{
	Skeleton spookyScary;
	Animation ThirdPersonWalk;
	float deltaTime;
	virtual void Init() override
	{
		
		spookyScary.Init();
		ThirdPersonWalk.Init(spookyScary);
		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);

		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		deltaTime = 2;

		for (uint32_t boneIndex = 0; boneIndex < GetSkeletonBoneCount(); ++boneIndex)
		{
			float x1, y1, z1, qx1, qy1, qz1, qw1;
			GetSkeletonBoneLocalBindTransform(static_cast<int>(boneIndex), x1, y1, z1, qw1, qx1, qy1, qz1);
			GetSkeletonBoneName(boneIndex);
			printf("%s : % f,% f,% f\n", GetSkeletonBoneName(boneIndex), x1, y1, z1);

		}
	}

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
			
		for (uint32_t boneIndex = 0; boneIndex < spookyScary.skeletonBones.size(); ++boneIndex)
		{
			/*if (spookyScary.skeletonBones[boneIndex].parent != NULL)
			{
				DrawLine(spookyScary.skeletonBones[boneIndex].worldMatrix.matrixTab4[0][3] + 300, 
						 spookyScary.skeletonBones[boneIndex].worldMatrix.matrixTab4[1][3], 
						 spookyScary.skeletonBones[boneIndex].worldMatrix.matrixTab4[2][3], 
						 spookyScary.skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[0][3]+300, 
						 spookyScary.skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[1][3], 
						 spookyScary.skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[2][3], 
						 0.5,
						 0.5, 
						 0.5);

			}*/

			for (uint32_t boneIndex = 0; boneIndex < ThirdPersonWalk.animation[deltaTime].skeletonBones.size(); ++boneIndex)
			{
				if (ThirdPersonWalk.animation[deltaTime].skeletonBones[boneIndex].parent != NULL)
				{
					DrawLine(ThirdPersonWalk.animation[deltaTime].skeletonBones[boneIndex].worldMatrix.matrixTab4[0][3] + 300, 
							 ThirdPersonWalk.animation[deltaTime].skeletonBones[boneIndex].worldMatrix.matrixTab4[1][3], 
							 ThirdPersonWalk.animation[deltaTime].skeletonBones[boneIndex].worldMatrix.matrixTab4[2][3], 
							 ThirdPersonWalk.animation[deltaTime].skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[0][3] + 300, 
							 ThirdPersonWalk.animation[deltaTime].skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[1][3], 
							 ThirdPersonWalk.animation[deltaTime].skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[2][3], 
							 0.5, 
							 0.5,
							 0.5);
				}

			}
			/*float x1, y1, z1, qx1, qy1, qz1, qw1;
			GetSkeletonBoneLocalBindTransform(static_cast<int>(spookyScary.skeletonBones[boneIndex].id_), x1, y1, z1, qw1, qx1, qy1, qz1);

			Matrix4 mat4;
			Vector3D test5 = Quaternion(qw1, Vector3D(qx1, qy1, qz1)).transformQuaternionToEulerAngles();
			mat4 = mat4.CreateTransformMatrix(test5, { x1, y1, z1 }, { 1,1,1 });
			Vector4D pos4d = (Vector4D(1, 1, 1, 1) * mat4); pos4d.Homogenize();
			Vector3D pos = { pos4d.x, pos4d.y, pos4d.z };
			Bone temp = spookyScary.skeletonBones[boneIndex];
			//test3.normalize();
			while (temp.parent != NULL)
			{
				float x2, y2, z2, qx2, qy2, qz2, qw2;
				GetSkeletonBoneLocalBindTransform(temp.id_, x2, y2, z2, qw2, qx2, qy2, qz2);

				temp = *temp.parent;
			}
				
			*/



		}


	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

