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

#ifndef SKELETONANIMATOR_H
#define SKELETONANIMATOR_H

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "GlobalDefs.h"
#include "Animation.h"

class TiXmlElement;
namespace Sk{namespace Res{class SkImageManager;}}

namespace Sk
{

class Bone;

/**
Anim namespace contains all stuff related to the animation system for skeletons.
 */
namespace Anim
{

/**
This class manages all animations for a skeleton.
 */
class SkeletonAnimator
{
    public:
        SkeletonAnimator();
        virtual ~SkeletonAnimator();

        inline Animation& GetAnimation(const std::string &name);

        const std::string& GetCurrentAnimation() const;
        void SetCurrentAnimation(const std::string &animName);

        void CreateAnimation(const std::string &name, const std::string &asACopyOf = std::string());
        void RenameAnimation(const std::string &name, const std::string &newName);
        void DeleteAnimation(const std::string &name);

        std::vector<std::string> GetListOfAnimations() const;

        void UpdateTime(float timeToAdd);
        void Seek(float time);
        void Reset();

        void Play();
        void Pause();
        void Stop();

        void SetSpeedRatio(float ratio);

        bool IsPlaying() const;
        bool IsPausing() const;
        bool IsStopped() const;

        float GetSpeedRatio() const;

        void SetDelayBetweenCalculations(float delay) {m_calculationDelay = delay;};
        float GetDelayBetweenCalculations() const {return m_calculationDelay;};

        void ApplyToSkeleton(std::vector<Bone*> &boneVec, Sk::Res::SkImageManager & imageMgr);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

        void LoadFromXml(TiXmlElement *ele);
        void SaveToXml(TiXmlElement *ele);

        void ExposeResources(Sk::Res::SkImageManager & manager);

    protected:
    private:
        std::map<std::string, Animation> m_animations;
        std::string m_currentAnimation;

        bool m_isRunning;
        bool m_isStopped;

        float m_speedRatio;

        float m_calculationDelay;
        float m_tmpTime;
};

inline Animation& SkeletonAnimator::GetAnimation(const std::string &name)
{
    return m_animations[name];
}

}

}

#endif // SKELETONANIMATOR_H
