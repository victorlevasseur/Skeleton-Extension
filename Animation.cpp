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

#include "Animation.h"

#include "GDL/tinyxml/tinyxml.h"

#include "BoneAnimation.h"
#include "InterpolationMethods.h"
#include "KeyFrame.h"
#include "Bone.h"
#include "ImageManager.h"

namespace Sk
{

namespace Anim
{

Animation::Animation() : m_period(10), m_autoRepeat(true)
{
    Reset();
}

Animation::~Animation()
{

}

void Animation::SetKeyFrame(const std::string &boneName, KeyFrameType type, KeyFrame &keyframe)
{
    for(unsigned int a = 0; a < m_keyFrames[boneName].keyFrames[type].size(); a++)
    {
        if(m_keyFrames[boneName].keyFrames[type][a].time == keyframe.time)
        {
            m_keyFrames[boneName].keyFrames[type][a] = keyframe;
            ReorderKeys(boneName);
            return;
        }
    }

    m_keyFrames[boneName].keyFrames[type].push_back(keyframe);
    ReorderKeys(boneName);
}

void Animation::SetKeyFrame(const std::string &boneName, KeyFrameType type, float time, float value)
{
    KeyFrame timefloat;
    timefloat.time = time;
    timefloat.value = value;

    SetKeyFrame(boneName, type, timefloat);
}

void Animation::SetKeyFrame(const std::string &boneName, KeyFrameType type, float time, std::string value)
{
    KeyFrame timefloat;
    timefloat.time = time;
    timefloat.valueStr = value;

    SetKeyFrame(boneName, type, timefloat);
}

bool Animation::HasKeyFrame(const std::string &boneName, KeyFrameType type, float time)
{
    if(m_keyFrames[boneName].keyFrames.count(type) == 0)
        return false;

    for(unsigned int a = 0; a < m_keyFrames[boneName].keyFrames[type].size(); a++)
    {
        if(m_keyFrames[boneName].keyFrames[type][a].time == time)
        {
            return true;
        }
    }

    return false;
}

void Animation::RemoveKeyFrame(const std::string &boneName, KeyFrameType type, float time)
{
    for(unsigned int a = 0; a < m_keyFrames[boneName].keyFrames[type].size(); a++)
    {
        if(m_keyFrames[boneName].keyFrames[type][a].time == time)
        {
            m_keyFrames[boneName].keyFrames[type].erase(m_keyFrames[boneName].keyFrames[type].begin() + a);
            ReorderKeys(boneName);
            return;
        }
    }
}

void Animation::ClearKeyFrame(const std::string &boneName, KeyFrameType type)
{
    m_keyFrames[boneName].keyFrames[type].clear();
}

std::string Animation::GetKeyFrameInterpolation(const std::string &boneName, KeyFrameType type, float time)
{
    for(unsigned int a = 0; a < m_keyFrames[boneName].keyFrames[type].size(); a++)
    {
        if(m_keyFrames[boneName].keyFrames[type][a].time == time)
        {
            return m_keyFrames[boneName].keyFrames[type][a].interpolation;
        }
    }

    return "";
}

void Animation::SetKeyFrameInterpolation(const std::string &boneName, KeyFrameType type, float time, const std::string &method)
{
    for(unsigned int a = 0; a < m_keyFrames[boneName].keyFrames[type].size(); a++)
    {
        if(m_keyFrames[boneName].keyFrames[type][a].time == time)
        {
            m_keyFrames[boneName].keyFrames[type][a].interpolation = method;
        }
    }
}

void Animation::UpdateTime(float timeToAdd)
{
    m_time += timeToAdd;

    while(m_time >= m_period && m_period > 0)
    {
        m_time -= m_period;
    }

    UpdateTimeOfSmoothedType(timeToAdd, AngleKeyFrame);
    UpdateTimeOfSmoothedType(timeToAdd, LengthKeyFrame);
    UpdateTimeOfSmoothedType(timeToAdd, PositionXKeyFrame);
    UpdateTimeOfSmoothedType(timeToAdd, PositionYKeyFrame);
    UpdateTimeOfStringType(timeToAdd, ImageKeyFrame);
}

float Animation::GetTimeDelta(const KeyFrame &frame1, const KeyFrame &frame2)
{
    return frame1.time <= frame2.time ? frame2.time - frame1.time : frame2.time + m_period - frame1.time;
}

int Animation::GetNextIndex(const std::string &boneName, KeyFrameType type, unsigned int index)
{
    if(index < GetBoneKeyFrames(boneName, type).size() - 1)
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
    Seek(0);
}

void Animation::Seek(float time)
{
    m_time = time;

    while(m_time >= m_period && m_period > 0)
    {
        m_time -= m_period;
    }

    SeekOfSmoothedType(time, AngleKeyFrame);
    SeekOfSmoothedType(time, LengthKeyFrame);
    SeekOfSmoothedType(time, PositionXKeyFrame);
    SeekOfSmoothedType(time, PositionYKeyFrame);
    SeekOfStringType(time, ImageKeyFrame);
}

void Animation::UpdateTimeOfSmoothedType(float timeToAdd, KeyFrameType type)
{
    std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin();
    for(; it != m_keyFrames.end(); it++)
    {
        std::vector<KeyFrame> *keyFrames = &(it->second.keyFrames[type]);

        if(keyFrames->size() == 0)
            continue;


        KeyFrame *key = &(keyFrames->at(it->second.currentIndex[type]));

        if(m_period == 0)
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

        it->second.progress[type] = GetTimeDelta(*key, *nextKey) != 0 ? ((((m_time >= key->time) ? m_time - key->time : m_time + m_period - key->time)) / GetTimeDelta(*key, *nextKey)) : 1;
        it->second.tmp_angleValue[type] = Sk::Anim::Interp::Get::Method(key->interpolation)->GetResult(it->second.progress[type], key->value, nextKey->value);
    }
}

void Animation::SeekOfSmoothedType(float time, KeyFrameType type)
{
    std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin();
    for(; it != m_keyFrames.end(); it++)
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

        if(m_period == 0)
        {
            it->second.tmp_angleValue[type] = key->value;
            continue;
        }

        KeyFrame *nextKey = &(it->second.keyFrames[type].at(GetNextIndex(it->first, type, it->second.currentIndex[type])));

        it->second.progress[type] = GetTimeDelta(*key, *nextKey) != 0 ? ((((m_time >= key->time) ? m_time - key->time : m_time + m_period - key->time)) / GetTimeDelta(*key, *nextKey)) : 1;
        it->second.tmp_angleValue[type] = Sk::Anim::Interp::Get::Method(key->interpolation)->GetResult(it->second.progress[type], key->value, nextKey->value);
    }
}

void Animation::UpdateTimeOfStringType(float timeToAdd, KeyFrameType type)
{
    std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin();
    for(; it != m_keyFrames.end(); it++)
    {
        std::vector<KeyFrame> *keyFrames = &(it->second.keyFrames[type]);

        if(keyFrames->size() == 0)
            continue;

        KeyFrame *key = &(keyFrames->at(it->second.currentIndex[type]));

        if(m_period == 0)
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

void Animation::SeekOfStringType(float time, KeyFrameType type)
{
    std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin();
    for(; it != m_keyFrames.end(); it++)
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

        if(m_period == 0)
        {
            it->second.tmp_string[type] = key->valueStr;
            continue;
        }

        it->second.tmp_string[type] = key->valueStr;
    }
}

void Animation::ApplyToSkeleton(std::vector<Bone*> &boneVec, Sk::Res::SkImageManager & imageMgr)
{
    for(unsigned int a = 0; a < boneVec.size(); a++)
    {
        if(m_keyFrames.count(boneVec[a]->GetName()) == 0)
            continue;

        boneVec[a]->m_relativeRotation = m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[AngleKeyFrame];
        boneVec[a]->m_size = m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[LengthKeyFrame];
        boneVec[a]->m_offset.x = m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[PositionXKeyFrame];
        boneVec[a]->m_offset.y = m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[PositionYKeyFrame];

        if(boneVec[a]->GetTextureName() != m_keyFrames[boneVec[a]->GetName()].tmp_string[ImageKeyFrame])
        {
            boneVec[a]->SetTextureName(m_keyFrames[boneVec[a]->GetName()].tmp_string[ImageKeyFrame]);
            boneVec[a]->LoadTexture(imageMgr);
        }
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
    for(std::map<KeyFrameType, std::vector<KeyFrame> >::iterator it = m_keyFrames[boneName].keyFrames.begin(); it != m_keyFrames[boneName].keyFrames.end(); it++)
    {
        std::sort(it->second.begin(), it->second.end(), TimeOrderFunctor());
    }
}

std::vector<float> Animation::GetListOfKeyFramesTime(const std::string &bone, KeyFrameType type)
{
    std::vector<float> listOfKeys;

    if(bone == "")
    {
        for(std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin(); it != m_keyFrames.end(); it++)
        {
            if(type == AnyKeyFrame)
            {
                for(std::map<KeyFrameType, std::vector<KeyFrame> >::iterator it2 = it->second.keyFrames.begin(); it2 != it->second.keyFrames.end(); it2++)
                {
                    for(unsigned int a = 0; a < it2->second.size(); a++)
                    {
                        listOfKeys.push_back(it2->second.at(a).time);
                    }
                }
            }
            else
            {
                for(unsigned int a = 0; a < it->second.keyFrames[type].size(); a++)
                {
                    listOfKeys.push_back(it->second.keyFrames[type].at(a).time);
                }
            }
        }
    }
    else
    {
        if(type == AnyKeyFrame)
        {
            for(std::map<KeyFrameType, std::vector<KeyFrame> >::iterator it2 = m_keyFrames[bone].keyFrames.begin(); it2 != m_keyFrames[bone].keyFrames.end(); it2++)
            {
                for(unsigned int a = 0; a < it2->second.size(); a++)
                {
                    listOfKeys.push_back(it2->second.at(a).time);
                }
            }
        }
        else
        {
            for(unsigned int a = 0; a < m_keyFrames[bone].keyFrames[type].size(); a++)
            {
                listOfKeys.push_back(m_keyFrames[bone].keyFrames[type].at(a).time);
            }
        }
    }

    std::sort(listOfKeys.begin(), listOfKeys.end());
    std::vector<float>::iterator lastEle = std::unique(listOfKeys.begin(), listOfKeys.end());
    listOfKeys.resize(lastEle - listOfKeys.begin());

    return listOfKeys;
}

void Animation::LoadFromXml(TiXmlElement *ele)
{
    Reset();
    m_keyFrames.clear();

    float period = 0;
    ele->QueryFloatAttribute("period", &period);
    SetPeriod(period);

    //Query all BoneAnimation
    TiXmlNode *child;
    for( child = ele->FirstChild("Bone"); child; child = child->NextSibling() )
    {
        if(child->ToElement())
        {
            m_keyFrames[std::string(child->ToElement()->Attribute("name"))] = BoneAnimation();
            BoneAnimation *currentBoneAnim = &m_keyFrames[std::string(child->ToElement()->Attribute("name"))];
            currentBoneAnim->keyFrames.clear();

            //Query all frames types
            TiXmlNode *keyframetypes;
            for( keyframetypes = child->ToElement()->FirstChild("Type"); keyframetypes; keyframetypes = keyframetypes->NextSibling() )
            {
                int typeInt = 0;
                keyframetypes->ToElement()->QueryIntAttribute("type", &typeInt);

                KeyFrameType type = static_cast<KeyFrameType>(typeInt);

                //Query all KeyFrames
                TiXmlNode *keyframe;
                for( keyframe = keyframetypes->ToElement()->FirstChild("Keyframe"); keyframe; keyframe = keyframe->NextSibling() )
                {
                    if(keyframe->ToElement())
                    {
                        KeyFrame timefloat;
                        keyframe->ToElement()->QueryFloatAttribute("time", &timefloat.time);
                        keyframe->ToElement()->QueryFloatAttribute("value", &timefloat.value);
                        if(keyframe->ToElement()->Attribute("valueStr") != 0)
                            timefloat.valueStr = std::string(keyframe->ToElement()->Attribute("valueStr"));

                        if(keyframe->ToElement()->Attribute("interpolation"))
                            timefloat.interpolation = std::string(keyframe->ToElement()->Attribute("interpolation"));
                        else
                            timefloat.interpolation = "Linear";

                        currentBoneAnim->keyFrames[type].push_back(timefloat);
                    }
                }
            }
        }
    }
}

void Animation::SaveToXml(TiXmlElement *ele)
{
    ele->SetDoubleAttribute("period", m_period);

    for(std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin(); it != m_keyFrames.end(); it++)
    {
        TiXmlElement *boneEle = new TiXmlElement("Bone");
        boneEle->SetAttribute("name", it->first.c_str());

        for(std::map<KeyFrameType, std::vector<KeyFrame> >::iterator it2 = it->second.keyFrames.begin(); it2 != it->second.keyFrames.end(); it2++)
        {
            TiXmlElement *keyframetypeEle = new TiXmlElement("Type");
            keyframetypeEle->SetDoubleAttribute("type", static_cast<int>(it2->first));

            for(unsigned int a = 0; a < it2->second.size(); a++)
            {
                TiXmlElement *timefloatEle = new TiXmlElement("Keyframe");
                timefloatEle->SetDoubleAttribute("time", it2->second.at(a).time);
                timefloatEle->SetDoubleAttribute("value", it2->second.at(a).value);
                timefloatEle->SetAttribute("valueStr", it2->second.at(a).valueStr.c_str());
                timefloatEle->SetAttribute("interpolation", it2->second.at(a).interpolation.c_str());

                keyframetypeEle->LinkEndChild(timefloatEle);
            }

            boneEle->LinkEndChild(keyframetypeEle);
        }
        ele->LinkEndChild(boneEle);
    }
}

void Animation::ExposeResources(Sk::Res::SkImageManager & manager)
{
    for(std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin(); it != m_keyFrames.end(); it++)
    {
        for(unsigned int a = 0; a < it->second.keyFrames[ImageKeyFrame].size(); a++)
        {
            manager.ExposeImage(it->second.keyFrames[ImageKeyFrame].at(a).valueStr);
        }
    }
}

bool TimeOrderFunctor::operator() (KeyFrame left, KeyFrame right)
{
    return (left.time < right.time);
}

}

}
