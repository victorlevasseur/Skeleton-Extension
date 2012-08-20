#ifndef SKBONEANIM_H
#define SKBONEANIM_H

#include <vector>
#include <map>
#include "globaldefs.h"

namespace Sk{namespace Anim{struct KeyFrame;}}

namespace Sk
{

namespace Anim
{

/**
This class stores all keyframes for one bone in an animation. The class also contains temporary values for the progress of each bones.
 */
class BoneAnimation
{
    public:

    BoneAnimation();

    std::map<KeyFrameType, unsigned int> currentIndex;

    std::map<KeyFrameType, float> tmp_angleValue;
    std::map<KeyFrameType, float> progress;

    std::map<KeyFrameType, std::vector<KeyFrame> > keyFrames;
};

}

}

#endif
