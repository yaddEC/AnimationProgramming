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
	std::vector<Matrix4> skinningMatrices;
	std::vector<Matrix4> indetittys;
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

		ComputeSkinningMatrices(spookyScary, skinningMatrices);
		
		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		deltaTime = 2;
	}

	void ComputeSkinningMatrices(const Skeleton& skeleton, std::vector<Matrix4>& skinningMatrices)
	{
		// Clear the skinning matrices vector
		skinningMatrices.clear();

		// Calculate the skinning matrices for each bone in the skeleton
		for (const Bone& bone : skeleton.skeletonBones)
		{
			// Calculate the skinning matrix for the bone
			Matrix4 skinningMatrix = identity4x4();

			// Add the skinning matrix to the skinning matrices vector
			skinningMatrices.push_back(skinningMatrix);
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
			
		const size_t boneCount = spookyScary.skeletonBones.size();
		std::vector<float> boneMatrices(boneCount * 16);

		for (uint32_t boneIndex = 0; boneIndex < spookyScary.skeletonBones.size(); ++boneIndex)
		{
			if (spookyScary.skeletonBones[boneIndex].parent != NULL)
			{
				Matrix4 drawChild = spookyScary.skeletonBones[boneIndex].AnimBones(deltaTime);
				Matrix4 drawParent = spookyScary.skeletonBones[boneIndex].parent->AnimBones(deltaTime);
				DrawLine(drawChild .matrixTab4[0][3] + 300,
						 drawChild .matrixTab4[1][3],
						 drawChild .matrixTab4[2][3],
						 drawParent.matrixTab4[0][3] + 300, 
						 drawParent.matrixTab4[1][3], 
						 drawParent.matrixTab4[2][3], 
						 0.5, 
						 0.5,
						 0.5);

				Matrix4 boneMatrix = spookyScary.skeletonBones[boneIndex].worldMatrix;
				boneMatrix.GetTransposeMat4();
				std::memcpy(&boneMatrices[boneIndex * 16], boneMatrix.matrixTab4, 16 * sizeof(float));
				
			}

		}
		
		SetSkinningPose(boneMatrices.data(), boneCount);
		
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





