#ifndef SKTEMPLATE_H
#define SKTEMPLATE_H

#include <map>
#include <string>
#include <utility>

#include "BoneAnimation.h"

namespace Sk
{

namespace Anim
{

class Animation;

class Template
{
    public:
        Template(Animation &animation, std::vector<std::pair<std::string, std::string> > bonesDescriptions, KeyFrameTypes types);
        ~Template();

        void LoadFromFile(const std::string &path);
        void SaveToFile(const std::string &path);

        void CreateAnimation(std::map<std::string, std::string> &bonesNames, Animation &baseAnimation);

    private:
        float m_period;
        std::map<std::string, BoneAnimation> m_keyFrames;
        std::vector<std::pair<std::string, std::string> > m_boneDescriptions;
        KeyFrameTypes m_types;
};

}

}

#endif
