#include "skeletonanimator.h"

#include "Bone.h"
#include "GDL/CommonTools.h"

Animation::Animation() : m_period(10), m_autoRepeat(true)
{
    Reset();
}

Animation::~Animation()
{

}

#include <wx/log.h>

void Animation::UpdateTime(float timeToAdd)
{
    m_time += timeToAdd;

    if(m_time >= m_period)
    {
        m_time -= m_period;
    }

    std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin();
    for(; it != m_keyFrames.end(); it++)
    {
        if(it->second.keyFrames.size() == 0)
            continue;

        TimeFloat key = it->second.keyFrames.at(it->second.currentIndex);
        if(m_period == 0)
        {
            it->second.tmp_angleValue = key.value;
            continue;
        }

        TimeFloat nextKey = it->second.keyFrames.at(GetNextIndex(it->first, it->second.currentIndex));

        while(((m_time > nextKey.time) && (key.time <= nextKey.time)) ||
              ((key.time > nextKey.time) && (m_time > nextKey.time) && (m_time < key.time)))
        {
            it->second.currentIndex = GetNextIndex(it->first, it->second.currentIndex);
            key = nextKey;

            nextKey = it->second.keyFrames.at(GetNextIndex(it->first, it->second.currentIndex));
        }

        it->second.progress = GetTimeDelta(key, nextKey) != 0 ? ((((m_time > key.time) ? m_time - key.time : m_time + m_period - key.time)) / GetTimeDelta(key, nextKey)) : 1;

        it->second.tmp_angleValue = (nextKey.value - key.value) * it->second.progress + key.value;
    }
}

float Animation::GetTimeDelta(const TimeFloat &frame1, const TimeFloat &frame2)
{
    return frame1.time <= frame2.time ? frame2.time - frame1.time : frame2.time + m_period - frame1.time;
}

int Animation::GetNextIndex(const std::string &boneName, int index)
{
    if(index < GetBoneKeyFrames(boneName).size() - 1)
    {
        index++;
        return index;
    }
    else
    {
        return 0;
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
        if(m_keyFrames.count(boneVec[a]->GetName()) == 0)
            continue;

        boneVec[a]->m_relativeRotation = m_keyFrames[boneVec[a]->GetName()].tmp_angleValue;
    }
}

SkeletonAnimator::SkeletonAnimator() : m_currentAnimation("Initial")
{
    //ctor
    CreateAnimation("Initial");
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
    m_animations[newName] = m_animations[name];
    DeleteAnimation(name);
}

void SkeletonAnimator::DeleteAnimation(const std::string &name)
{
    m_animations.erase(name);
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
