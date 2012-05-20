#ifndef SKELETONANIMATOR_H
#define SKELETONANIMATOR_H

#include <vector>
#include <map>

struct TimeFloat
{
    float time;
    float value;
};

struct Timeline
{
    float period;
    std::vector<TimeFloat> keyFrames;
};

class Animation
{
    friend class Bone;

    public:
        Animation();
        virtual ~Animation();

    private:
        std::map<std::string, TimeLine> m_keyFrames;
};

class SkeletonAnimator
{
    public:
        SkeletonAnimator();
        virtual ~SkeletonAnimator();

        Animation& GetAnimation(const std::string &name);

        void CreateAnimation(const std::string &name);
        void RenameAnimation(const std::string &name, const std::string &newName);
        void DeleteAnimation(const std::string &name);

    protected:
    private:
        std::map<std::string, Animation> m_animations;
};

#endif // SKELETONANIMATOR_H
