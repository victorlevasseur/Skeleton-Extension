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
#include "GDL/CommonTools.h"

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
            SortKeyFrames(boneName);
            return;
        }
    }

    m_keyFrames[boneName].keyFrames[type].push_back(keyframe);
    SortKeyFrames(boneName);
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
            SortKeyFrames(boneName);
            return;
        }
    }
}

void Animation::ClearBoneKeyFrames(const std::string &boneName, KeyFrameType type)
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

void Animation::NotifyBoneRenamed(const std::string &oldName, const std::string &newName)
{
    if(m_keyFrames.count(oldName) == 0)
        return;

    m_keyFrames[newName] = BoneAnimation(m_keyFrames[oldName]);
    m_keyFrames.erase(oldName);
}

void Animation::SortKeyFrames(const std::string &boneName)
{
    for(std::map<KeyFrameType, std::vector<KeyFrame> >::iterator it = m_keyFrames[boneName].keyFrames.begin(); it != m_keyFrames[boneName].keyFrames.end(); it++)
    {
        std::sort(it->second.begin(), it->second.end(), TimeOrderFunctor());
    }
}

std::vector<float> Animation::GetKeyFramesTimes(const std::string &bone, KeyFrameType type)
{
    std::vector<float> listOfKeys;

    if(bone == "")
    {
        for(std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin(); it != m_keyFrames.end(); it++)
        {
            if(type == AllKeyFrame)
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
        if(type == AllKeyFrame)
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

void Animation::Merge(Animation &animationToMerge, KeyFrameTypes typesToMerge, std::map<std::string, std::string> namesCorrespondence, bool resetPeriod)
{
    if(resetPeriod)
        SetPeriod(animationToMerge.m_period);

    for(std::map<std::string, BoneAnimation>::iterator it = animationToMerge.m_keyFrames.begin(); it != animationToMerge.m_keyFrames.end(); it++)
    {
        std::string boneName = namesCorrespondence.count(it->first) > 0 ? namesCorrespondence[it->first] : it->first;

        for(std::map<KeyFrameType, std::vector<KeyFrame> >::iterator it2 = animationToMerge.m_keyFrames[it->first].keyFrames.begin(); it2 != animationToMerge.m_keyFrames[it->first].keyFrames.end(); it2++)
        {
            if((typesToMerge & it2->first) != 0)
                m_keyFrames[boneName].keyFrames[it2->first] = it2->second;
        }

    }
}

void Animation::LoadFromXml(TiXmlElement *ele, int fileVersion)
{
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
                int typeInt = 1;
                keyframetypes->ToElement()->QueryIntAttribute("type", &typeInt);

                KeyFrameType type = fileVersion != 0 ? (static_cast<KeyFrameType>(typeInt)) : (static_cast<KeyFrameType>(pow(2, typeInt)));

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
