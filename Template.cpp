#include "Template.h"

#include "Animation.h"
#include "GDL/tinyxml/tinyxml.h"

namespace Sk
{

namespace Anim
{

Template::Template(Animation &animation, std::vector<std::pair<std::string, std::string> > bonesDescriptions, KeyFrameTypes types)
{
    m_types = types;

    for(std::map<std::string, BoneAnimation>::iterator it = animation.m_keyFrames.begin(); it != animation.m_keyFrames.end(); it++)
    {
        for(std::map<KeyFrameType, std::vector<KeyFrame> >::iterator it2 = it->second.keyFrames.begin(); it2 != it->second.keyFrames.end(); it2++)
        {
            if((types & it2->first) != 0)
            {
                m_keyFrames[it->first].keyFrames[it2->first] = it2->second;
            }
        }
    }

    m_boneDescriptions = bonesDescriptions;
}

Template::~Template()
{

}

void Template::LoadFromFile(const std::string &path)
{
    TiXmlDocument *doc = new TiXmlDocument(path.c_str());
    doc->LoadFile(path.c_str());

    TiXmlElement *ele = doc->RootElement()->FirstChildElement("Keyframes");

    m_keyFrames.clear();
    m_boneDescriptions.clear();

    float period = 0;
    ele->QueryFloatAttribute("period", &period);
    m_period = period;

    //Query all BoneAnimation
    TiXmlNode *child;
    for( child = ele->FirstChild("Bone"); child; child = child->NextSibling("Bone") )
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

void Template::SaveToFile(const std::string &path)
{
    TiXmlDocument *doc = new TiXmlDocument("Template");
    TiXmlElement *baseEle = doc->LinkEndChild(new TiXmlElement("Template"))->ToElement();
    TiXmlElement *ele = baseEle->LinkEndChild(new TiXmlElement("Keyframes"))->ToElement();

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

    doc->SaveFile(path.c_str());
}

}

}
