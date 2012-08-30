/*
Copyright (C) 2012 Victor Levasseur

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
  */

#include "SkeletonAnimator.h"

#include "GDL/tinyxml/tinyxml.h"
#include "GDL/CommonTools.h"

#include "Bone.h"
#include "InterpolationMethods.h"
#include "ImageManager.h"

namespace Sk
{

namespace Anim
{

SkeletonAnimator::SkeletonAnimator() : m_currentAnimation("Initial"), m_isRunning(true), m_isStopped(false), m_speedRatio(1.f), m_computationsDelay(0.f), m_tmpTime(0.f)
{
    //ctor
    CreateAnimation("Initial");
}

SkeletonAnimator::~SkeletonAnimator()
{
    //dtor
}

const std::string& SkeletonAnimator::GetCurrentAnimationName() const
{
    return m_currentAnimation;
}

void SkeletonAnimator::SetCurrentAnimationName(const std::string &animName)
{
    Stop();
    m_currentAnimation = animName;
    GetAnimation(m_currentAnimation).Reset();
    Play();
}

void SkeletonAnimator::CreateAnimation(const std::string &name, const std::string &asACopyOf)
{
    if(asACopyOf != "")
        m_animations[name] = Animation(m_animations[asACopyOf]);
    else
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

std::vector<std::string> SkeletonAnimator::GetAnimations() const
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
    if(!m_isRunning)
        return;

    if(m_computationsDelay > 0.f)
    {
        m_tmpTime += timeToAdd;
        if(m_tmpTime > m_computationsDelay)
        {
            m_tmpTime -= m_computationsDelay;
            GetAnimation(m_currentAnimation).UpdateTime(m_computationsDelay * m_speedRatio);
        }
    }
    else
    {
        GetAnimation(m_currentAnimation).UpdateTime(timeToAdd * m_speedRatio);
    }
}

void SkeletonAnimator::Seek(float time)
{
    GetAnimation(m_currentAnimation).Seek(time);
}

void SkeletonAnimator::Reset()
{
    GetAnimation(m_currentAnimation).Reset();
}

void SkeletonAnimator::Play()
{
    m_isRunning = true;

    if(m_isStopped)
    {
        m_isStopped = false;
        Reset();
    }
}

void SkeletonAnimator::Pause()
{
    m_isRunning = false;
}

void SkeletonAnimator::Stop()
{
    m_isRunning = false;
    m_isStopped = true;
}

void SkeletonAnimator::SetSpeedRatio(float ratio)
{
    if(ratio > 0)
        m_speedRatio = ratio;
}

bool SkeletonAnimator::IsPlaying() const
{
    return m_isRunning;
}

bool SkeletonAnimator::IsPausing() const
{
    return (!m_isRunning) && (!m_isStopped);
}

bool SkeletonAnimator::IsStopped() const
{
    return (!m_isRunning) && m_isStopped;
}

float SkeletonAnimator::GetSpeedRatio() const
{
    return m_speedRatio;
}

void SkeletonAnimator::ApplyToSkeleton(std::vector<Bone*> &boneVec, Sk::Res::SkImageManager & imageMgr)
{
    GetAnimation(m_currentAnimation).ApplyToSkeleton(boneVec, imageMgr);
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

void SkeletonAnimator::LoadFromXml(TiXmlElement *ele)
{
    m_animations.clear();

    ele->QueryFloatAttribute("calculationDelay", &m_computationsDelay);

    TiXmlNode *child;
    for( child = ele->FirstChild(); child; child = child->NextSibling() )
    {
        if(child->ToElement())
        {
            m_animations[std::string(child->ToElement()->Attribute("name"))] = Animation();
            m_animations[std::string(child->ToElement()->Attribute("name"))].LoadFromXml(child->ToElement());
        }
    }
}

void SkeletonAnimator::SaveToXml(TiXmlElement *ele)
{
    ele->SetDoubleAttribute("calculationDelay", m_computationsDelay);

    for(std::map<std::string, Animation>::iterator it = m_animations.begin(); it != m_animations.end(); it++)
    {
        TiXmlElement *newEle = new TiXmlElement("Animation");
        newEle->SetAttribute("name", it->first.c_str());
        it->second.SaveToXml(newEle);
        ele->LinkEndChild(newEle);
    }
}

void SkeletonAnimator::ExposeResources(Sk::Res::SkImageManager & manager)
{
    for(std::map<std::string, Animation>::iterator it = m_animations.begin(); it != m_animations.end(); it++)
    {
        it->second.ExposeResources(manager);
    }
}

}

}
