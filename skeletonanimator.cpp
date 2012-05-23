#include "skeletonanimator.h"

#include "Bone.h"

Animation::Animation() : m_period(10), m_autoRepeat(true)
{
    Reset();
}

Animation::~Animation()
{

}

void Animation::UpdateTime(float timeToAdd)
{
    m_time += timeToAdd;
    if(m_time >= m_period)
        m_time -= m_period;

    std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin();
    for(; it != m_keyFrames.end(); it++)
    {
        //Update each bone keyframes
        if(m_time > it->second.keyFrames.at(it->second.nextIndex).time && it->second.nextIndex != 0)
        {
            it->second.currentIndex++;
            it->second.nextIndex++;

            if(it->second.nextIndex >= m_keyFrames.size())
            {
                if(m_autoRepeat)
                    it->second.nextIndex = 0;
                else
                    /* TODO : STOP ANIMATION*/;
            }
        }
        else if(m_time > it->second.keyFrames.at(it->second.nextIndex).time && it->second.nextIndex == 0)
        {
            it->second.currentIndex = 0;
            it->second.nextIndex++;

            if(it->second.nextIndex >= m_keyFrames.size())
            {
                it->second.nextIndex = 0;
            }
        }

        //Processing progression
        if(it->second.keyFrames.at(it->second.nextIndex).time < it->second.keyFrames.at(it->second.currentIndex).time)
            it->second.progress = (m_time - it->second.keyFrames.at(it->second.currentIndex).time) / (it->second.keyFrames.at(it->second.nextIndex).time - it->second.keyFrames.at(it->second.currentIndex).time);
        else if(it->second.keyFrames.at(it->second.nextIndex).time > it->second.keyFrames.at(it->second.currentIndex).time && m_time > it->second.keyFrames.at(it->second.currentIndex).time)
            it->second.progress = (m_time - it->second.keyFrames.at(it->second.currentIndex).time) / (it->second.keyFrames.at(it->second.nextIndex).time - it->second.keyFrames.at(it->second.currentIndex).time + m_period);
        else if(it->second.keyFrames.at(it->second.nextIndex).time > it->second.keyFrames.at(it->second.currentIndex).time)
            it->second.progress = (m_time - (it->second.keyFrames.at(it->second.currentIndex).time - m_period)) / (it->second.keyFrames.at(it->second.nextIndex).time - (it->second.keyFrames.at(it->second.currentIndex).time - m_period));
    }
}

void Animation::Reset()
{
    Seek(m_period - m_time);
}

void Animation::Seek(float time)
{
    if(time >= m_time)
    {
        UpdateTime(time - m_time);
    }
    else
    {
        UpdateTime(m_period - m_time + time);
    }
}

void Animation::ApplyToSkeleton(std::vector<Bone*> &boneVec)
{
    for(unsigned int a = 0; a < boneVec.size(); a++)
    {
        float angleValue;
        angleValue = GetBoneKeyFrames(boneVec.at(a)->GetName()).at(m_keyFrames[boneVec.at(a)->GetName()].currentIndex).value + m_keyFrames[boneVec.at(a)->GetName()].progress * (GetBoneKeyFrames(boneVec.at(a)->GetName()).at(m_keyFrames[boneVec.at(a)->GetName()].nextIndex).value - GetBoneKeyFrames(boneVec.at(a)->GetName()).at(m_keyFrames[boneVec.at(a)->GetName()].currentIndex).value);
        boneVec.at(a)->m_relativeRotation = angleValue;
    }
}

SkeletonAnimator::SkeletonAnimator() : m_currentAnimation("")
{
    //ctor
    CreateAnimation("");
}

SkeletonAnimator::~SkeletonAnimator()
{
    //dtor
}

const std::string& SkeletonAnimator::GetCurrentAnimation() const
{
    return m_currentAnimation;
}

void SkeletonAnimator::SetCurrentAnimation(const std::string &animName)
{
    m_currentAnimation = animName;
    GetAnimation(m_currentAnimation).Reset();
}

void SkeletonAnimator::CreateAnimation(const std::string &name)
{
    m_animations[name] = Animation();
}

void SkeletonAnimator::RenameAnimation(const std::string &name, const std::string &newName)
{

}

void SkeletonAnimator::DeleteAnimation(const std::string &name)
{

}

void SkeletonAnimator::UpdateTime(float timeToAdd)
{
    GetAnimation(m_currentAnimation).UpdateTime(timeToAdd);
}

void SkeletonAnimator::Seek(float time)
{
    GetAnimation(m_currentAnimation).Seek(time);
}

void SkeletonAnimator::Reset()
{
    GetAnimation(m_currentAnimation).Reset();
}

void SkeletonAnimator::ApplyToSkeleton(std::vector<Bone*> &boneVec)
{
    GetAnimation(m_currentAnimation).ApplyToSkeleton(boneVec);
}
