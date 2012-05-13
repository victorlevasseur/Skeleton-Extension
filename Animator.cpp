#include "Animator.h"

Animator::Animator() : m_time(0), m_beginKeyFrame_time(-1), m_endKeyFrame_time(-1), duration(0)
{
    //ctor
}

Animator::~Animator()
{
    //dtor
}

void Animator::SetRootBone(Bone *bone)
{
    m_rootBone = bone;
    Seek(0);
}

void Animator::Update(float timeToAdd)
{
    if(m_time + timeToAdd >= m_endKeyFrame_time)
    {
        m_beginKeyFrame_time = m_endKeyFrame_time;

        std::map<float, KeyFrame>::iterator it = m_keyFrames.begin();
        while(it->first <= m_beginKeyFrame_time) it++;

        m_endKeyFrame_time = it != m_keyFrames.end() ? it->first : duration;
    }
    m_time += timeToAdd;
    while(m_time >= duration) m_time =- duration;

    ApplyKeyFrame(m_keyFrames[m_beginKeyFrame_time], (m_endKeyFrame_time - m_time) / (m_endKeyFrame_time - m_beginKeyFrame_time), m_keyFrames[m_endKeyFrame_time != duration ? m_endKeyFrame_time : 0]);
}

void Animator::Seek(float time)
{
    std::map<float, KeyFrame>::iterator it = m_keyFrames.begin();
    while (it->first <= time)
    {
        ApplyKeyFrame(it->second);
        m_beginKeyFrame_time = it->first;
        m_endKeyFrame_time = (++it) != m_keyFrames.end() ? it->first : duration;
    }

    m_time = time;
    while(m_time >= duration) m_time =- duration;
    ApplyKeyFrame(m_keyFrames[m_beginKeyFrame_time], (m_endKeyFrame_time - m_time) / (m_endKeyFrame_time - m_beginKeyFrame_time), m_keyFrames[m_endKeyFrame_time != duration ? m_endKeyFrame_time : 0]);
}

void Animator::ApplyKeyFrame(KeyFrame &frame)
{

}

void Animator::ApplyKeyFrame(KeyFrame &frame, float progress, KeyFrame &frameEnd)
{

}
