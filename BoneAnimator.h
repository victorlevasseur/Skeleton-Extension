#ifndef BONEANIMATOR_H
#define BONEANIMATOR_H

#include <string>
#include <vector>
#include <map>

struct KeyFrame
{
    float angle;
};

class Bone;

class Animation
{
    public:
        Animation();
        ~Animation();

        void Restart(Bone &bone);
        void Update(float timeToAdd, Bone &bone);
        void Seek(float time, Bone &bone);

    protected:
    private:

        void PrepareKeyFrame(float time); //Prepare next key frame
        void SetProgressToKeyFrame(float percentage, Bone &bone);

        float SearchLastKeyFrameFromTime(float time);
        float SearchNextKeyFrameFromTime(float time);

        KeyFrame m_lastKeyFrame;
        KeyFrame m_nextKeyFrame;
        float m_lastKeyFrameTime;
        float m_nextKeyFrameTime;

        float m_time;
        float m_period;
        std::map<float, KeyFrame> m_keyFrames;
};

class BoneAnimator
{
    public:
        BoneAnimator();
        virtual ~BoneAnimator();

        void SetAnimation(const std::string &animation);

        void RestartAnimation(Bone &bone);
        void Update(float timeToAdd, Bone &bone);
        void Seek(float time, Bone &bone);

    protected:
    private:

        std::map<std::string, Animation> m_animations;
        std::string m_currentAnimation;
};

#endif // BONEANIMATOR_H
