#include "skeletonanimator.h"

#include "Bone.h"

Animation::Animation() : m_period(10), m_autoRepeat(true)
{

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

std::vector<TimeFloat>& Animation::GetBoneKeyFrames(const std::string &boneName)
{

}

void Animation::ApplyToSkeleton(std::vector<Bone*> &boneVec)
{

}

SkeletonAnimator::SkeletonAnimator()
{
    //ctor
}

SkeletonAnimator::~SkeletonAnimator()
{
    //dtor
}
