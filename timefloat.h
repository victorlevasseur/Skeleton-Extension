#ifndef SKTIMEFLOAT_H
#define SKTIMEFLOAT_H

#include <string>

namespace Sk
{

namespace Anim
{

/**
Represents a keyframe for one bone.
It's a combination of a time, a value and an interpolation method.
 */
struct TimeFloat
{
    TimeFloat() : time(0), value(0), interpolation("Linear") {};

    float time; ///< Time (position) of the keyframe in the animation's timeline
    float value; ///< Value associated with the keyframe (can be an angle, a length, depending of the keyframe type)

    std::string interpolation; ///< Interpolation method (as std::string representing its name) used from this keyframe to the next (of the same type)
};

}

}

#endif
