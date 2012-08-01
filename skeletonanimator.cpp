#include "skeletonanimator.h"

#include "Bone.h"
#include "interpolationMethods.h"

#include "GDL/CommonTools.h"

namespace Sk
{

Animation::Animation() : m_period(10), m_autoRepeat(true)
{
    Reset();
}

Animation::~Animation()
{

}

void Animation::SetKeyFrame(const std::string &boneName, KeyFrameType type, TimeFloat &keyframe)
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
    TimeFloat timefloat;
    timefloat.time = time;
    timefloat.value = value;

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

void Animation::UpdateTime(float timeToAdd)
{
    m_time += timeToAdd;

    while(m_time >= m_period && m_period > 0)
    {
        m_time -= m_period;
    }

    UpdateTimeOfSmoothedType(timeToAdd, AngleKeyFrame);
    UpdateTimeOfSmoothedType(timeToAdd, LengthKeyFrame);
}

float Animation::GetTimeDelta(const TimeFloat &frame1, const TimeFloat &frame2)
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
}

void Animation::UpdateTimeOfSmoothedType(float timeToAdd, KeyFrameType type)
{
    std::map<std::string, BoneAnimation>::iterator it = m_keyFrames.begin();
    for(; it != m_keyFrames.end(); it++)
    {
        if(it->second.keyFrames[type].size() == 0)
            continue;


        TimeFloat key = it->second.keyFrames[type].at(it->second.currentIndex[type]);

        if(m_period == 0)
        {
            it->second.tmp_angleValue[type] = key.value;
            continue;
        }

        TimeFloat nextKey = it->second.keyFrames[type].at(GetNextIndex(it->first, type, it->second.currentIndex[type]));


        while(((m_time > nextKey.time) && (key.time < nextKey.time)) ||
              ((key.time > nextKey.time) && (m_time > nextKey.time) && (m_time < key.time)))
        {
            it->second.currentIndex[type] = GetNextIndex(it->first, type, it->second.currentIndex[type]);
            key = nextKey;

            nextKey = it->second.keyFrames[type].at(GetNextIndex(it->first, type, it->second.currentIndex[type]));
        }

        it->second.progress[type] = GetTimeDelta(key, nextKey) != 0 ? ((((m_time >= key.time) ? m_time - key.time : m_time + m_period - key.time)) / GetTimeDelta(key, nextKey)) : 1;
        it->second.tmp_angleValue[type] = Sk::Interpolation::Get::Method(key.interpolation)->GetResult(it->second.progress[type], key.value, nextKey.value, key.parameters);
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

        TimeFloat key = it->second.keyFrames[type].at(it->second.currentIndex[type]);

        if(m_period == 0)
        {
            it->second.tmp_angleValue[type] = key.value;
            continue;
        }

        TimeFloat nextKey = it->second.keyFrames[type].at(GetNextIndex(it->first, type, it->second.currentIndex[type]));

        it->second.progress[type] = GetTimeDelta(key, nextKey) != 0 ? ((((m_time >= key.time) ? m_time - key.time : m_time + m_period - key.time)) / GetTimeDelta(key, nextKey)) : 1;
        it->second.tmp_angleValue[type] = Sk::Interpolation::Get::Method(key.interpolation)->GetResult(it->second.progress[type], key.value, nextKey.value, key.parameters);
        //it->second.tmp_angleValue[type] = (nextKey.value - key.value) * it->second.progress[type] + key.value;
    }
}

void Animation::ApplyToSkeleton(std::vector<Bone*> &boneVec)
{
    for(unsigned int a = 0; a < boneVec.size(); a++)
    {
        if(m_keyFrames.count(boneVec[a]->GetName()) == 0)
            continue;

        boneVec[a]->m_relativeRotation = m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[AngleKeyFrame];
        boneVec[a]->m_size = m_keyFrames[boneVec[a]->GetName()].tmp_angleValue[LengthKeyFrame];
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
    for(std::map<KeyFrameType, std::vector<TimeFloat> >::iterator it = m_keyFrames[boneName].keyFrames.begin(); it != m_keyFrames[boneName].keyFrames.end(); it++)
    {
        std::sort(it->second.begin(), it->second.end(), TimeOrderFunctor());
    }
}

std::vector<float> Animation::GetListOfKeyFramesTime(const std::string &bone)
{
    std::vector<float> listOfKeys;

    if(bone == "")
    {
        for(std::map<std::string, BoneAnimation>::const_iterator it = m_keyFrames.begin(); it != m_keyFrames.end(); it++)
        {
            for(std::map<KeyFrameType, std::vector<TimeFloat> >::const_iterator it2 = it->second.keyFrames.begin(); it2 != it->second.keyFrames.end(); it2++)
            {
                for(unsigned int a = 0; a < it2->second.size(); a++)
                {
                    listOfKeys.push_back(it2->second.at(a).time);
                }
            }
        }
    }
    else
    {
        for(std::map<KeyFrameType, std::vector<TimeFloat> >::const_iterator it2 = m_keyFrames[bone].keyFrames.begin(); it2 != m_keyFrames[bone].keyFrames.end(); it2++)
        {
            for(unsigned int a = 0; a < it2->second.size(); a++)
            {
                listOfKeys.push_back(it2->second.at(a).time);
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
                        TimeFloat timefloat;
                        keyframe->ToElement()->QueryFloatAttribute("time", &timefloat.time);
                        keyframe->ToElement()->QueryFloatAttribute("value", &timefloat.value);
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

        for(std::map<KeyFrameType, std::vector<TimeFloat> >::iterator it2 = it->second.keyFrames.begin(); it2 != it->second.keyFrames.end(); it2++)
        {
            TiXmlElement *keyframetypeEle = new TiXmlElement("Type");
            keyframetypeEle->SetDoubleAttribute("type", static_cast<int>(it2->first));

            for(unsigned int a = 0; a < it2->second.size(); a++)
            {
                TiXmlElement *timefloatEle = new TiXmlElement("Keyframe");
                timefloatEle->SetDoubleAttribute("time", it2->second.at(a).time);
                timefloatEle->SetDoubleAttribute("value", it2->second.at(a).value);

                keyframetypeEle->LinkEndChild(timefloatEle);
            }

            boneEle->LinkEndChild(keyframetypeEle);
        }
        ele->LinkEndChild(boneEle);
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

void SkeletonAnimator::LoadFromXml(TiXmlElement *ele)
{
    m_animations.clear();

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
    for(std::map<std::string, Animation>::iterator it = m_animations.begin(); it != m_animations.end(); it++)
    {
        TiXmlElement *newEle = new TiXmlElement("Animation");
        newEle->SetAttribute("name", it->first.c_str());
        it->second.SaveToXml(newEle);
        ele->LinkEndChild(newEle);
    }
}

}
