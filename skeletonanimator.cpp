#include "skeletonanimator.h"

Animation::Animation()
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
        if(m_time > it->keyFrames.at(it->nextIndex).time && it->nextIndex != 0)
        {
            it->currentIndex++;
            it->nextIndex++;

            if(it->nextIndex >= m_keyFrames.size())
            {
                it->nextIndex = 0;
            }
        }
        else if(m_time > it->keyFrames.at(it->nextIndex).time && it->nextIndex == 0)
        {
            it->currentIndex = 0;
            it->nextIndex++;

            if(it->nextIndex >= m_keyFrames.size())
            {
                it->nextIndex = 0;
            }
        }

        //it->progress = it->nextIndex
    }
}

void Animation::Seek(float time)
{

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
