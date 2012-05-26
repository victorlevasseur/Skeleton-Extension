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
    /*if(m_time >= m_period)
        m_time -= m_period;*/

    std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin();
    for(; it != m_keyFrames.end(); it++)
    {
        if(it->second.keyFrames.size() == 0)
            continue;

        TimeFloat key = it->second.keyFrames.at(it->second.currentIndex);

        if(key.time >= m_time - it->second.beforeIndexTime)
        {
            it->second.currentIndex = GetNextIndex(it->first, it->second.currentIndex);
            it->second.beforeIndexTime += key.time;
            key = it->second.keyFrames.at(it->second.currentIndex);
        }

        int nextIndex(GetNextIndex(it->first, it->second.currentIndex));
        TimeFloat nextKey = it->second.keyFrames.at(nextIndex);

        it->second.progress = key.time != 0 ? (m_time - it->second.beforeIndexTime) / key.time : 1;
        it->second.tmp_angleValue = (nextKey.value - key.value) * it->second.progress + key.value;
    }
}

int Animation::GetNextIndex(const std::string &boneName, int index)
{
    if(index < GetBoneKeyFrames(boneName).size() - 1)
    {
        return ++index;
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
    /*if(time >= m_time)
    {
        UpdateTime(time - m_time);
    }
    else
    {
        UpdateTime(m_period - m_time + time);
    }*/
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
