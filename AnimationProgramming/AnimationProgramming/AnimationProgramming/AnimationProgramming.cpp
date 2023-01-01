// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "imgui.h"
#include "Skeleton.h"
#include "Maths.h"
#include "Engine.h"
#include "Simulation.h"

class CSimulation : public ISimulation
{
	size_t keyCountWalk;
	size_t keyCountRun;
	Skeleton spookyScaryWalk;
	Skeleton spookyScaryRun;
	std::vector<Matrix4> skinningMatrices;
	float deltaTime;
	float deltaTime2;
	float deltaTime3;
	const char* nameAnimWalk = "ThirdPersonWalk.anim";
	const char* nameAnimRun = "ThirdPersonRun.anim";

	virtual void Init() override
	{
		ImGui::SetCurrentContext((ImGuiContext*)GetImGUIContext());
		keyCountWalk = GetAnimKeyCount(nameAnimWalk);
		keyCountRun = GetAnimKeyCount(nameAnimRun);


		spookyScaryWalk.Init();
		spookyScaryWalk.AnimInit(nameAnimWalk);
		spookyScaryWalk.Update();

		spookyScaryRun.Init();
		spookyScaryRun.AnimInit(nameAnimRun);
		spookyScaryRun.Update();


		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);
		
		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		
		GetAnimLocalBoneTransform(nameAnimWalk, spineParent, keyCountWalk / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCountWalk);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		deltaTime = 2;
		deltaTime3 = 2;
	}
	float frame = 3; 

	virtual void Update(float frameTime) override
	{
		float fps = ImGui::GetIO().Framerate;
		ImGui::Text("FPS: %.1f", fps);

		ImGui::Begin("Debug");
		ImGui::SliderFloat("Frame", &frame, 0, 7);
		ImGui::End();


		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
			
		const size_t boneCountWalk = spookyScaryWalk.skeletonBones.size();
		const size_t boneCountRun = spookyScaryRun.skeletonBones.size();
		std::vector<float> boneMatrices(boneCountWalk * 16);
		std::vector<float> boneMatrices2(boneCountRun * 16);

		for (uint32_t boneIndex = 0; boneIndex < spookyScaryWalk.skeletonBones.size(); ++boneIndex)
		{
			Matrix4 boneMatrix;
			Matrix4 drawChild = spookyScaryWalk.skeletonBones[boneIndex].AnimBones(deltaTime);
			Matrix4 drawChild2 = spookyScaryWalk.skeletonBones[boneIndex].AnimBones(deltaTime);
			boneMatrix.inverse(spookyScaryWalk.skeletonBones[boneIndex].worldMatrix, boneMatrix);
			boneMatrix = boneMatrix.GetTransposeMat4() * drawChild.GetTransposeMat4();

			std::memcpy(&boneMatrices[boneIndex * 16], boneMatrix.matrixTab4, 16 * sizeof(float));
			if (spookyScaryWalk.skeletonBones[boneIndex].parent != NULL)
			{
				Matrix4 drawParent = spookyScaryWalk.skeletonBones[boneIndex].parent->AnimBones(deltaTime);
				DrawLine(drawChild .matrixTab4[0][3] - 150,
						 drawChild .matrixTab4[1][3],
						 drawChild .matrixTab4[2][3],
						 drawParent.matrixTab4[0][3] - 150, 
						 drawParent.matrixTab4[1][3], 
						 drawParent.matrixTab4[2][3], 
						 0.5, 
						 0.5,
						 0.5);
			}
		}

		for (uint32_t boneIndex = 0; boneIndex < spookyScaryRun.skeletonBones.size(); ++boneIndex)
		{
			Matrix4 boneMatrix;
			Matrix4 drawChild = spookyScaryRun.skeletonBones[boneIndex].AnimBones(deltaTime3);
			Matrix4 drawChild2 = spookyScaryRun.skeletonBones[boneIndex].AnimBones(deltaTime3);
			boneMatrix.inverse(spookyScaryRun.skeletonBones[boneIndex].worldMatrix, boneMatrix);
			boneMatrix = boneMatrix.GetTransposeMat4() * drawChild.GetTransposeMat4();

			std::memcpy(&boneMatrices2[boneIndex * 16], boneMatrix.matrixTab4, 16 * sizeof(float));
			if (spookyScaryRun.skeletonBones[boneIndex].parent != NULL)
			{
				Matrix4 drawParent = spookyScaryRun.skeletonBones[boneIndex].parent->AnimBones(deltaTime3);
				DrawLine(drawChild.matrixTab4[0][3] + 150,
						 drawChild.matrixTab4[1][3],
						 drawChild.matrixTab4[2][3],
						 drawParent.matrixTab4[0][3] + 150,
						 drawParent.matrixTab4[1][3],
						 drawParent.matrixTab4[2][3],
						 1,
						 0.5,
						 0.6);
			}
		}

		SetSkinningPose(boneMatrices.data(), boneCountWalk);
		
		deltaTime2++;
		if (deltaTime2 > frame)
		{
			deltaTime2 = 0;
			deltaTime++;
			deltaTime3++;
		}
		if (deltaTime3 > keyCountRun - 1)
		{
			deltaTime3 = 0;
		}
		if (deltaTime > keyCountWalk - 1)
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





