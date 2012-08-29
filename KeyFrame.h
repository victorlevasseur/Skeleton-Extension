/*
Copyright (C) 2012 Victor Levasseur

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
  */

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
struct KeyFrame
{
    KeyFrame() : time(0), value(0), valueStr(""), interpolation("Linear") {};

    float time; ///< Time (position) of the keyframe in the animation's timeline
    float value; ///< Value associated with the keyframe (can be an angle, a length, depending of the keyframe type)
    std::string valueStr; ///< Value associated with the keyframe as string (can be an image name...)

    std::string interpolation; ///< Interpolation method (as std::string representing its name) used from this keyframe to the next (of the same type)
};

}

}

#endif
