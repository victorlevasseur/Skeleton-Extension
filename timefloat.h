#ifndef SKTIMEFLOAT_H
#define SKTIMEFLOAT_H

#include <string>

namespace Sk
{

namespace Anim
{

struct ValueStr
{
    char *v;
    //size_t s;
};

/**
Represents a keyframe for one bone.
It's a combination of a time, a value and an interpolation method.
 */
struct TimeFloat
{
    TimeFloat() : time(0), interpolation("Linear") {};

    float time; ///< Time (position) of the keyframe in the animation's timeline

    union
    {
        public:

        float value; ///< Value associated with the keyframe (can be an angle, a length, depending of the keyframe type)
        ValueStr valueStr; ///< Value as string associated with the keyframe (can be an image name)
    };

    std::string interpolation; ///< Interpolation method (as std::string representing its name) used from this keyframe to the next (of the same type)
};

/**
Get a value as string.
 */
std::string GetValueStr(ValueStr *val);

/**
Set a value as string to a ValueStr.
 */
void SetValueStr(ValueStr *val, std::string &str);

/**
Used to avoid memory leaks with ValueStr (because it can have any de/constructor)
 */
void DestroyValueStr(ValueStr *val);

}

}

#endif
