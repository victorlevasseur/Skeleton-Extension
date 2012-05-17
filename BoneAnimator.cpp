#include "BoneAnimator.h"
#include "Bone.h"


Animation::Animation() : m_lastKeyFrameTime(0), m_nextKeyFrameTime(0), m_time(0), m_period(0)
{
    //ctor
}

Animation::~Animation()
{
    //dtor
}

void Animation::Restart(Bone &bone)
{
    m_time = 0;
    PrepareKeyFrame(0);
}

void Animation::Update(float timeToAdd, Bone &bone)
{
    m_time += timeToAdd;

    if(m_time > m_nextKeyFrameTime)
        PrepareKeyFrame(SearchNextKeyFrameFromTime(m_time));

    if(m_time > m_period)
    {
        m_time -= m_period;
        PrepareKeyFrame(0);
    }

    SetProgressToKeyFrame((m_time - m_lastKeyFrameTime)/(m_nextKeyFrameTime - m_lastKeyFrameTime), bone);
}

void Animation::Seek(float time, Bone &bone)
{
    m_nextKeyFrameTime = SearchLastKeyFrameFromTime(time);
    m_nextKeyFrame = m_keyFrames[time];

    PrepareKeyFrame(SearchNextKeyFrameFromTime(time));

    SetProgressToKeyFrame((time - m_lastKeyFrameTime)/(m_nextKeyFrameTime - m_lastKeyFrameTime), bone);

    m_time = time;
}

void Animation::PrepareKeyFrame(float time)
{
    m_lastKeyFrame = m_keyFrames[m_nextKeyFrameTime];
    m_lastKeyFrameTime = m_nextKeyFrameTime;
    m_nextKeyFrame = m_keyFrames[time];
    m_nextKeyFrameTime = time;
}

void Animation::SetProgressToKeyFrame(float percentage, Bone &bone)
{
    float angleToSet = m_lastKeyFrame.angle;
    angleToSet += (m_nextKeyFrame.angle - m_lastKeyFrame.angle) * percentage;

    bone.m_relativeRotation = angleToSet;
}

float Animation::SearchLastKeyFrameFromTime(float time)
{
    std::map<float, KeyFrame>::iterator it = m_keyFrames.begin();

    while(it->first <= time && it != m_keyFrames.end())
    {
        it++
    };

    if(it == m_keyFrames.end())
        return -1;

    it--;
    return it->first;
}

float Animation::SearchNextKeyFrameFromTime(float time)
{
    std::map<float, KeyFrame>::iterator it = m_keyFrames.begin();

    while(it->first < time && it != m_keyFrames.end())
    {
        it++
    };

    if(it == m_keyFrames.end())
        return -1;

    it++;
    if(it == m_keyFrames.end())
        return -1;

    return it->first;
}

BoneAnimator::BoneAnimator()
{
    //ctor
}

BoneAnimator::~BoneAnimator()
{
    //dtor
}
