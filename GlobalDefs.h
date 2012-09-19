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

#ifndef SKGLOBALDEFS_H
#define SKGLOBALDEFS_H

namespace Sk
{

namespace Anim
{
/**
Identified keyframes related to the different properties of bones.
 */
enum KeyFrameType
{
    AngleKeyFrame = 0, /**< Keyframe related to angle */
    LengthKeyFrame = 1, /**< Length keyframe */
    PositionXKeyFrame = 2, /**< X offset keyframe */
    PositionYKeyFrame = 3, /**< Y offset keyframe (keyframes for X and Y offset are defined in the same time but are stored separatly)*/
    ImageKeyFrame = 4, /**< Image keyframe */
    ZOrderKeyFrame = 5, /**< Z-Order keyframe */

    AnyKeyFrame = 1000 /**< Used to represents all keyframes types in some methods*/
};

typedef int KeyFrameTypes;

}

}

#endif
