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

}

}

#endif
