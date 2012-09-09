#ifndef SKTEMPLATE_H
#define SKTEMPLATE_H

#include <map>
#include <string>

#include "BoneAnimation.h"

namespace Sk
{

namespace Anim
{

class Template
{
    public:
        Template(const Animation &animation, std::map<std::string, std::string> bonesDescriptions);
        ~Template();

        void LoadFromFile(const std::string &path);
        void SaveToFile(const std::string &path);

        Animation* CreateAnimation(std::map<std::string, std::string> &bonesNames);

    private:
        float m_period;
        std::map<std::string, BoneAnimation> m_keyFrames;
        std::map<std::string, std::string> m_boneDescriptions;
};

}

}

#endif
