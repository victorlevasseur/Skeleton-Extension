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

#ifndef SKANIMATION_H
#define SKANIMATION_H

#include <map>
#include "GlobalDefs.h"
#include "KeyFrame.h"
#include "BoneAnimation.h"

class TiXmlElement;
namespace Sk{class Bone;}
namespace Sk{namespace Res{class SkImageManager;}}

namespace Sk
{

namespace Anim
{

/**
This class represents an animations. It manages all calculations for each bones and contains a map of BoneAnimation (each linked to one bone). The class contains methods to edit keyframes.
 */
class Animation
{
    friend class Sk::Bone;
    friend class SkeletonAnimator;
    friend class Template;

    public:
        Animation();
        virtual ~Animation();

        float GetPeriod() const {return m_period;};
        void SetPeriod(float value) {m_period = value;};

        void SetKeyFrame(const std::string &boneName, KeyFrameType type, KeyFrame &keyframe);
        void SetKeyFrame(const std::string &boneName, KeyFrameType type, float time, float value);
        void SetKeyFrame(const std::string &boneName, KeyFrameType type, float time, std::string value);

        bool HasKeyFrame(const std::string &boneName, KeyFrameType type, float time);
        void RemoveKeyFrame(const std::string &boneName, KeyFrameType type, float time);
        void ClearBoneKeyFrames(const std::string &boneName, KeyFrameType type);

        std::string GetKeyFrameInterpolation(const std::string &boneName, KeyFrameType type, float time);
        void SetKeyFrameInterpolation(const std::string &boneName, KeyFrameType type, float time, const std::string &method);

        /// Don't forget to call SortKeyFrames(const std::string &boneName); after modifying a bone keyframes list.
        inline const std::vector<KeyFrame>& GetBoneKeyFrames(const std::string &boneName, KeyFrameType type);
        void SortKeyFrames(const std::string &boneName);

        std::vector<float> GetKeyFramesTimes(const std::string &bone = "", KeyFrameType type = AnyKeyFrame);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

        void LoadFromXml(TiXmlElement *ele);
        void SaveToXml(TiXmlElement *ele);

        void ExposeResources(Sk::Res::SkImageManager & manager);

    private:

        float m_period;
        bool m_autoRepeat;

        std::map<std::string, BoneAnimation> m_keyFrames;
};

inline const std::vector<KeyFrame>& Animation::GetBoneKeyFrames(const std::string &boneName, KeyFrameType type)
{
    return m_keyFrames[boneName].keyFrames[type];
}

class TimeOrderFunctor : public std::binary_function<KeyFrame, KeyFrame, bool>
{
    public:
        bool operator() (KeyFrame left, KeyFrame right);
};

}

}

#endif
