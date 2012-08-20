#include "boneanimation.h"

#include "timefloat.h"

namespace Sk
{

namespace Anim
{

BoneAnimation::BoneAnimation()
{
    keyFrames[AngleKeyFrame].push_back(KeyFrame());

    KeyFrame lengthTimeFloat;
    lengthTimeFloat.time = 0;
    lengthTimeFloat.value = 100;
    keyFrames[LengthKeyFrame].push_back(KeyFrame());
};

}

}
