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
	int CurrentkeyCount;
	int CurrentkeyCount2;
	bool  ChangeAnim = true;
	bool  Pause = false;
	bool  PlayB = false;
	float deltaTime = 0;
	float deltaTime2 = 0;
	float deltaTime3 = 0;
	float frame = 0.5;
	float colorWalk[3] = { 0.5, 0.5, 0.5 };
	float colorRun[3] = { 0, 0.5, 0 };
	const char* nameAnimWalk = "ThirdPersonWalk.anim";
	const char* nameAnimRun  = "ThirdPersonRun.anim";

	virtual void UpdateImgui()
	{
		float fps = ImGui::GetIO().Framerate;
		ImGui::Text("FPS: %.1f", fps);
		ImGui::Text("CurrentkeyCount: %d", CurrentkeyCount);
		ImGui::Text("CurrentkeyCount2: %d", CurrentkeyCount2);
		ImGui::Text("deltaTime: %.01f", deltaTime);

		ImGui::Begin("Debug");
		ImGui::SliderFloat("Frame", &frame, 0.01, 1);
		ImGui::Checkbox("Switch Anim", &ChangeAnim);
		ImGui::Checkbox("Play Backward", &PlayB);
		ImGui::Checkbox("Pause", &Pause);
		if (Pause)
		{
			if (ImGui::Button("Forward"))
			{
				deltaTime += frame;
			}
			if (ImGui::Button("Backward"))
			{
				deltaTime -= frame;
			}
		}
		ImGui::End();

		ImGui::Begin("Color");
		ImGui::ColorEdit3("Color Skelet Walk", colorWalk);
		ImGui::ColorEdit3("Color Skelet Run", colorRun);
		ImGui::End();
	}

	virtual void CreateSkeleton()
	{
		const size_t boneCountWalk = spookyScaryWalk.skeletonBones.size();
		const size_t boneCountRun = spookyScaryRun.skeletonBones.size();
		std::vector<float> boneMatrices(boneCountWalk * 16);
		std::vector<float> boneMatrices2(boneCountRun * 16);

		for (uint32_t boneIndex = 0; boneIndex < spookyScaryWalk.skeletonBones.size(); ++boneIndex)
		{
			Matrix4 boneMatrix;
			Matrix4 drawChild = spookyScaryWalk.skeletonBones[boneIndex].AnimBones(CurrentkeyCount, deltaTime, keyCountWalk);
			boneMatrix.inverse(spookyScaryWalk.skeletonBones[boneIndex].worldMatrix, boneMatrix);
			boneMatrix = boneMatrix.GetTransposeMat4() * drawChild.GetTransposeMat4();

			std::memcpy(&boneMatrices[boneIndex * 16], boneMatrix.matrixTab4, 16 * sizeof(float));
			if (spookyScaryWalk.skeletonBones[boneIndex].parent != NULL)
			{
				Matrix4 drawParent = spookyScaryWalk.skeletonBones[boneIndex].parent->AnimBones(CurrentkeyCount, deltaTime, keyCountWalk);
				DrawLine(drawChild .matrixTab4[0][3] - 150,
						 drawChild .matrixTab4[1][3],
						 drawChild .matrixTab4[2][3],
						 drawParent.matrixTab4[0][3] - 150,
						 drawParent.matrixTab4[1][3],
						 drawParent.matrixTab4[2][3],
						 colorWalk[0],
						 colorWalk[1],
						 colorWalk[2]);
			}
		}

		for (uint32_t boneIndex = 0; boneIndex < spookyScaryRun.skeletonBones.size(); ++boneIndex)
		{
			Matrix4 boneMatrix;
			Matrix4 drawChild = spookyScaryRun.skeletonBones[boneIndex].AnimBones(CurrentkeyCount2, deltaTime, keyCountRun);
			boneMatrix.inverse(spookyScaryRun.skeletonBones[boneIndex].worldMatrix, boneMatrix);
			boneMatrix = boneMatrix.GetTransposeMat4() * drawChild.GetTransposeMat4();

			std::memcpy(&boneMatrices2[boneIndex * 16], boneMatrix.matrixTab4, 16 * sizeof(float));
			if (spookyScaryRun.skeletonBones[boneIndex].parent != NULL)
			{
				Matrix4 drawParent = spookyScaryRun.skeletonBones[boneIndex].parent->AnimBones(CurrentkeyCount2, deltaTime, keyCountRun);
				DrawLine(drawChild .matrixTab4[0][3] + 150,
						 drawChild .matrixTab4[1][3],
						 drawChild .matrixTab4[2][3],
						 drawParent.matrixTab4[0][3] + 150,
						 drawParent.matrixTab4[1][3],
						 drawParent.matrixTab4[2][3],
						 colorRun[0],
						 colorRun[1],
						 colorRun[2]);
			}
		}

		if (ChangeAnim)
		{
			SetSkinningPose(boneMatrices.data(), boneCountWalk);
		}
		else
		{
			SetSkinningPose(boneMatrices2.data(), boneCountRun);
		}

		if (!Pause && !PlayB)
		{
			deltaTime += frame;
		}

		if (!Pause && PlayB)
		{
			deltaTime -= frame;
		}

		if (deltaTime > 1)
		{
			CurrentkeyCount++;
			CurrentkeyCount2++;
			deltaTime = 0;
		}

		if (CurrentkeyCount2 > keyCountRun - 1)
		{
			CurrentkeyCount2 = 0;
		}
		if (CurrentkeyCount > keyCountWalk - 1)
		{
			CurrentkeyCount = 0;
		}

		if (deltaTime < 0)
		{
			CurrentkeyCount--;
			CurrentkeyCount2--;
			deltaTime = 1;

			if (CurrentkeyCount2 < 0)
			{
				CurrentkeyCount2 = keyCountRun - 1;
			}
			if (CurrentkeyCount < 0)
			{
				CurrentkeyCount = keyCountWalk - 1;
			}
		}

		if (CurrentkeyCount2 < 0)
		{
			CurrentkeyCount2 = keyCountRun - 1;
		}
		if (CurrentkeyCount < 0)
		{
			CurrentkeyCount = keyCountWalk - 1;
		}
	}

	virtual void Init() override
	{
		ImGui::SetCurrentContext((ImGuiContext*)GetImGUIContext());
		keyCountWalk = GetAnimKeyCount(nameAnimWalk);
		keyCountRun = GetAnimKeyCount(nameAnimRun);

		CurrentkeyCount = 0;
		spookyScaryWalk.Init();
		spookyScaryWalk.AnimInit(nameAnimWalk);
		spookyScaryWalk.Update();

		spookyScaryRun.Init();
		spookyScaryRun.AnimInit(nameAnimRun);
		spookyScaryRun.Update();

		deltaTime = 0;
		deltaTime3 = 0;
	}

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 100, 0, 100, 100, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 100, 0, 0, 200, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 100, 0, 0, 100, 100, 0, 0, 1);
			
		UpdateImgui();
		CreateSkeleton();
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}





