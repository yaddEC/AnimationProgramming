// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Skeleton.h"
#include "Maths.h"
#include "Engine.h"
#include "Simulation.h"

class CSimulation : public ISimulation
{
	size_t keyCount;
	Skeleton spookyScary;
	std::vector<Matrix4> skinningMatrices;
	std::vector<Matrix4> indetittys;
	float deltaTime;
	float deltaTime2;
	virtual void Init() override
	{
		keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		spookyScary.Init();
		spookyScary.AnimInit();
		spookyScary.Update();
		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);
		
		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		deltaTime = 2;
	}

	void inverse(const Matrix4 in, Matrix4& out) {
		float a00 =  in.matrixTab16[0],  a01 =  in.matrixTab16[1], a02 =  in.matrixTab16[2], a03 =  in.matrixTab16[3];
		float a10 =  in.matrixTab16[4],  a11 =  in.matrixTab16[5], a12 =  in.matrixTab16[6], a13 =  in.matrixTab16[7];
		float a20 =  in.matrixTab16[8],  a21 =  in.matrixTab16[9], a22 =  in.matrixTab16[10], a23 =  in.matrixTab16[11];
		float a30 =  in.matrixTab16[12], a31 =  in.matrixTab16[13], a32 =  in.matrixTab16[14], a33 =  in.matrixTab16[15];

		float b00 = a00 * a11 - a01 * a10;
		float b01 = a00 * a12 - a02 * a10;
		float b02 = a00 * a13 - a03 * a10;
		float b03 = a01 * a12 - a02 * a11;
		float b04 = a01 * a13 - a03 * a11;
		float b05 = a02 * a13 - a03 * a12;
		float b06 = a20 * a31 - a21 * a30;
		float b07 = a20 * a32 - a22 * a30;
		float b08 = a20 * a33 - a23 * a30;
		float b09 = a21 * a32 - a22 * a31;
		float b10 = a21 * a33 - a23 * a31;
		float b11 = a22 * a33 - a23 * a32;

		float det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

		if (std::abs(det) <= std::numeric_limits<float>::epsilon()) {
			return;
		}

		det = 1.0f / det;

		out.matrixTab16[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
		out.matrixTab16[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
		out.matrixTab16[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
		out.matrixTab16[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
		out.matrixTab16[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
		out.matrixTab16[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
		out.matrixTab16[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;

		out.matrixTab16[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
		out.matrixTab16[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
		out.matrixTab16[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
		out.matrixTab16[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
		out.matrixTab16[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
		out.matrixTab16[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
		out.matrixTab16[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
		out.matrixTab16[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
		out.matrixTab16[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
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
			Matrix4 drawChild = spookyScary.skeletonBones[boneIndex].AnimBones(deltaTime);
			Matrix4 boneMatrix;
			inverse(spookyScary.skeletonBones[boneIndex].worldMatrix, boneMatrix);
			boneMatrix = boneMatrix.GetTransposeMat4() * drawChild.GetTransposeMat4();

			std::memcpy(&boneMatrices[boneIndex * 16], boneMatrix.matrixTab4, 16 * sizeof(float));
			if (spookyScary.skeletonBones[boneIndex].parent != NULL)
			{
				Matrix4 drawParent = spookyScary.skeletonBones[boneIndex].parent->AnimBones(deltaTime);
				DrawLine(drawChild .matrixTab4[0][3] - 100,
						 drawChild .matrixTab4[1][3],
						 drawChild .matrixTab4[2][3],
						 drawParent.matrixTab4[0][3] - 100, 
						 drawParent.matrixTab4[1][3], 
						 drawParent.matrixTab4[2][3], 
						 0.5, 
						 0.5,
						 0.5);
			}

		}

		SetSkinningPose(boneMatrices.data(), boneCount);
		
		deltaTime2++;
		if (deltaTime2 > 20)
		{
			deltaTime2 = 0;
			deltaTime++;
		}
		if (deltaTime > keyCount - 1)
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





