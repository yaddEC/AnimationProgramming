// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Maths.h"
#include "Simulation.h"
#include <cstdint>

class CSimulation : public ISimulation
{
	virtual void Init() override
	{
		//int spine01 =	GetSkeletonBoneIndex("spine_01");
		//int spineParent = GetSkeletonBoneParentIndex(spine01);
		//const char* spineParentName = GetSkeletonBoneName(spineParent);

		//float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		//size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		//GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		//printf("Spine parent bone : %s\n", spineParentName);
		//printf("Anim key count : %ld\n", keyCount);
		//printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
		//printf("Bone Count : % ld\n", GetSkeletonBoneCount());
		for (uint32_t boneIndex = 0; boneIndex < GetSkeletonBoneCount(); ++boneIndex)
		{
			float x1, y1, z1, qx1, qy1, qz1, qw1;
			GetSkeletonBoneLocalBindTransform(static_cast<int>(boneIndex), x1, y1, z1, qw1, qx1, qy1, qz1);
			GetSkeletonBoneName(boneIndex);
			printf("%s : % f,% f,% f\n", GetSkeletonBoneName(boneIndex), x1,y1,z1);

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
		float x, y, z, qx, qy, qz, qw;
		for (uint32_t boneIndex = 0; boneIndex < GetSkeletonBoneCount(); ++boneIndex)
		{
			float x1, y1, z1, qx1, qy1, qz1, qw1;
			GetSkeletonBoneLocalBindTransform(static_cast<int>(boneIndex), x1, y1, z1, qw1, qx1, qy1, qz1);

			Matrix4 mat4;
			Vector3D test5 = quaternion(qw1, Vector3D (qx1,qy1,qz1)).transformQuaternionToEulerAngles();
			mat4 = mat4.CreateTransformMatrix(test5, { x1, y1, z1 }, { 1,1,1 });
			Vector4D pos4d = (Vector4D(1, 1, 1, 1) * mat4); pos4d.Homogenize();
			Vector3D pos = { pos4d.x, pos4d.y, pos4d.z };

			//test3.normalize();
			if (boneIndex != 0)
			{
				DrawLine(pos.x, pos.y, pos.z, pos.x+1, pos.y+1, pos.z+1, 0, 0, 1);
			}

	
			
		}

	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

