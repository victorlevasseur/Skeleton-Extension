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

SkeletonAnimator::SkeletonAnimator() : m_currentAnimation("Initial"), m_time(0), m_isRunning(true), m_isStopped(false), m_speedRatio(1.f), m_computationsDelay(0.f), m_tmpTime(0.f)
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
    Reset();
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
            UpdateTimeInternal(timeToAdd * m_speedRatio);
        }
    }
    else
    {
        UpdateTimeInternal(timeToAdd * m_speedRatio);
    }
}

void SkeletonAnimator::Seek(float time)
{
    SeekInternal(time);
}

void SkeletonAnimator::UpdateTimeInternal(float timeToAdd)
{
    Animation *currentAnim = &GetAnimation(m_currentAnimation);

    m_time += timeToAdd;

    while(m_time >= currentAnim->m_period && currentAnim->m_period > 0)
    {
        m_time -= currentAnim->m_period;
    }

    UpdateTimeOfSmoothedType(timeToAdd, AngleKeyFrame);
    UpdateTimeOfSmoothedType(timeToAdd, LengthKeyFrame);
    UpdateTimeOfSmoothedType(timeToAdd, PositionXKeyFrame);
    UpdateTimeOfSmoothedType(timeToAdd, PositionYKeyFrame);
    UpdateTimeOfStringType(timeToAdd, ImageKeyFrame);
}

void SkeletonAnimator::SeekInternal(float time)
{
    Animation *currentAnim = &GetAnimation(m_currentAnimation);

    m_time = time;

    while(m_time >= currentAnim->m_period && currentAnim->m_period > 0)
    {
        m_time -= currentAnim->m_period;
    }

    SeekOfSmoothedType(time, AngleKeyFrame);
    SeekOfSmoothedType(time, LengthKeyFrame);
    SeekOfSmoothedType(time, PositionXKeyFrame);
    SeekOfSmoothedType(time, PositionYKeyFrame);
    SeekOfStringType(time, ImageKeyFrame);
}

void SkeletonAnimator::UpdateTimeOfSmoothedType(float timeToAdd, KeyFrameType type)
{
    Animation *currentAnim = &GetAnimation(m_currentAnimation);

    std::map<std::string, BoneAnimation>::iterator it = currentAnim->m_keyFrames.begin();
    for(; it != currentAnim->m_keyFrames.end(); it++)
    {
        std::vector<KeyFrame> *keyFrames = &(it->second.keyFrames[type]);

        if(keyFrames->size() == 0)
            continue;


        KeyFrame *key = &(keyFrames->at(it->second.currentIndex[type]));

        if(currentAnim->m_period == 0)
        {
            it->second.tmp_angleValue[type] = key->value;
            continue;
        }

        KeyFrame *nextKey = &(keyFrames->at(GetNextIndex(it->first, type, it->second.currentIndex[type])));


        while(((m_time > nextKey->time) && (key->time < nextKey->time)) ||
              ((key->time > nextKey->time) && (m_time > nextKey->time) && (m_time < key->time)))
        {
            it->second.currentIndex[type] = GetNextIndex(it->first, type, it->second.currentIndex[type]);
            key = nextKey;

            nextKey = &(keyFrames->at(GetNextIndex(it->first, type, it->second.currentIndex[type])));
        }

        //it->second.progress[type] = (GetTimeDelta(*key, *nextKey) != 0 ? ((((m_time >= key->time) ? m_time - key->time : m_time + m_period - key->time)) / GetTimeDelta(*key, *nextKey)) : 1);
        it->second.tmp_angleValue[type] = Sk::Anim::Interp::Get::Method(key->interpolation)->GetResult((GetTimeDelta(*key, *nextKey) != 0 ? ((((m_time >= key->time) ? m_time - key->time : m_time + currentAnim->m_period - key->time)) / GetTimeDelta(*key, *nextKey)) : 1),
                                                                                                       key->value,
                                                                                                       nextKey->value);
    }
}

void SkeletonAnimator::SeekOfSmoothedType(float time, KeyFrameType type)
{
    Animation *currentAnim = &GetAnimation(m_currentAnimation);

    std::map<std::string, BoneAnimation>::iterator it = currentAnim->m_keyFrames.begin();
    for(; it != currentAnim->m_keyFrames.end(); it++)
    {
        if(it->second.keyFrames[type].size() == 0)
            continue;

        for(unsigned int a = 0; a < it->second.keyFrames[type].size(); a++)
        {
            if(it->second.keyFrames[type].at(a).time > m_time)
                break;
            it->second.currentIndex[type] = a;
        }

        KeyFrame *key = &(it->second.keyFrames[type].at(it->second.currentIndex[type]));

        if(currentAnim->m_period == 0)
        {
            it->second.tmp_angleValue[type] = key->value;
            continue;
        }

        KeyFrame *nextKey = &(it->second.keyFrames[type].at(GetNextIndex(it->first, type, it->second.currentIndex[type])));

        //it->second.progress[type] = (GetTimeDelta(*key, *nextKey) != 0 ? ((((m_time >= key->time) ? m_time - key->time : m_time + m_period - key->time)) / GetTimeDelta(*key, *nextKey)) : 1);
        it->second.tmp_angleValue[type] = Sk::Anim::Interp::Get::Method(key->interpolation)->GetResult((GetTimeDelta(*key, *nextKey) != 0 ? ((((m_time >= key->time) ? m_time - key->time : m_time + currentAnim->m_period - key->time)) / GetTimeDelta(*key, *nextKey)) : 1),
                                                                                                       key->value,
                                                                                                       nextKey->value);
    }
}

