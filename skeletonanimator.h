#ifndef SKELETONANIMATOR_H
#define SKELETONANIMATOR_H

#include <vector>
#include <map>
#include <string>

class Bone;

struct TimeFloat
{
    float time;
    float value;
};

struct BoneAnimation
{
    unsigned int currentIndex;
    unsigned int nextIndex;
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

        inline std::vector<TimeFloat>& GetBoneKeyFrames(const std::string &boneName);

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

    private:
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

        void UpdateTime(float timeToAdd);
        void Seek(float time);
        void Reset();

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

    protected:
    private:
        std::map<std::string, Animation> m_animations;
        std::string m_currentAnimation;
};

inline Animation& SkeletonAnimator::GetAnimation(const std::string &name)
{
    return m_animations[name];
}

inline std::vector<TimeFloat>& Animation::GetBoneKeyFrames(const std::string &boneName)
{
    return m_keyFrames[boneName].keyFrames;
}

#endif // SKELETONANIMATOR_H
