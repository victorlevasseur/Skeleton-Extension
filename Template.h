#ifndef SKTEMPLATE_H
#define SKTEMPLATE_H

#ifdef GD_IDE_ONLY

#include <map>
#include <string>
#include <utility>

#include "BoneAnimation.h"

namespace Sk
{

namespace Anim
{

class Animation;

/**
Class to manage a template. Provides methods to create or apply template from/to an animation.
Note : Only available when GD_IDE_ONLY is defined.
*/
class Template
{
    public:
        Template();
        ~Template();

        void LoadFromFile(const std::string &path);
        void SaveToFile(const std::string &path);

        void CreateFromAnimation(Animation &animation, std::vector<std::pair<std::string, std::string> > bonesDescriptions, KeyFrameTypes types);
        void CreateAnimation(std::map<std::string, std::string> &bonesNames, Animation &baseAnimation);

        const std::vector<std::pair<std::string, std::string> >& GetDescriptions() const {return m_boneDescriptions;};

    private:
        float m_period;
        std::map<std::string, BoneAnimation> m_keyFrames;
        std::vector<std::pair<std::string, std::string> > m_boneDescriptions;
        KeyFrameTypes m_types;
};

}

}

#endif

#endif
