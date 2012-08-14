#ifndef SKELETONANIMATOR_H
#define SKELETONANIMATOR_H

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "GDL/tinyxml/tinyxml.h"

namespace Sk
{

class Bone;

/**
Anim namespace contains all stuff related to the animation system for skeletons.
 */
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

/**
This class stores all keyframes for one bone in an animation. The class also contains temporary values for the progress of each bones.
 */
class BoneAnimation
{
    public:

    BoneAnimation()
    {
        keyFrames[AngleKeyFrame].push_back(TimeFloat());

        TimeFloat lengthTimeFloat;
        lengthTimeFloat.time = 0;
        lengthTimeFloat.value = 100;
        keyFrames[LengthKeyFrame].push_back(TimeFloat());
    };

    std::map<KeyFrameType, unsigned int> currentIndex;

    std::map<KeyFrameType, float> tmp_angleValue;
    std::map<KeyFrameType, float> progress;

    std::map<KeyFrameType, std::vector<TimeFloat> > keyFrames;
};

/**
This class represents an animations. It manages all calculations for each bones and contains a map of BoneAnimation (each linked to one bone). The class contains methods to edit keyframes.
 */
class Animation
{
    friend class Sk::Bone;

    public:
        Animation();
        virtual ~Animation();

        void Reset();

        void UpdateTime(float timeToAdd);
        void Seek(float time);

        float GetPeriod() const {return m_period;};
        void SetPeriod(float value) {m_period = value;};

        void SetKeyFrame(const std::string &boneName, KeyFrameType type, TimeFloat &keyframe);
        void SetKeyFrame(const std::string &boneName, KeyFrameType type, float time, float value);
        bool HasKeyFrame(const std::string &boneName, KeyFrameType type, float time);
        void RemoveKeyFrame(const std::string &boneName, KeyFrameType type, float time);
        void ClearKeyFrame(const std::string &boneName, KeyFrameType type);

        std::string GetKeyFrameInterpolation(const std::string &boneName, KeyFrameType type, float time);
        void SetKeyFrameInterpolation(const std::string &boneName, KeyFrameType type, float time, const std::string &method);

        /// Don't forget to call ReorderKeys(const std::string &boneName); after modifying a bone keyframes list.
        inline const std::vector<TimeFloat>& GetBoneKeyFrames(const std::string &boneName, KeyFrameType type);
        void ReorderKeys(const std::string &boneName);

        std::vector<float> GetListOfKeyFramesTime(const std::string &bone = "", KeyFrameType type = AnyKeyFrame);

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

        void LoadFromXml(TiXmlElement *ele);
        void SaveToXml(TiXmlElement *ele);

    private:
        int GetNextIndex(const std::string &boneName, KeyFrameType type, unsigned int index);
        float GetTimeDelta(const TimeFloat &frame1, const TimeFloat &frame2);

        void UpdateTimeOfSmoothedType(float timeToAdd, KeyFrameType type);
        void SeekOfSmoothedType(float time, KeyFrameType type);

        float m_time;
        float m_period;
        bool m_autoRepeat;
        std::map<std::string, BoneAnimation> m_keyFrames;
};

/**
This class manages all animations for a skeleton.
 */
class SkeletonAnimator
{
    public:
        SkeletonAnimator();
        virtual ~SkeletonAnimator();

        inline Animation& GetAnimation(const std::string &name);

        const std::string& GetCurrentAnimation() const;
        void SetCurrentAnimation(const std::string &animName);

        void CreateAnimation(const std::string &name, const std::string &asACopyOf = std::string());
        void RenameAnimation(const std::string &name, const std::string &newName);
        void DeleteAnimation(const std::string &name);

        std::vector<std::string> GetListOfAnimations() const;

        void UpdateTime(float timeToAdd);
        void Seek(float time);
        void Reset();

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

        void LoadFromXml(TiXmlElement *ele);
        void SaveToXml(TiXmlElement *ele);

    protected:
    private:
        std::map<std::string, Animation> m_animations;
        std::string m_currentAnimation;
};

class TimeOrderFunctor : public std::binary_function<TimeFloat, TimeFloat, bool>
{
    public:
        bool operator() (TimeFloat left, TimeFloat right) {return (left.time < right.time);};
};

inline Animation& SkeletonAnimator::GetAnimation(const std::string &name)
{
    return m_animations[name];
}

inline const std::vector<TimeFloat>& Animation::GetBoneKeyFrames(const std::string &boneName, KeyFrameType type)
{
    return m_keyFrames[boneName].keyFrames[type];
}

}

}

#endif // SKELETONANIMATOR_H
