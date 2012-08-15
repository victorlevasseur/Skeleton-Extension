#ifndef SKELETONANIMATOR_H
#define SKELETONANIMATOR_H

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "globaldefs.h"
#include "animation.h"

class TiXmlElement;

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

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

        void LoadFromXml(TiXmlElement *ele);
        void SaveToXml(TiXmlElement *ele);

    protected:
    private:
        std::map<std::string, Animation> m_animations;
        std::string m_currentAnimation;
};

inline Animation& SkeletonAnimator::GetAnimation(const std::string &name)
{
    return m_animations[name];
}

}

}

#endif // SKELETONANIMATOR_H
