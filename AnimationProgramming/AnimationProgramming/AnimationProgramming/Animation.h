#pragma once
#include "Maths.h"
#include "Skeleton.h"
#include "Engine.h"
#include "Bone.h"
#include <vector>

class Animation
{
public:
    // Constructor
    Animation() {}
    void Init(Skeleton skel);
    void Play();
    std::vector<Skeleton> animation;
private:
    // Vector of keyframes
};



