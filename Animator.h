#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <map>
#include <string>
#include "Bone.h"

struct BoneState
{
    float angle;
    float size;
};

struct KeyFrame
{
    std::map<std::string, BoneState> bones;
};

class Animator
{
    public:
        Animator();
        ~Animator();

        void SetRootBone(Bone *bone);

        void Update(float timeToAdd);
        void Seek(float time);

    protected:
    private:

        void ApplyKeyFrame(KeyFrame &frame);
        void ApplyKeyFrame(KeyFrame &frame, float progress, KeyFrame &frameEnd);

        Bone *m_rootBone;
        float m_time;

        std::map<float, KeyFrame> m_keyFrames;
        float m_beginKeyFrame_time;
        float m_endKeyFrame_time;

        float duration;
};

#endif // ANIMATOR_H
