#pragma once
#include "Maths.h"
#include <iostream>
#include <vector>
#include <map>

using namespace Math;

class Keyframe
{
public:
    // Constructor
    Keyframe() {}

    // Set the position of the keyframe
    void setPosition(Vector3D position) { this->position = position; }

    // Get the position of the keyframe
    Vector3D getPosition() { return position; }

    // Set the rotation of the keyframe
    void setRotation(Quaternion rotation) { this->rotation = rotation; }

    // Get the rotation of the keyframe
    Quaternion getRotation() { return rotation; }

    // Play the keyframe
    void play()
    {
        // Set the position and rotation of the animated objects
        // to the values stored in this keyframe
        setPosition(position);
        setRotation(rotation);
    }

    // Position of the keyframe
    Vector3D position;

    // Rotation of the keyframe
    Quaternion rotation;
};

class Animation
{
public:
    // Constructor
    Animation() {}

    // Add a keyframe to the animation
    void addKeyframe(Keyframe keyframe) { keyframes.push_back(keyframe); }

    // Get a keyframe at a specific index
    Keyframe* getKeyframe(int index) { return &keyframes[index]; }

    // Play the animation
    void play()
    {
        // Loop through all keyframes and play them in order
        for (Keyframe& keyframe : keyframes)
        {
            keyframe.play();
        }
    }

private:
    // Vector of keyframes
    std::vector<Keyframe> keyframes;
};

void playFirstKeyframe(Animation& anim)
{
    // Get the first keyframe

    Keyframe* keyframe = anim.getKeyframe(0);

    // Play the keyframe
    keyframe->play();
}



