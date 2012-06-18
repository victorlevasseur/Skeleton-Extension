#ifndef SKELETONANIMATOR_H
#define SKELETONANIMATOR_H

#include <vector>
#include <map>
#include <string>
#include <algorithm>

class Bone;

struct TimeFloat
{
    TimeFloat() : time(0), value(0) {};

    float time;
    float value;
};

class BoneAnimation
{
    public:

    BoneAnimation() : currentIndex(0), tmp_angleValue(0), progress(0)
    {
        keyFrames.push_back(TimeFloat());
    };

    unsigned int currentIndex;

    float tmp_angleValue;
    float progress;

    std::vector<TimeFloat> keyFrames;
};

class Animation
{
    friend class Bone;

    public:
        Animation();
        virtual ~Animation();

        void UpdateTime(float timeToAdd);
        void Seek(float time);
        void Reset();

        float GetPeriod() const {return m_period;};
        void SetPeriod(float value) {m_period = value;};

        void SetKeyFrame(const std::string &boneName, TimeFloat &keyframe);
        void SetKeyFrame(const std::string &boneName, float time, float value);

        /// Don't forget to call ReorderKeys(const std::string &boneName); after modifying a bone keyframes list.
        inline const std::vector<TimeFloat>& GetBoneKeyFrames(const std::string &boneName);
        void ReorderKeys(const std::string &boneName);

        std::vector<float> GetListOfKeyFramesTime(const std::string &bone = "") const;

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

    private:
        int GetNextIndex(const std::string &boneName, unsigned int index);
        float GetTimeDelta(const TimeFloat &frame1, const TimeFloat &frame2);

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

        void CreateAnimation(const std::string &name);
        void RenameAnimation(const std::string &name, const std::string &newName);
        void DeleteAnimation(const std::string &name);

        std::vector<std::string> GetListOfAnimations() const;

        void UpdateTime(float timeToAdd);
        void Seek(float time);
        void Reset();

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

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

inline const std::vector<TimeFloat>& Animation::GetBoneKeyFrames(const std::string &boneName)
{
    return m_keyFrames[boneName].keyFrames;
}

#endif // SKELETONANIMATOR_H
