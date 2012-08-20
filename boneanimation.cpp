#include "boneanimation.h"

#include "timefloat.h"

namespace Sk
{

namespace Anim
{

BoneAnimation::BoneAnimation()
{
    keyFrames[AngleKeyFrame].push_back(TimeFloat());

    TimeFloat lengthTimeFloat;
    lengthTimeFloat.time = 0;
    lengthTimeFloat.value = 100;
    keyFrames[LengthKeyFrame].push_back(TimeFloat());
};

}

}