void SkeletonAnimator::UpdateTimeOfStringType(float timeToAdd, KeyFrameType type)
{
    Animation *currentAnim = &GetAnimation(m_currentAnimation);

    std::map<std::string, BoneAnimation>::iterator it = currentAnim->m_keyFrames.begin();
    for(; it != currentAnim->m_keyFrames.end(); it++)
    {
        std::vector<KeyFrame> *keyFrames = &(it->second.keyFrames[type]);

        if(keyFrames->size() == 0)
            continue;

        KeyFrame *key = &(keyFrames->at(it->second.currentIndex[type]));

        if(currentAnim->m_period == 0)
        {
            it->second.tmp_string[type] = key->valueStr;
            continue;
        }

        KeyFrame *nextKey = &(keyFrames->at(GetNextIndex(it->first, type, it->second.currentIndex[type])));


        while(((m_time > nextKey->time) && (key->time < nextKey->time)) ||
              ((key->time > nextKey->time) && (m_time > nextKey->time) && (m_time < key->time)))
        {
            it->second.currentIndex[type] = GetNextIndex(it->first, type, it->second.currentIndex[type]);
            key = nextKey;

            nextKey = &(keyFrames->at(GetNextIndex(it->first, type, it->second.currentIndex[type])));
        }

        it->second.tmp_string[type] = key->valueStr;
    }
}

void SkeletonAnimator::SeekOfStringType(float time, KeyFrameType type)
{
    Animation *currentAnim = &GetAnimation(m_currentAnimation);

    std::map<std::string, BoneAnimation>::iterator it = currentAnim->m_keyFrames.begin();
    for(; it != currentAnim->m_keyFrames.end(); it++)
    {
        if(it->second.keyFrames[type].size() == 0)
            continue;

        for(unsigned int a = 0; a < it->second.keyFrames[type].size(); a++)
        {
            if(it->second.keyFrames[type].at(a).time > m_time)
                break;
            it->second.currentIndex[type] = a;
        }

        KeyFrame *key = &(it->second.keyFrames[type].at(it->second.currentIndex[type]));

        if(currentAnim->m_period == 0)
        {
            it->second.tmp_string[type] = key->valueStr;
            continue;
        }

        it->second.tmp_string[type] = key->valueStr;
    }
}

float SkeletonAnimator::GetTimeDelta(const KeyFrame &frame1, const KeyFrame &frame2)
{
    return frame1.time <= frame2.time ? frame2.time - frame1.time : frame2.time + GetAnimation(m_currentAnimation).m_period - frame1.time;
}

int SkeletonAnimator::GetNextIndex(const std::string &boneName, KeyFrameType type, unsigned int index)
{
    if(index < GetAnimation(m_currentAnimation).GetBoneKeyFrames(boneName, type).size() - 1)
    {
        index++;
        return index;
    }
    else
    {
        return 0;
    }
}

void SkeletonAnimator::Reset()
{
    Seek(0);
    //GetAnimation(m_currentAnimation).Reset();
}

float SkeletonAnimator::GetTime()
{
    return m_time;
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
    //GetAnimation(m_currentAnimation).ApplyToSkeleton(boneVec, imageMgr);

    Animation *currentAnim = &GetAnimation(m_currentAnimation);

    for(unsigned int a = 0; a < boneVec.size(); a++)
    {
        if(currentAnim->m_keyFrames.count(boneVec[a]->GetName()) == 0)
            continue;

        boneVec[a]->m_angle = currentAnim->m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[AngleKeyFrame];
        boneVec[a]->m_length = currentAnim->m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[LengthKeyFrame];
        boneVec[a]->m_offset.x = currentAnim->m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[PositionXKeyFrame];
        boneVec[a]->m_offset.y = currentAnim->m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[PositionYKeyFrame];

        if(boneVec[a]->GetTextureName() != currentAnim->m_keyFrames[boneVec[a]->GetName()].tmp_string[ImageKeyFrame])
        {
            boneVec[a]->SetTextureName(currentAnim->m_keyFrames[boneVec[a]->GetName()].tmp_string[ImageKeyFrame]);
            boneVec[a]->LoadTexture(imageMgr);
        }
    }
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

void SkeletonAnimator::LoadFromXml(TiXmlElement *ele, int fileVersion)
{
    m_animations.clear();

    ele->QueryFloatAttribute("calculationDelay", &m_computationsDelay);

    TiXmlNode *child;
    for( child = ele->FirstChild(); child; child = child->NextSibling() )
    {
        if(child->ToElement())
        {
            m_animations[std::string(child->ToElement()->Attribute("name"))] = Animation();
            m_animations[std::string(child->ToElement()->Attribute("name"))].LoadFromXml(child->ToElement(), fileVersion);
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
