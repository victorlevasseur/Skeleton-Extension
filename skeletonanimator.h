#ifndef SKELETONANIMATOR_H
#define SKELETONANIMATOR_H

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "GDL/tinyxml/tinyxml.h"

class Bone;

enum KeyFrameType
{
    AngleKeyFrame = 0,
    LengthKeyFrame = 1,
    PositionXKeyFrame = 2,
    PositionYKeyFrame = 3
};

struct TimeFloat
{
    TimeFloat() : time(0), value(0) {};

    float time;
    float value;
};

class BoneAnimation
{
    public:

    BoneAnimation()
    {
        keyFrames[AngleKeyFrame].push_back(TimeFloat());
    };

    std::map<KeyFrameType, unsigned int> currentIndex;

    std::map<KeyFrameType, float> tmp_angleValue;
    std::map<KeyFrameType, float> progress;

    std::map<KeyFrameType, std::vector<TimeFloat> > keyFrames;
};

typedef void (Bone::*FloatMethod)(float);

class Animation
{
    friend class Bone;

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

        /// Don't forget to call ReorderKeys(const std::string &boneName); after modifying a bone keyframes list.
        inline const std::vector<TimeFloat>& GetBoneKeyFrames(const std::string &boneName, KeyFrameType type);
        void ReorderKeys(const std::string &boneName);

        std::vector<float> GetListOfKeyFramesTime(const std::string &bone = "");

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

        void LoadFromXml(TiXmlElement *ele);
        void SaveToXml(TiXmlElement *ele);

    private:
        int GetNextIndex(const std::string &boneName, KeyFrameType type, unsigned int index);
        float GetTimeDelta(const TimeFloat &frame1, const TimeFloat &frame2);

        void UpdateTimeOfType(float timeToAdd, KeyFrameType type);
        void SeekOfType(float time, KeyFrameType type);

        float m_time;
        float m_period;
        bool m_autoRepeat;
        std::map<std::string, BoneAnimation> m_keyFrames;
};

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

#endif // SKELETONANIMATOR_H
