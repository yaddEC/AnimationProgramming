// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Skeleton.h"
#include "Maths.h"
#include "Engine.h"
#include "Simulation.h"
#include "Keyframe.h"

class CSimulation : public ISimulation
{
	Skeleton spookyScary;
	Animation anim;
	virtual void Init() override
	{
		
		spookyScary.Init();
		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);

		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		Keyframe keyframe1;
		keyframe1.setPosition(Vector3D(posX, posY, posZ));
		keyframe1.setRotation(Quaternion(quatW, Vector3D(quatX, quatY, quatZ)));
		anim.addKeyframe(keyframe1);


		Keyframe keyframe2;
		keyframe2.setPosition(Vector3D(10, 500, 10));
		keyframe2.setRotation(Quaternion(0, Vector3D(0, 1, 0)));
		anim.addKeyframe(keyframe2);



		playFirstKeyframe(anim);
	}

	virtual void Update(float frameTime) override
	{
		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		for (int i = 0; i < 64; i++)
		{
			GetAnimLocalBoneTransform("ThirdPersonWalk.anim", i, 64, posX, posY, posZ, quatW, quatX, quatY, quatZ);
			GetSkeletonBoneLocalBindTransform(i, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		}

		
		for (uint32_t boneIndex = 0; boneIndex < spookyScary.skeletonBones.size(); ++boneIndex)
		{
			if (spookyScary.skeletonBones[boneIndex].parent != NULL)
			{
				DrawLine(spookyScary.skeletonBones[boneIndex].worldMatrix.matrixTab4[0][3]+300, spookyScary.skeletonBones[boneIndex].worldMatrix.matrixTab4[1][3], spookyScary.skeletonBones[boneIndex].worldMatrix.matrixTab4[2][3], spookyScary.skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[0][3]+300, spookyScary.skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[1][3], spookyScary.skeletonBones[boneIndex].parent->worldMatrix.matrixTab4[2][3], 0.5, 0.5, 0.5);
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

