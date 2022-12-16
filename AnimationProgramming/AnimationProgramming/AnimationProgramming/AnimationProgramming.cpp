// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Skeleton.h"
#include "Maths.h"
#include "Engine.h"
#include "Simulation.h"

class CSimulation : public ISimulation
{
	Skeleton spookyScary;
	float deltaTime;
	float deltaTime2;
	virtual void Init() override
	{
		
		spookyScary.Init();
		spookyScary.AnimInit();
		spookyScary.Update();
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
				if (spookyScary.skeletonBones[boneIndex].parent != NULL)
				{
					Matrix4 drawChild = spookyScary.skeletonBones[boneIndex].AnimBones(deltaTime);
					Matrix4 drawParent = spookyScary.skeletonBones[boneIndex].parent->AnimBones(deltaTime);
					DrawLine(drawChild.matrixTab4[0][3] + 300,
							 drawChild.matrixTab4[1][3],
							 drawChild.matrixTab4[2][3],
							drawParent.matrixTab4[0][3] + 300, 
							drawParent.matrixTab4[1][3], 
							drawParent.matrixTab4[2][3], 
							 0.5, 
							 0.5,
							 0.5);
				}

			}
		
			
			deltaTime2++;
			if (deltaTime2 > 20)
			{
				deltaTime2 = 0;
				deltaTime++;
			}
			if (deltaTime > 30)
			{
				deltaTime = 0;
				
			}



		


	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

