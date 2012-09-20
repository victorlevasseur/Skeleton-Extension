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

        const std::string& GetCurrentAnimationName() const;
        void SetCurrentAnimationName(const std::string &animName);

        void CreateAnimation(const std::string &name, const std::string &asACopyOf = std::string());
        void RenameAnimation(const std::string &name, const std::string &newName);
        void DeleteAnimation(const std::string &name);

        std::vector<std::string> GetAnimations() const;

        void UpdateTime(float timeToAdd);
        void Seek(float time);
        void Reset();

        float GetTime();

        void Play();
        void Pause();
        void Stop();

        void SetSpeedRatio(float ratio);

        bool IsPlaying() const;
        bool IsPausing() const;
        bool IsStopped() const;

        float GetSpeedRatio() const;

        void SetComputationsDelay(float delay) {m_computationsDelay = delay;};
        float GetComputationsDelay() const {return m_computationsDelay;};

        void ApplyToSkeleton(std::vector<Bone*> &boneVec, Sk::Res::SkImageManager & imageMgr);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

        void LoadFromXml(TiXmlElement *ele, int fileVersion);
        void SaveToXml(TiXmlElement *ele);

        void ExposeResources(Sk::Res::SkImageManager & manager);

    protected:
    private:
        std::map<std::string, Animation> m_animations;
        std::string m_currentAnimation;

        void UpdateTimeInternal(float timeToAdd);
        void SeekInternal(float time);

        int GetNextIndex(const std::string &boneName, KeyFrameType type, unsigned int index);
        float GetTimeDelta(const KeyFrame &frame1, const KeyFrame &frame2);

        void UpdateTimeOfSmoothedType(float timeToAdd, KeyFrameType type);
        void SeekOfSmoothedType(float time, KeyFrameType type);

        void UpdateTimeOfStringType(float timeToAdd, KeyFrameType type);
        void SeekOfStringType(float time, KeyFrameType type);

        float m_time;

        bool m_isRunning;
        bool m_isStopped;

        float m_speedRatio;

        float m_computationsDelay;
        float m_tmpTime;
};

inline Animation& SkeletonAnimator::GetAnimation(const std::string &name)
{
    return m_animations[name];
}

}

}

#endif // SKELETONANIMATOR_H
