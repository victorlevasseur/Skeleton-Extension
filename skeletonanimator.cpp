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

void Animation::SetKeyFrame(const std::string &boneName, TimeFloat &keyframe)
{
    for(unsigned int a = 0; a < m_keyFrames[boneName].keyFrames.size(); a++)
    {
        if(m_keyFrames[boneName].keyFrames[a].time == keyframe.time)
        {
            m_keyFrames[boneName].keyFrames[a] = keyframe;
            ReorderKeys(boneName);
            return;
        }
    }

    m_keyFrames[boneName].keyFrames.push_back(keyframe);
    ReorderKeys(boneName);
}

void Animation::SetKeyFrame(const std::string &boneName, float time, float value)
{
    TimeFloat timefloat;
    timefloat.time = time;
    timefloat.value = value;

    SetKeyFrame(boneName, timefloat);
}

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

int Animation::GetNextIndex(const std::string &boneName, unsigned int index)
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

void Animation::NotifyBoneRenamed(const std::string &oldName, const std::string &newName)
{
    if(m_keyFrames.count(oldName) == 0)
        return;

    m_keyFrames[newName] = BoneAnimation(m_keyFrames[oldName]);
    m_keyFrames.erase(oldName);
}

void Animation::ReorderKeys(const std::string &boneName)
{
    std::sort(m_keyFrames[boneName].keyFrames.begin(), m_keyFrames[boneName].keyFrames.end(), TimeOrderFunctor());
}

std::vector<float> Animation::GetListOfKeyFramesTime(const std::string &bone) const
{
    std::vector<float> listOfKeys;

    if(bone == "")
    {
        for(std::map<std::string, BoneAnimation>::const_iterator it = m_keyFrames.begin(); it != m_keyFrames.end(); it++)
        {
            for(unsigned int a = 0; a < it->second.keyFrames.size(); a++)
            {
                listOfKeys.push_back(it->second.keyFrames.at(a).time);
            }
        }
    }
    else
    {
        for(unsigned int a = 0; a < m_keyFrames.at(bone).keyFrames.size(); a++)
        {
            listOfKeys.push_back(m_keyFrames.at(bone).keyFrames.at(a).time);
        }
    }

    std::sort(listOfKeys.begin(), listOfKeys.end());
    std::vector<float>::iterator lastEle = std::unique(listOfKeys.begin(), listOfKeys.end());
    listOfKeys.resize(lastEle - listOfKeys.begin());

    return listOfKeys;
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

std::vector<std::string> SkeletonAnimator::GetListOfAnimations() const
{
    std::vector<std::string> animations;

    for(std::map<std::string, Animation>::const_iterator it = m_animations.begin(); it != m_animations.end(); it++)
    {
        animations.push_back(it->first);
    }

    return animations;
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

void SkeletonAnimator::NotifyBoneRenamed(const std::string &oldName, const std::string &newName)
{
    if(oldName == newName)
    {
        return;
    }

    for(std::map<std::string, Animation>::iterator it = m_animations.begin(); it != m_animations.end(); it++)
    {
        it->second.NotifyBoneRenamed(oldName, newName);
    }
}
